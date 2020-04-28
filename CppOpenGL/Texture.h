#pragma once
#include<iostream>
#include<string>

#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<SOIL2.h>

class Texture
{
private:
	GLuint id;
	int width;
	int height;

public:
	Texture()
	{
		//Texture 1
		int image_width1 = 0;
		int image_height1 = 0;
		unsigned char* image1 = SOIL_load_image("Images/wood.png", &image_width1, &image_height1, NULL, SOIL_LOAD_RGBA);


		GLuint texture1;
		glGenTextures(1, &texture1);
		glBindTexture(GL_TEXTURE_2D, texture1);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		if (image1)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width1, image_height1, 0, GL_RGBA, GL_UNSIGNED_BYTE, image1);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "ERROR::TEXTURE_LOADING_FAILED" << std::endl;
		}

		glActiveTexture(0);
		glBindTexture(GL_TEXTURE_2D, 0);
		SOIL_free_image_data(image1);
	}
	~Texture()
	{
		glDeleteTextures(1, &this->id);
	}
};