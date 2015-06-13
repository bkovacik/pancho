#include "render.h"

Render::Render(int width, int height, unsigned char* image_data, GLFWwindow* window) {
	this->width = width;
	this->height = height;
	this->window = window;
	this->frames = 0;
	this->lastTime = glfwGetTime();

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		exit(-1);

	initVertexShader();
	initFragmentShader();
	initShader();

	//create vao
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//init vbo
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(GLfloat), &vertices[0], GL_DYNAMIC_DRAW);

	//init ebo
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size()*sizeof(GLuint), &elements[0], GL_DYNAMIC_DRAW);

	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);

	GLint texAttrib = glGetAttribLocation(shaderProgram, "texcoord");
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));

	bindTexture(image_data);
}

Render::~Render() {
	glDeleteProgram(shaderProgram);
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);

	glDeleteBuffers(1, &ebo);
	glDeleteBuffers(1, &vbo);

	glDeleteVertexArrays(1, &vao);
}

void Render::initVertexShader() {
	vertexSource =
		"#version 330 core\n"
		"in vec2 texcoord;"
		"in vec2 position;"
		"out vec2 Texcoord;"
		"void main() {"
		"	Texcoord = texcoord;"
		"	gl_Position = vec4(position, 0.0, 1.0);"
		"}";

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
}

void Render::initFragmentShader() {
	fragmentSource =
		"#version 330 core\n"
		"in vec2 Texcoord;"
		"out vec4 outColor;"
		"uniform sampler2D tex;"
		"void main() {"
		"	outColor = texture(tex, Texcoord);"
		"}";

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
}

void Render::initShader() {
	//init and "compile" the shader
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glBindFragDataLocation(shaderProgram, 0, "outColor");
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);
}

void Render::bindTexture(unsigned char* image_data) {
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable( GL_TEXTURE_2D );
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	float color[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);
}

void Render::shiftImage(float offX, float offY, int objOffset) {
	int windowX, windowY;
	glfwGetWindowSize(window, &windowX, &windowY);

	float 	ox = offX/windowX,
		oy = offY/windowY;

	for (int i = objOffset; i < objOffset+16; i+=4) {
		vertices[i] += ox;
		vertices[i+1] += oy;
	}

	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size()*sizeof(GLfloat), &vertices[0]);
}

//takes x and y values as coords the image is supposed to be placed at
//the coords structure is gotten from the texture atlas
void Render::addImage(int x, int y, const Coords& coords) {
	int windowX, windowY,
		offX = coords.endX-coords.beginX,
		offY = coords.endY-coords.beginY;
	glfwGetWindowSize(window, &windowX, &windowY);

	float 	bx = x*2.0/windowX - 1.0,
		by = y*2.0/windowY - 1.0,
		ex = bx + offX*2.0/windowX,
		ey = by + offY*2.0/windowY,
		cbx = (float)coords.beginX/width,
		cby = (float)coords.beginY/height,
		cex = (float)coords.endX/width,
		cey = (float)coords.endY/height;

	GLfloat v[] = {
		bx, ey, cbx, cby,	//Top-left
		ex, ey, cex, cby,	//Top-right
		bx, by, cbx, cey,	//Bottom-left
		ex, by, cex, cey,	//Bottom-right
	};
	vertices.insert(vertices.end(), v, v+sizeof(v)/sizeof(GLfloat));

	move.insert(move.end(), 2, 0.0);

	//add degenerate triangles first
	GLuint end = 0;
	if (elements.size()) {
		end = elements.back();
		elements.push_back(end);
		elements.push_back(++end);
	}

	//then add the new quad
	for (GLuint i = end; i < end+4; i++)
		elements.push_back(i);
}

void Render::setMovement(float offX, float offY, int objOffset) {
	move[objOffset++] = offX;
	move[objOffset] = offY;
}

//renders the vertices at the given fps
void Render::render(int fps, int scroll) {
	glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(GLfloat), &vertices[0], GL_DYNAMIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size()*sizeof(GLuint), &elements[0], GL_DYNAMIC_DRAW);

	int windowX, windowY;
	double delay = 1.0/fps;

	glfwGetWindowSize(window, &windowX, &windowY);

	while (!glfwWindowShouldClose(window))
	{
		double currentTime = glfwGetTime();
		if (currentTime - lastTime >= delay) {
			lastTime = currentTime;
			glfwPollEvents();

			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			for (int i = 0; i < move.size(); i+=2) {
				int	xMove = scroll/fps,
					yMove = scroll/fps,
					//round up
					roundX = ((windowX + BACK_TEX_WIDTH - 1) / BACK_TEX_WIDTH) * BACK_TEX_WIDTH,
					roundY = ((windowY + BACK_TEX_HEIGHT - 1) / BACK_TEX_HEIGHT) * BACK_TEX_HEIGHT,
					//add another tex dimension, then multiply whole thing by two, then subtract one step
					xWrap = (roundX + BACK_TEX_WIDTH) * 2 - xMove,
					yWrap = (roundY + BACK_TEX_HEIGHT) * 2 - yMove;

				float	wrapAtX = (float) roundX / windowX,
					wrapAtY = (float) roundY / windowY;

				//wrap background tiles around
				if (vertices[i*8+4] < -wrapAtX)
					shiftImage(xWrap, 0, i*8);
				if (vertices[i*8] > wrapAtX)
					shiftImage(-xWrap, 0, i*8);
				if (vertices[i*8+1] < -wrapAtY)
					shiftImage(0, yWrap, i*8);
				if (vertices[i*8+9] > wrapAtY)
					shiftImage(0, -yWrap, i*8);
				else
					//normalize movement by fps
					shiftImage(move[i]/fps, move[i+1]/fps,i*8);
			}

			glDrawElements(GL_TRIANGLE_STRIP, elements.size(), GL_UNSIGNED_INT, 0);

			glfwSwapBuffers(window);
		}
	}
	
	glfwTerminate();
}
