#include "Game.h"



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
	Game game("C++ OpenGL", 640, 480, 4, 5, false);

	
	//Material 0

	

	//Lights

	//MAIN LOOP
	while (!game.getWindowShouldClose())
	{
		//Update Input
		game.update();
		game.render();

	}
	//End of program



	//Delete VAO and Buffers


	return 0;
}