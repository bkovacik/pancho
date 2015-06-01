#include "image.h"

Image::Image(const char* name) {
	FILE* image;
	image = fopen(name, "rb");

	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	info_ptr = png_create_info_struct(png_ptr);

	png_init_io(png_ptr, image);
	png_read_info(png_ptr, info_ptr);

	this->width = png_get_image_width(png_ptr, info_ptr);
	this->height = png_get_image_height(png_ptr, info_ptr);
	this->rowbytes = png_get_rowbytes(png_ptr, info_ptr);

	image_data = (unsigned char*) malloc(rowbytes*height);
	png_byte this_is_a_byte;

	png_byte* row_pointers[height];
	for (png_uint_32 i = 0;  i < height;  i++)
        	row_pointers[i] = image_data + i*rowbytes;

	//populates image_data
	png_read_image(png_ptr, row_pointers);

	fclose(image);

	genTexture();
}

Image::~Image() {
	free(image_data);
	png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
}

void Image::genTexture() {
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_data);

	//sprites should fit objects perfectly, so no need for filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	float color[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);

}
