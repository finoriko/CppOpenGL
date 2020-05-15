#include "Game.h"



void updateInput(GLFWwindow* window) //키입력 esc를 누르면 꺼짐
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

void frambuffer_resize_callback(GLFWwindow* window, int fbw, int fbh) //사이즈에 따라서 그리는 영역이 바뀜
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
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GLmajorver); //메이저 버전
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GLminorVer); // 마이너 버전
	glfwWindowHint(GLFW_RESIZABLE, resizable); //gl_flase 하면 리사이즈 안됨

	GLFWwindow* window = glfwCreateWindow(width, height, "CppOpenGL", NULL, NULL); //윈도우 크기와 창 이름

	glfwGetFramebufferSize(window, &fbwidth, &fbHeight);
	glfwSetFramebufferSizeCallback(window, frambuffer_resize_callback); //크기 변경을 해주는 콜백 크기에 따라 프레임 버퍼도 다르게 해준다

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