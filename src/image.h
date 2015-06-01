//image.h

#ifndef IMAGE_H
#define IMAGE_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <png.h>
#include <cstdio>
#include <iostream>

class Image {
	private:
		void genTexture();

		long width, height;
		png_structp png_ptr;
		png_infop info_ptr;
		png_uint_32 rowbytes;
		unsigned char* image_data;
		GLuint texture;
	public:
		Image(const char* name);
		~Image();

		long getWidth() { return width; }
		long getHeight() { return height; }
		GLuint getTexture() { return texture; }
		unsigned char* getImage_data() { return image_data; }
};

#endif
