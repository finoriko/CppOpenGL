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
	unsigned int type;
	GLint textureUnit;
public:
	Texture(const char* fileName,GLenum type,GLint texture_unit)
	{
		this->type = type;
		this->textureUnit = texture_unit;
		//Texture 1
		unsigned char* image = SOIL_load_image(fileName, &this->width, &this->height, NULL, SOIL_LOAD_RGBA);


		glGenTextures(1, &this->id);
		glBindTexture(type, this->id);

		glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		if (image)
		{
			glTexImage2D(type, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
			glGenerateMipmap(type);
		}
		else
		{
			std::cout << "ERROR::TEXTURE::TEXTURE_LOADING_FAILED" << std::endl;
		}

		glActiveTexture(0);
		glBindTexture(type, 0);
		SOIL_free_image_data(image);
	}

	~Texture()
	{
		glDeleteTextures(1, &this->id);
	}

	inline GLuint getID() const
	{
		return this->id;
	}
	void bind()
	{
		glActiveTexture(GL_TEXTURE0 + this->textureUnit);
		glBindTexture(this->type, this->id);
	}
	void unbind()
	{
		glActiveTexture(0);
		glBindTexture(this->type, 0);
	}

	inline GLint getTextureUnit() const
	{
		return this->textureUnit;
	}

	void loadFromFile(const char* fileName)
	{
		if (this->id)
		{
			glDeleteTextures(1, &this->id);
		}
		unsigned char* image = SOIL_load_image(fileName, &this->width, &this->height, NULL, SOIL_LOAD_RGBA);


		glGenTextures(1, &this->id);
		glBindTexture(type, this->id);

		glTexParameteri(this->type, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(this->type, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(this->type, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(this->type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		if (image)
		{
			glTexImage2D(this->type, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
			glGenerateMipmap(this->type);
		}
		else
		{
			std::cout << "ERROR::TEXTURE::LOADFROMFILE::TEXTURE_LOADING_FAILED" << std::endl;
		}

		glActiveTexture(0);
		glBindTexture(this->type, 0);
		SOIL_free_image_data(image);
	}
	
};