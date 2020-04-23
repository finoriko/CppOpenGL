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
		in_file.open(fileName); //���� �б�

		if (in_file.is_open())
		{
			while (std::getline(in_file, temp))
			{
				src += temp + "\n"; //src�� ���̴� ���� �о�°� �ֱ�
			}
		}
		else
		{
			std::cout << "ERROR::SHADER::COULD_NOT_OPEN_FILE"<<fileName << std::endl;
		}
		in_file.close(); // ���ϴݱ�
		return src;
	}

	


	GLuint loadShader(GLenum type, char* fileName)
	{
		char infolog[512];
		GLint success;

		GLuint shader = glCreateShader(GL_VERTEX_SHADER); //���ؽ� ���̴� ����
		std::string str_src = this->loadShaderSource(fileName);
		const GLchar* src = str_src.c_str();
		glShaderSource(shader, 1, &src, NULL); //���̴� ��ü�� �߰�
		glCompileShader(shader); //���̴� �������ϱ�

		glGetShaderiv(shader, GL_COMPILE_STATUS, &success); //���̴� ������ ���������� �Ϸ�Ǿ����� �˼� �ִ�.
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