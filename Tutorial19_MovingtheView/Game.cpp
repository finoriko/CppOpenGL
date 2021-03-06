#include "Game.h"

//Private functions
void Game::initGLFW()
{
	//INIT GLFW
	if (glfwInit() == GLFW_FALSE)
	{
		std::cout << "ERROR::GLFW_INIT_FAILED" << "\n";
		glfwTerminate();
	}
}

void Game::initWindow(
	const char* title,
	bool resizable
)
{
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, this->GL_VERSION_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, this->GL_VERSION_MINOR);
	glfwWindowHint(GLFW_RESIZABLE, resizable);

	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); MAC OS

	this->window = glfwCreateWindow(this->WINDOW_WIDTH, this->WINDOW_HEIGHT, title, NULL, NULL);

	if (this->window == nullptr)
	{
		std::cout << "ERROR::GLFW_WINDOW_INIT_FAILED" << "\n";
		glfwTerminate();
	}

	glfwGetFramebufferSize(this->window, &this->framebufferWidth, &this->framebufferHeight);
	glfwSetFramebufferSizeCallback(window, Game::framebuffer_resize_callback);
	//IMPORTANT WHITH PERSPECTIVE MATRIX!!!

	//glViewport(0, 0, framebufferWidth, framebufferHeight);

	glfwMakeContextCurrent(this->window); //IMPORTANT!!
}

void Game::initGLEW()
{
	glewExperimental = GL_TRUE;

	//Error
	if (glewInit() != GLEW_OK)
	{
		std::cout << "ERROR::MAIN.CPP::GLEW_INIT_FAILED" << "\n";
		glfwTerminate();
	}
}

