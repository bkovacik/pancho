#include "render.h"

Render::Render(int width, int height, unsigned char* image_data) {
	this->width = width;
	this->height = height;
	this->moveX = 0;
	this->moveY = 0;
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

	//init ebo
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);

	GLint texAttrib = glGetAttribLocation(shaderProgram, "texcoord");
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));

	GLint oriAttrib = glGetAttribLocation(shaderProgram, "orientation");
	glEnableVertexAttribArray(oriAttrib);
	glVertexAttribPointer(oriAttrib, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(4 * sizeof(GLfloat)));

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
		"#version 150 core\n"
		"in vec4 position;\n"
		"in vec2 texcoord;\n"
		"in vec2 orientation;\n"
		"out vec2 Texcoord;\n"
		"out vec2 Orientation;\n"
		"void main() {\n"
		"	gl_Position = position;\n"
		"	Texcoord = texcoord;\n"
		"	Orientation = orientation;\n"
		"}";

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	GLint bufflen = 0;
  	glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &bufflen);
	GLchar* log_string = new char[bufflen + 1];
	glGetShaderInfoLog(vertexShader, bufflen, 0, log_string);
	printf("%s\n", log_string);
	delete log_string;
}

void Render::initFragmentShader() {
	fragmentSource =
		"#version 150 core\n"
		"in vec2 Texcoord;\n"
		"in vec2 Orientation;\n"
		"out vec4 outColor;\n"
		"uniform sampler2D tex;\n"
		"void main() {\n"
		"	vec2 v = vec2(Texcoord[0]*(1-Orientation[0])+Orientation[1]*Orientation[0], Texcoord[1]);\n"
		"	outColor = texture(tex, v);\n"
		"}";

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	GLint bufflen = 0;
  	glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &bufflen);
	GLchar* log_string = new char[bufflen + 1];
	glGetShaderInfoLog(fragmentShader, bufflen, 0, log_string);
	printf("%s\n", log_string);
	delete log_string;
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
	int windowX = Window::getHeight(), windowY = Window::getWidth();

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
void Render::addImage(int x, int y, const Coords& coords, int offX, int offY) {
	int windowX = Window::getHeight(), windowY = Window::getWidth();

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

void Render::addImage(int x, int y, const Coords& coords) {
	int 	offX = coords.endX-coords.beginX,
		offY = coords.endY-coords.beginY;

	addImage(x, y, coords, offX, offY);
}

void Render::setMovement(int moveX, int moveY) {
	this->moveX = moveX;
	this->moveY = moveY;
}

void Render::genElements(int max) {
	int offset = 0;
	elements.resize(0);

	for (int i = 0; i < max; i++) {
		elements.push_back(i);

		if (i%4==3) {
			elements.push_back(i);
			elements.push_back(i+1);
		}
	}

	return;
}

//renders the vertices at the given fps
void Render::render(int fps, Level& level) {
	int numDraw = level.getDrawVert().size();

	genElements(numDraw/5+1);

	glBufferData(GL_ARRAY_BUFFER, numDraw*sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (numDraw/10*3-1)*sizeof(GLuint), &elements[0], GL_DYNAMIC_DRAW);

	int windowX = Window::getHeight(), windowY = Window::getWidth();
	double delay = 1.0/fps;

	while (!glfwWindowShouldClose(Window::getWindow()))
	{
		double currentTime = glfwGetTime();

		if (currentTime - lastTime >= delay) {
			if (numDraw < level.getDrawVert().size()) {
				numDraw = level.getDrawVert().size();

				genElements(numDraw*4+1);

				glBufferData(GL_ARRAY_BUFFER, numDraw*sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, (numDraw/10*3-1)*sizeof(GLuint), &elements[0], GL_DYNAMIC_DRAW);
			}

			lastTime = currentTime;
			glfwPollEvents();

			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			level.step(fps);

			glBufferSubData(GL_ARRAY_BUFFER, 0, level.getDrawVert().size()*sizeof(GLfloat), &level.getDrawVert()[0]);

			glDrawElements(GL_TRIANGLE_STRIP, level.getDrawVert().size()/10*3-1, GL_UNSIGNED_INT, 0);

			glfwSwapBuffers(Window::getWindow());
		}
	}
	
	glfwTerminate();
}
