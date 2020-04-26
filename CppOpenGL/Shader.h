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
			std::cout << "ERROR::SHADER::COULD_NOT_OPEN_FILE"<<fileName << std::endl;
		}
		in_file.close(); // 파일닫기
		return src;
	}

	


	GLuint loadShader(GLenum type, char* fileName)
	{
		char infolog[512];
		GLint success;

		GLuint shader = glCreateShader(GL_VERTEX_SHADER); //버텍스 셰이더 선언
		std::string str_src = this->loadShaderSource(fileName);
		const GLchar* src = str_src.c_str();
		glShaderSource(shader, 1, &src, NULL); //셰이더 객체에 추가
		glCompileShader(shader); //셰이더 컴파일하기

		glGetShaderiv(shader, GL_COMPILE_STATUS, &success); //셰이더 파일이 성공적으로 완료되었는지 알수 있다.
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, infolog);
			std::cout << "ERROR::SHADERS::COULD_NOT_COMPLIE_SHADER: "<<fileName << std::endl;

			std::cout << infolog << std::endl;
		}
		return shader;
	}

	void linkProgram(GLuint vertexShader, GLuint geometryShader, GLuint fragmentShader)
	{
		char infolog[512];
		GLint success;

		this->id = glCreateProgram();

		glAttachShader(this->id, vertexShader);


	}

public:

	//Constructors/Destructors
	Shader(char* vertexFilie, char* fragmentFile, char* geometryFile = "")
	{

	}
	~Shader()
	{
		glDeleteProgram(this->id);
	}

};