void Game::initOpenGLOptions()
{
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//Input
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Game::initMatrices()
{
	this->ViewMatrix = glm::mat4(1.f);
	this->ViewMatrix = glm::lookAt(this->camPosition, this->camPosition + this->camFront, this->worldUp);

	this->ProjectionMatrix = glm::mat4(1.f);
	this->ProjectionMatrix = glm::perspective(
		glm::radians(this->fov),
		static_cast<float>(this->framebufferWidth) / this->framebufferHeight,
		this->nearPlane,
		this->farPlane
	);
}

void Game::initShaders()
{
	this->shaders.push_back(new Shader(this->GL_VERSION_MAJOR, this->GL_VERSION_MINOR,
		"vertex_core.glsl", "fragment_core.glsl"));
}

void Game::initTextures()
{

	//TEXTURE 0
	this->textures.push_back(new Texture("Images/pusheen.png", GL_TEXTURE_2D));
	this->textures.push_back(new Texture("Images/pusheen_specular.png", GL_TEXTURE_2D));

	//TEXTURE 1
	this->textures.push_back(new Texture("Images/container.png", GL_TEXTURE_2D));
	this->textures.push_back(new Texture("Images/container_specular.png", GL_TEXTURE_2D));

}

void Game::initMaterials()
{
	this->materials.push_back(new Material(glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(1.f),
		0, 1));
}

void Game::initMeshes()
{
	this->meshes.push_back(new Mesh(&Pyramid(),
		glm::vec3(0.f),
		glm::vec3(0.f),
		glm::vec3(1.f)
	));
	this->meshes.push_back(
		new Mesh(
			&Quad(),
			glm::vec3(0.f),
			glm::vec3(0.f),
			glm::vec3(1.f)
		)
	);
}
void Game::initLights()
{
	this->lights.push_back(new glm::vec3(0.f, 0.f, 1.f));
}

void Game::initUniforms()
{
	//INIT UNIFORMS
	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(ViewMatrix, "ViewMatrix");
	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(ProjectionMatrix, "ProjectionMatrix");

	this->shaders[SHADER_CORE_PROGRAM]->setVec3f(*this->lights[0], "lightPos0");
	this->shaders[SHADER_CORE_PROGRAM]->setVec3f(this->camPosition, "cameraPos");
}
void Game::updateUniforms()
{
	//update view matrix(camera)
	this->ViewMatrix = glm::lookAt(this->camPosition, this->camPosition + this->camFront, this->worldUp);

	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(ViewMatrix, "ViewMatrix");

	glfwGetFramebufferSize(this->window, &this->framebufferWidth, &this->framebufferHeight);

	ProjectionMatrix = glm::perspective(
		glm::radians(fov),
		static_cast<float>(framebufferWidth) / framebufferHeight,
		nearPlane,
		farPlane
	);

	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(ProjectionMatrix, "ProjectionMatrix");

	
}

//Constructors / Destructors
Game::Game(
	const char* title,
	const int WINDOW_WIDTH, const int WINDOW_HEIGHT,
	const int GL_VERSION_MAJOR, const int GL_VERSION_MINOR,
	bool resizable
)
	:
	WINDOW_WIDTH(WINDOW_WIDTH),
	WINDOW_HEIGHT(WINDOW_HEIGHT),
	GL_VERSION_MAJOR(GL_VERSION_MAJOR),
	GL_VERSION_MINOR(GL_VERSION_MINOR)
{
	//Init variables
	this->window = nullptr;
	this->framebufferWidth = this->WINDOW_WIDTH;
	this->framebufferHeight = this->WINDOW_HEIGHT;

	this->camPosition = glm::vec3(0.f, 0.f, 1.f);
	this->worldUp = glm::vec3(0.f, 1.f, 0.f);
	this->camFront = glm::vec3(0.f, 0.f, -1.f);

	this->ViewMatrix = glm::mat4(1.f);
	this->ViewMatrix = glm::lookAt(this->camPosition, this->camPosition + this->camFront, this->worldUp);

	this->fov = 90.f;
	this->nearPlane = 0.1f;
	this->farPlane = 1000.f;

	this->ProjectionMatrix = glm::mat4(1.f);
	this->ProjectionMatrix = glm::perspective(
		glm::radians(this->fov),
		static_cast<float>(this->framebufferWidth) / this->framebufferHeight,
		this->nearPlane,
		this->farPlane
	);

	this->initGLFW();
	this->initWindow(title, resizable);
	this->initGLEW();
	this->initOpenGLOptions();

	this->initMatrices();
	this->initShaders();
	this->initTextures();
	this->initMaterials();
	this->initMeshes();
	this->initLights();
	this->initUniforms();
}

Game::~Game()
{
	glfwDestroyWindow(this->window);
	glfwTerminate();
	for (size_t i = 0; i < this->shaders.size(); i++)
		delete this->shaders[i];

	for (size_t i = 0; i < this->textures.size(); i++)
		delete this->textures[i];

	for (size_t i = 0; i < this->materials.size(); i++)
		delete this->materials[i];

	for (size_t i = 0; i < this->meshes.size(); i++)
		delete this->meshes[i];
	for (size_t i = 0; i < this->lights.size(); i++)
		delete this->lights[i];
}
int Game::getWindowShouldClose()
{
	return glfwWindowShouldClose(this->window);
}
//Modifier
void Game::setWindowShouldClose()
{
	glfwSetWindowShouldClose(this->window, GLFW_TRUE);
}
//Functions




void Game::updateInput()
{
	//Program
	if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(this->window, GLFW_TRUE);
	}
	//Cameara
	if (glfwGetKey(this->window, GLFW_KEY_W) == GLFW_PRESS)
	{
		this->camPosition.z -= 0.05f;
	}
	if (glfwGetKey(this->window, GLFW_KEY_S) == GLFW_PRESS)
	{
		this->camPosition.z += 0.05f;
	}
	if (glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS)
	{
		this->camPosition.x -= 0.05f;
	}
	if (glfwGetKey(this->window, GLFW_KEY_D) == GLFW_PRESS)
	{
		this->camPosition.x += 0.05f;
	}
	if (glfwGetKey(this->window, GLFW_KEY_C) == GLFW_PRESS)
	{
		this->camPosition.y -= 0.05f;
	}
	if (glfwGetKey(this->window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		this->camPosition.y += 0.05f;
	}
}

void Game::update()
{
	//Update Input
	glfwPollEvents();
	this->updateInput();
	/*Game::updateInput(this->window);
	Game::updateInput(this->window, *this->meshes[MESH_QUAD]);*/
}

void Game::render()
{
	//UPDATE --- 
	//updateInput(window);


	//update
	//Draw

	//clear
	glClearColor(0.f, 0.f, 0.f, 1.f); // 색 넣기
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); //초기화

	//use a program
	//glUseProgram(core_program);
	//this->shaders[SHADER_CORE_PROGRAM]->set1i(0, "texture0");
	//this->shaders[SHADER_CORE_PROGRAM]->set1i(1, "texture1");
	
	this->updateUniforms();

	this->materials[MAT_1]->sendToShader(*this->shaders[SHADER_CORE_PROGRAM]);

	//this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(ProjectionMatrix, "ProjectionMatrix");
	//glUniformMatrix4fv(glGetUniformLocation(core_program, "ProjectionMatrix"), 1, GL_FALSE, glm::value_ptr(ProjectionMatrix));

	this->shaders[SHADER_CORE_PROGRAM]->use();

	//Activate texture
	/*glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture0);*/
	//this->textures[TEX_PUSHEEN]->bind(0);
	//this->textures[TEX_PUSHEEN_SPECULAR]->bind(1);
	////Bind vertex array object

	////draw
	//this->meshes[MESH_QUAD]->render(this->shaders[SHADER_CORE_PROGRAM]);

	this->textures[TEX_CONTAINER]->bind(0);
	this->textures[TEX_CONTAINER_SPECULAR]->bind(1);

	this->meshes[MESH_QUAD]->render(this->shaders[SHADER_CORE_PROGRAM]);

	//end draw
	glfwSwapBuffers(window);
	glFlush();

	glBindVertexArray(0);
	glUseProgram(0);
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}



//Static functions
void Game::framebuffer_resize_callback(GLFWwindow* window, int fbW, int fbH)
{
	glViewport(0, 0, fbW, fbH);
}
//void Game::updateInput(GLFWwindow* window)
//{
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//	{
//		glfwSetWindowShouldClose(window, GLFW_TRUE);
//	}
//};
//
//void Game::updateInput(GLFWwindow* window, Mesh& mesh)
//{
//	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//	{
//		mesh.move(glm::vec3(0.f, 0.f, -0.01f));
//	}
//	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//	{
//		mesh.move(glm::vec3(0.f, 0.f, 0.01f));
//	}
//	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//	{
//		mesh.move(glm::vec3(-0.01f, 0.f, 0.0f));
//	}
//	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//	{
//		mesh.move(glm::vec3(0.01f, 0.f, 0.0f));
//	}
//	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
//	{
//		mesh.move(glm::vec3(0.f, 0.01f, 0.0f));
//	}
//	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
//	{
//		mesh.move(glm::vec3(0.f, -0.01f, 0.0f));
//	}
//	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
//	{
//		mesh.rotate(glm::vec3(0.f, -1.f, 0.0f));
//	}
//	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
//	{
//		mesh.rotate(glm::vec3(0.f, 1.f, 0.0f));
//	}
//	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
//	{
//		mesh.scaleUp(glm::vec3(1.f));
//	}
//	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
//	{
//		mesh.scaleUp(glm::vec3(-1.f));
//	}
//}