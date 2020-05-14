#pragma once

#include "libs.h"

//ZOOOOOOOOOOOM IN BEFORE RECORDING!


class Game
{
private:
	//Variables
		//Window
	GLFWwindow* window;
	const int WINDOW_WIDTH;
	const int WINDOW_HEIGHT;
	int framebufferWidth;
	int framebufferHeight;

	//OpenGL Context
	const int GL_VERSION_MAJOR;
	const int GL_VERSION_MINOR;

	//Matrices
	glm::mat4 ViewMatrix;
	glm::vec3 camPosition;
	glm::vec3 worldUp;
	glm::vec3 camFront;

	glm::mat4 ProjectionMatrix;
	float fov;
	float nearPlane;
	float farPlane;
	//Private functions
	void initGLFW();
	void initWindow(
		const char* title,
		bool resizable
	);
	void initGLEW();
	void initOpenGLOptions();
	void initMatrices();
	//Static variables

public:
	//Constructors / Destructors
	Game(
		const char* title,
		const int WINDOW_WIDTH, const int WINDOW_HEIGHT,
		const int GL_VERSION_MAJOR, const int GL_VERSION_MINOR,
		bool resizable
	);
	virtual ~Game();
	//Accessors
	int getWindowShouldClose();
	//Modifiers
	void setWindowShouldClose();
	

	//Functions
	void update();
	void render();
	

	//Static functions
	static void framebuffer_resize_callback(GLFWwindow* window, int fbW, int fbH);
};