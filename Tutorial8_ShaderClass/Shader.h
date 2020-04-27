#pragma once

#include<iostream>
#include<fstream>
#include<string>

#include<GL/glew.h>
#include<GLFW/glfw3.h>

#include<glm.hpp>
#include<vec2.hpp>
#include<vec3.hpp>
#include<vec4.hpp>
#include<mat4x4.hpp>
#include<gtc/type_ptr.hpp>

class Shader
{
private:
	//Member var
	GLuint id;

	//Private fuctions
	std::string loadShaderSource(char* fileName)
	{
		std::string temp = "";
		std::string src = "";

		std::ifstream in_file;

		//Vertex
		in_file.open(fileName); //파일 읽기

		if (in_file.is_open())
		{
			while (std::getline(in_file, temp))
			{
				src += temp + "\n"; //src에 셰이더 파일 읽어온거 넣기
			}
		}
		else
		{
			std::cout << "ERROR::SHADER::COULD_NOT_OPEN_FILE" << fileName << std::endl;
		}
		in_file.close(); // 파일닫기
		return src;
	}




	GLuint loadShader(GLenum type, char* fileName)
	{
		char infolog[512];
		GLint success;

		GLuint shader = glCreateShader(type); //버텍스 셰이더 선언
		std::string str_src = this->loadShaderSource(fileName);
		const GLchar* src = str_src.c_str();
		glShaderSource(shader, 1, &src, NULL); //셰이더 객체에 추가
		glCompileShader(shader); //셰이더 컴파일하기

		glGetShaderiv(shader, GL_COMPILE_STATUS, &success); //셰이더 파일이 성공적으로 완료되었는지 알수 있다.
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, infolog);
			std::cout << "ERROR::SHADERS::COULD_NOT_COMPLIE_SHADER: " << fileName << std::endl;

			std::cout << infolog << std::endl;
		}
		return shader;
	}

	void linkProgram(GLuint vertexShader, GLuint geometryShader, GLuint fragmentShader)
	{
		char infolog[512];
		GLint success;

		this->id = glCreateProgram();
		//glUseProgram(this->id);
		glAttachShader(this->id, vertexShader);

		if (geometryShader)
		{
			glAttachShader(this->id, geometryShader);

		}
		glAttachShader(this->id, fragmentShader);

		glLinkProgram(this->id);
		glGetProgramiv(this->id, GL_LINK_STATUS, &success);

		if (!success)
		{
			glGetProgramInfoLog(this->id, 512, NULL, infolog);
			std::cout << "ERROR::LOADSHADERS::COULD_NOT_OPEN_FRAGMENT_FILE" << std::endl;

			std::cout << infolog << std::endl;

		}

		//End
		glUseProgram(0);
	}

public:

	//Constructors/Destructors
	Shader(char* vertexFilie, char* fragmentFile, char* geometryFile = "")
	{
		GLuint vertexShader = 0;
		GLuint geometryShader = 0;
		GLuint fragmentShader = 0;

		vertexShader = loadShader(GL_VERTEX_SHADER, vertexFilie);

		if (geometryFile != "")
		{
			geometryShader = loadShader(GL_GEOMETRY_SHADER, geometryFile);
		}
		fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentFile);
		this->linkProgram(vertexShader, geometryShader, fragmentShader);

		glDeleteShader(vertexShader);
		glDeleteShader(geometryShader);
		glDeleteShader(fragmentShader);
	}
	~Shader()
	{
		glDeleteProgram(this->id);
	}
	//void use()
	//{
	//	glUseProgram(this->id);
	//}
	//void unuse()
	//{
	//	glUseProgram(0);
	//}
	//void set1i(GLint value, const GLchar* name)
	//{
	//	this->use();

	//	glUniform1i(glGetUniformLocation(this->id, name), value); //조심 fv가 아님

	//	this->unuse();
	//}
	//void set1f(GLfloat value, const GLchar* name)
	//{
	//	this->use();
	//	glUniform1f(glGetUniformLocation(this->id, name), value); //조심 fv가 아님

	//	this->unuse();
	//}
	//void setVec2f(glm::fvec2 value, const GLchar* name)
	//{
	//	this->use();
	//	glUniform2fv(glGetUniformLocation(this->id,name), 1, glm::value_ptr(value));

	//	this->unuse();
	//}
	//void setVec3f(glm::fvec3 value, const GLchar* name)
	//{
	//	this->use();

	//	glUniform3fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));

	//	this->unuse();
	//}
	//void setVec4f(glm::fvec4 value, const GLchar* name)
	//{
	//	this->use();

	//	glUniform4fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));

	//	this->unuse();
	//}
	//void setMat3fv(glm::mat3 value, const GLchar* name, GLboolean transpose = GL_FALSE)
	//{
	//	this->use();

	//	glUniformMatrix3fv(glGetUniformLocation(this->id, name), 1, transpose, glm::value_ptr(value));

	//	this->unuse();
	//}
	//void setMat4fv(glm::mat4 value, const GLchar* name,GLboolean transpose = GL_FALSE)
	//{
	//	this->use();
	//	glUniformMatrix4fv(glGetUniformLocation(this->id, name), 1, transpose, glm::value_ptr(value));

	//	this->unuse();
	//}
	void use()
	{
		glUseProgram(this->id);
	}

	void unuse()
	{
		glUseProgram(0);
	}

	void set1i(GLint value, const GLchar* name)
	{
		this->use();

		glUniform1i(glGetUniformLocation(this->id, name), value);

		this->unuse();
	}

	void set1f(GLfloat value, const GLchar* name)
	{
		this->use();

		glUniform1f(glGetUniformLocation(this->id, name), value);

		this->unuse();
	}

	void setVec2f(glm::fvec2 value, const GLchar* name)
	{
		this->use();

		glUniform2fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));

		this->unuse();
	}

	void setVec3f(glm::fvec3 value, const GLchar* name)
	{
		this->use();

		glUniform3fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));

		this->unuse();
	}

	void setVec4f(glm::fvec4 value, const GLchar* name)
	{
		this->use();

		glUniform4fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));

		this->unuse();
	}

	void setMat3fv(glm::mat3 value, const GLchar* name, GLboolean transpose = GL_FALSE)
	{
		this->use();

		glUniformMatrix3fv(glGetUniformLocation(this->id, name), 1, transpose, glm::value_ptr(value));

		this->unuse();
	}

	void setMat4fv(glm::mat4 value, const GLchar* name, GLboolean transpose = GL_FALSE)
	{
		this->use();

		glUniformMatrix4fv(glGetUniformLocation(this->id, name), 1, transpose, glm::value_ptr(value));

		this->unuse();
	}
};