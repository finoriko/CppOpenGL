#include "libs.h"

Vertex vertices[] =
{
	////position							   //color						 //Texcoords
	//glm::vec3(-0.5f,0.5f,0.0f),			   glm::vec3(1.0f,0.0f,0.0f),	 glm::vec2(0.0f,1.0f),  //직각 삼각형
	//glm::vec3(-0.5f,-0.5f,0.0f),		   glm::vec3(0.0f,1.0f,0.0f),	 glm::vec2(0.0f,0.0f),
	//glm::vec3(0.5f,-0.5f,0.0f),			   glm::vec3(0.0f,0.0f,1.0f),	 glm::vec2(1.0f,0.0f),

	////Position							   //Color						 //Texcoords
	//glm::vec3(0.0f,0.5f,0.0f),			   glm::vec3(1.0f,0.0f,0.0f),	 glm::vec2(0.0f,1.0f), //정 삼각형
	//glm::vec3(-0.5f,-0.5f,0.0f),		   glm::vec3(0.0f,1.0f,0.0f),	 glm::vec2(0.0f,0.0f),
	//glm::vec3(0.5f,-0.5f,0.0f),			   glm::vec3(0.0f,0.0f,1.0f),	 glm::vec2(1.0f,0.0f),

	////Position							   //Color						 //Texcoords
	//glm::vec3(-0.5f,0.5f,0.0f),			   glm::vec3(1.0f,0.0f,0.0f),	 glm::vec2(0.0f,1.0f), //위쪽 직각 삼각형
	//glm::vec3(0.5f,-0.5f,0.0f),		   glm::vec3(0.0f,0.0f,1.0f),	 glm::vec2(1.0f,0.0f),
	//glm::vec3(0.5f,0.5f,0.0f),			   glm::vec3(1.0f,1.0f,0.0f),	 glm::vec2(0.0f,0.0f),

	glm::vec3(-0.5f,0.5f,0.0f),			   glm::vec3(1.0f,0.0f,0.0f),	 glm::vec2(0.0f,1.0f),  //직각 삼각형
	glm::vec3(-0.5f,-0.5f,0.0f),		   glm::vec3(0.0f,1.0f,0.0f),	 glm::vec2(0.0f,0.0f),
	glm::vec3(0.5f,-0.5f,0.0f),			   glm::vec3(0.0f,0.0f,1.0f),	 glm::vec2(1.0f,0.0f),
	glm::vec3(0.5f,0.5f,0.0f),			   glm::vec3(1.0f,1.0f,0.0f),	 glm::vec2(0.0f,0.0f),

};
unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

GLuint indices[] =
{
	0,1,2,//Triangle1
	0,2,3,//Triangle2
};
unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);

void updateInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

void frambuffer_resize_callback(GLFWwindow* window, int fbw, int fbh)
{
	glViewport(0, 0, fbw, fbh);
}
bool loadShaders(GLuint& program)
{
	bool loadSuccess = true;
	char infolog[512];
	GLint success;

	std::string temp = "";
	std::string src = "";

	std::ifstream in_file;

	//Vertex
	in_file.open("vertex_core.glsl");

	if (in_file.is_open())
	{
		while (std::getline(in_file, temp))
		{
			src += temp + "\n";
		}
	}
	else
	{
		std::cout << "ERROR::LOADSHADERS::COULD_NOT_OPEN_VERTEXT_FILE" << std::endl;
		loadSuccess = false;
	}
	in_file.close();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const GLchar* vertSrc = src.c_str();
	glShaderSource(vertexShader, 1, &vertSrc, NULL);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infolog);
		std::cout << "ERROR::LOADSHADERS::COULD_NOT_OPEN_VERTEXT_FILE" << std::endl;

		std::cout << infolog << std::endl;
		loadSuccess = false;
	}

	temp = "";
	src = "";
	//Fragment

	in_file.open("fragment_core.glsl");

	if (in_file.is_open())
	{
		while (std::getline(in_file, temp))
		{
			src += temp + "\n";
		}
	}
	else
	{
		std::cout << "ERROR::LOADSHADERS::COULD_NOT_OPEN_FRAGMENT_FILE" << std::endl;
		loadSuccess = false;

	}
	in_file.close();

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar* fragSrc = src.c_str();
	glShaderSource(fragmentShader, 1, &fragSrc, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infolog);
		std::cout << "ERROR::LOADSHADERS::COULD_NOT_OPEN_FRAGMENT_FILE" << std::endl;

		std::cout << infolog << std::endl;
		loadSuccess = false;

	}

	//Program
	program = glCreateProgram();

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(program, 512, NULL, infolog);
		std::cout << "ERROR::LOADSHADERS::COULD_NOT_OPEN_FRAGMENT_FILE" << std::endl;

		std::cout << infolog << std::endl;
		loadSuccess = false;

	}

	//End
	glUseProgram(0);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return loadSuccess;
}

int main()
{
	//Init GLFW
	glfwInit();

	//Create Window
	const int WINDOW_WIDTH = 640;
	const int WINDOW_HEIGHT = 480;
	int framebufferWidth = 0;
	int framebufferHeight = 0;

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); //메이저 버전
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4); // 마이너 버전
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE); //gl_flase 하면 리사이즈 안됨

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "CppOpenGL", NULL, NULL); //윈도우 크기와 창 이름

	glfwSetFramebufferSizeCallback(window, frambuffer_resize_callback); //크기 변경을 해주는 콜백 크기에 따라 프레임 버퍼도 다르게 해준다

	//glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
	//glViewport(0, 0, framebufferWidth, framebufferHeight);

	glfwMakeContextCurrent(window);


	//init glew(needs window and opengl context

	glewExperimental = GL_TRUE;

	//Error
	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW FAILED" << std::endl;
		glfwTerminate();
	}

	//Opengl Options
	glEnable(GL_DEPTH_TEST);


	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//SHADER INIT
	GLuint core_program;
	if (!loadShaders(core_program))
	{
		glfwTerminate();
	}

	//MODEL

	//VAO , VBO , EBO
	//GEN VAO AND BIND
	GLuint VAO;
	glCreateVertexArrays(1, &VAO);
	glBindVertexArray(VAO);


	//GEN VBO AND BIND AND SEND DATA
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);



	//GEN EBO AND BIND AND SEND DATA
	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	//SET VERTEXATTRIBPOINTERS AND ENABLE(Input ASSEMBLY)
	/*GLuint attribLoc = glGetAttribLocation(core_program, "vertex_position");
	glVertexAttribPointer(attribLoc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),(GLvoid*)offsetof(Vertex,position));
	glEnableVertexAttribArray(attribLoc);*/

	//Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);
	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);
	//Texcoord
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
	glEnableVertexAttribArray(2);
	//BIND VAO 0

	glBindVertexArray(0);




	//MAIN LOOP
	while (!glfwWindowShouldClose(window))
	{
		//Update Input
		glfwPollEvents();
		//update
		updateInput(window);
		//Draw

		//clear
		glClearColor(0.f, 0.f, 0.f, 1.f); // 색 넣기
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); //초기화

		//use a program
		glUseProgram(core_program);

		//Bind vertex array object
		glBindVertexArray(VAO);

		//draw
		//glDrawArrays(GL_TRIANGLES,0, nrOfVertices);
		glDrawElements(GL_TRIANGLES, nrOfIndices, GL_UNSIGNED_INT, 0);


		//end draw
		glfwSwapBuffers(window);
		glFlush();

	}
	//End of program
	glfwDestroyWindow(window);
	glfwTerminate();

	//Delete program
	glDeleteProgram(core_program);

	//Delete VAO and Buffers


	return 0;
}