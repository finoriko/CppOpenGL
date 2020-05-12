#include "Game.h"

Vertex vertices[] =
{
	glm::vec3(-0.5f,0.5f,0.0f),			   glm::vec3(1.0f,0.0f,0.0f),	 glm::vec2(0.0f,1.0f),  glm::vec3(0.0f,0.0f,1.0f), //���� �ﰢ��
	glm::vec3(-0.5f,-0.5f,0.0f),		   glm::vec3(0.0f,1.0f,0.0f),	 glm::vec2(0.0f,0.0f),  glm::vec3(0.0f,0.0f,1.0f),
	glm::vec3(0.5f,-0.5f,0.0f),			   glm::vec3(0.0f,0.0f,1.0f),	 glm::vec2(1.0f,0.0f),  glm::vec3(0.0f,0.0f,1.0f),
	glm::vec3(0.5f,0.5f,0.0f),			   glm::vec3(1.0f,1.0f,0.0f),	 glm::vec2(1.0f,1.0f),  glm::vec3(0.0f,0.0f,1.0f),

};
unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

GLuint indices[] =
{
	0,1,2,//Triangle1
	0,2,3,//Triangle2
};
unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint); //����

void updateInput(GLFWwindow* window) //Ű�Է� esc�� ������ ����
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

void frambuffer_resize_callback(GLFWwindow* window, int fbw, int fbh) //����� ���� �׸��� ������ �ٲ�
{
	glViewport(0, 0, fbw, fbh);
}

void updateInput(GLFWwindow* window,Mesh &mesh)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		mesh.move(glm::vec3(0.f, 0.f, -0.01f));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		mesh.move(glm::vec3(0.f, 0.f, 0.01f));
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		mesh.move(glm::vec3(-0.01f, 0.f, 0.0f));
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		mesh.move(glm::vec3(0.01f, 0.f, 0.0f));
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		mesh.rotate(glm::vec3(0.f, -1.f, 0.0f));
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		mesh.rotate(glm::vec3(0.f, 1.f, 0.0f));
	}
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
	{
		mesh.scaleUp(glm::vec3(1.f));
	}
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
	{
		mesh.scaleUp(glm::vec3(-1.f));
	}
}

GLFWwindow* createWindow(
	const char* title,
	const int width, const int height,
	int& fbwidth, int& fbHeight,
	const int GLmajorver,const int GLminorVer,
	bool resizable)
{

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GLmajorver); //������ ����
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GLminorVer); // ���̳� ����
	glfwWindowHint(GLFW_RESIZABLE, resizable); //gl_flase �ϸ� �������� �ȵ�

	GLFWwindow* window = glfwCreateWindow(width, height, "CppOpenGL", NULL, NULL); //������ ũ��� â �̸�

	glfwGetFramebufferSize(window, &fbwidth, &fbHeight);
	glfwSetFramebufferSizeCallback(window, frambuffer_resize_callback); //ũ�� ������ ���ִ� �ݹ� ũ�⿡ ���� ������ ���۵� �ٸ��� ���ش�

	//glViewport(0, 0, framebufferWidth, framebufferHeight);

	glfwMakeContextCurrent(window);

	return window;
}


int main()
{
	//Init GLFW
	glfwInit();


	const int GLmajorVersion = 4;
	const int GLminorVersion = 4;
	//Create Window
	const int WINDOW_WIDTH = 640;
	const int WINDOW_HEIGHT = 480;
	int framebufferWidth = WINDOW_WIDTH;
	int framebufferHeight = WINDOW_HEIGHT;



	//init glew(needs window and opengl context
	GLFWwindow* window = createWindow("CppOpenGL",WINDOW_WIDTH,WINDOW_HEIGHT,framebufferWidth,framebufferHeight, GLmajorVersion, GLminorVersion,false);
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
	Shader core_program(GLmajorVersion,GLminorVersion,"vertex_core.glsl","fragment_core.glsl");
	
	//Model Mesh
	Mesh test(&Quad(),
		glm::vec3(0.f),
		glm::vec3(0.f),
		glm::vec3(1.f)
		);

	Texture texture_0("Images/pusheen.png", GL_TEXTURE_2D,0);


	//Texture 1
	Texture texture_1("Images/container.png",GL_TEXTURE_2D,1);
	
	//Material 0
	Material material0(glm::vec3(0.1f), glm::vec3(1.f),glm::vec3(2.f), texture_0.getTextureUnit(), texture_1.getTextureUnit());

	
	glm::vec3 camPosition(0.f,0.f,1.f);
	glm::vec3 worldUp(0.f, 1.f, 0.f);
	glm::vec3 camFront(0.f, 0.f, -1.f);

	glm::mat4 ViewMatrix(1.f);
	ViewMatrix = glm::lookAt(camPosition, camPosition + camFront, worldUp);

	float fov = 90.f;
	float nearPlane = 0.1f;
	float farPlane = 1000.f;
	glm::mat4 ProjectionMatrix(1.f);

	ProjectionMatrix = glm::perspective(glm::radians(fov), static_cast<float>(framebufferWidth) / framebufferHeight,nearPlane,farPlane );

	//Lights
	glm::vec3 lightPos0(0.f, 0.f, 1.f);

	//init uniforms
	core_program.setMat4fv(ViewMatrix, "ViewMatrix");
	core_program.setMat4fv(ProjectionMatrix, "ProjectionMatrix");

	core_program.setVec3f(lightPos0, "lightPos0");
	core_program.setVec3f(camPosition, "cameraPos");

	glUseProgram(0);

	//MAIN LOOP
	while (!glfwWindowShouldClose(window))
	{
		//Update Input
		glfwPollEvents();
		updateInput(window, test);


		//update
		updateInput(window);
		//Draw

		//clear
		glClearColor(0.f, 0.f, 0.f, 1.f); // �� �ֱ�
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); //�ʱ�ȭ

		//use a program
		//glUseProgram(core_program);
		core_program.set1i(texture_0.getTextureUnit(), "texture0");
		core_program.set1i(texture_1.getTextureUnit(), "texture1");
		material0.sendToShader(core_program);

		//glUniformMatrix4fv(glGetUniformLocation(core_program, "ModelMatrix"), 1, GL_FALSE, glm::value_ptr(ModelMatrix));
		glfwGetFramebufferSize(window,&framebufferWidth,&framebufferHeight);

		ProjectionMatrix = glm::perspective(glm::radians(fov), static_cast<float>(framebufferWidth) / framebufferHeight, nearPlane, farPlane);

		core_program.setMat4fv(ProjectionMatrix, "ProjectionMatrix");
		//glUniformMatrix4fv(glGetUniformLocation(core_program, "ProjectionMatrix"), 1, GL_FALSE, glm::value_ptr(ProjectionMatrix));

		core_program.use();

		//Activate texture
		/*glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture0);*/
		texture_0.bind();
		texture_1.bind();
		//Bind vertex array object

		//draw
		test.render(&core_program);

		//end draw
		glfwSwapBuffers(window);
		glFlush();

		glBindVertexArray(0);
		glUseProgram(0);
		glActiveTexture(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	//End of program
	glfwDestroyWindow(window);
	glfwTerminate();



	//Delete VAO and Buffers


	return 0;
}