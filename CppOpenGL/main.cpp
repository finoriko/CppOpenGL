#include "libs.h"

Vertex vertices[] =
{
	////position							   //color						 //Texcoords
	//glm::vec3(-0.5f,0.5f,0.0f),			   glm::vec3(1.0f,0.0f,0.0f),	 glm::vec2(0.0f,1.0f),  //���� �ﰢ��
	//glm::vec3(-0.5f,-0.5f,0.0f),		   glm::vec3(0.0f,1.0f,0.0f),	 glm::vec2(0.0f,0.0f),
	//glm::vec3(0.5f,-0.5f,0.0f),			   glm::vec3(0.0f,0.0f,1.0f),	 glm::vec2(1.0f,0.0f),

	////Position							   //Color						 //Texcoords
	//glm::vec3(0.0f,0.5f,0.0f),			   glm::vec3(1.0f,0.0f,0.0f),	 glm::vec2(0.0f,1.0f), //�� �ﰢ��
	//glm::vec3(-0.5f,-0.5f,0.0f),		   glm::vec3(0.0f,1.0f,0.0f),	 glm::vec2(0.0f,0.0f),
	//glm::vec3(0.5f,-0.5f,0.0f),			   glm::vec3(0.0f,0.0f,1.0f),	 glm::vec2(1.0f,0.0f),

	////Position							   //Color						 //Texcoords
	//glm::vec3(-0.5f,0.5f,0.0f),			   glm::vec3(1.0f,0.0f,0.0f),	 glm::vec2(0.0f,1.0f), //���� ���� �ﰢ��
	//glm::vec3(0.5f,-0.5f,0.0f),		   glm::vec3(0.0f,0.0f,1.0f),	 glm::vec2(1.0f,0.0f),
	//glm::vec3(0.5f,0.5f,0.0f),			   glm::vec3(1.0f,1.0f,0.0f),	 glm::vec2(0.0f,0.0f),
	////Position							   //Color				     //Texcoords            //Normal
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

void updateInput(GLFWwindow* window,glm::vec3& position, glm::vec3& rotation, glm::vec3& scale)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		position.z -= 0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		position.z += 0.01f;

	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		position.x -= 0.01f;

	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		position.x += 0.01f;

	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		rotation.y -= 1.f;

	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		rotation.y += 1.f;

	}
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
	{
		scale += 0.1f;

	}
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
	{
		scale -= 0.1f;

	}
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
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); //������ ����
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4); // ���̳� ����
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE); //gl_flase �ϸ� �������� �ȵ�

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "CppOpenGL", NULL, NULL); //������ ũ��� â �̸�

	glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
	glfwSetFramebufferSizeCallback(window, frambuffer_resize_callback); //ũ�� ������ ���ִ� �ݹ� ũ�⿡ ���� ������ ���۵� �ٸ��� ���ش�

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
	Shader core_program("vertex_core.glsl","fragment_core.glsl");
	
	//Model Mesh
	Mesh test(vertices, nrOfVertices, indices, nrOfIndices);

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
	//Normal
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(3);
	//BIND VAO 0

	glBindVertexArray(0);

	Texture texture_0("Images/pusheen.png", GL_TEXTURE_2D,0);


	//Texture 1
	Texture texture_1("Images/container.png",GL_TEXTURE_2D,1);
	
	//Material 0
	Material material0(glm::vec3(0.1f), glm::vec3(1.f),glm::vec3(2.f), texture_0.getTextureUnit(), texture_1.getTextureUnit());

	glm::vec3 position(0.f);
	glm::vec3 rotation(0.f);
	glm::vec3 scale(1.f);

	//Init matrices
	glm::mat4 ModelMatrix(1.f);
	ModelMatrix = glm::translate(ModelMatrix, position);
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));
	ModelMatrix = glm::scale(ModelMatrix, scale);

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
	//glUseProgram(core_program);
	//core_program.use();
	core_program.setMat4fv(ModelMatrix, "ModelMatrix");
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
		updateInput(window, position, rotation, scale);


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
		//position.z -= 0.01f;
		//rotation.y += 2.f;

		//Move ,rotate and scale
		ModelMatrix = glm::mat4(1.f);
		ModelMatrix = glm::translate(ModelMatrix, position);
		ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));
		ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));
		ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));
		ModelMatrix = glm::scale(ModelMatrix, scale);

		core_program.setMat4fv(ModelMatrix, "ModelMatrix");

		//glUniformMatrix4fv(glGetUniformLocation(core_program, "ModelMatrix"), 1, GL_FALSE, glm::value_ptr(ModelMatrix));
		glfwGetFramebufferSize(window,&framebufferWidth,&framebufferHeight);

		ProjectionMatrix = glm::mat4(1.f);
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
		glBindVertexArray(VAO);

		//draw
		//glDrawArrays(GL_TRIANGLES,0, nrOfVertices);
		glDrawElements(GL_TRIANGLES, nrOfIndices, GL_UNSIGNED_INT, 0);

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