#include<iostream>
#include"Shader.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include<GLFW/glfw3.h>
// GLM �������� ��
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include"Camera.h"

// ���ݵ�����
#pragma region Model Data 
float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

unsigned int indices[] = { // ��������
	0,1,2,
	2,3,0
};

glm::vec3 cubePositions[] = {
  glm::vec3(0.0f,  0.0f,  0.0f),
  glm::vec3(2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3(2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3(1.3f, -2.0f, -2.5f),
  glm::vec3(1.5f,  2.0f, -2.5f),
  glm::vec3(1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
};   // ������λ��
 
#pragma endregion

#pragma region Camera Declare
// Instantiate Camera class
Camera camera(glm::vec3(0, 0, 3.0f), glm::radians(-15.f), glm::radians(180.0f), glm::vec3(0, 1.0f, 0.0f));
#pragma endregion

#pragma region  Input Declare
// ǰһ�ε�x�� y����
float lastX;
float lastY;
bool firstMouse = true;

using namespace std;
// �Զ��崦����������
void processInput(GLFWwindow * window);

void mouse_callback(GLFWwindow* window, double xPos, double yPos);
#pragma endregion


// �ַ������д�����ַ����ַ��������ƵĶ����� string.c_str()
unsigned int loadImageToGPU(const char* filename, GLint internalFormat, GLenum format, int textureSlot) {

	unsigned int TexBuffer;
	glGenTextures(1, &TexBuffer);
	glActiveTexture(GL_TEXTURE0 + textureSlot);
	glBindTexture(GL_TEXTURE_2D, TexBuffer);
	int width, height, nrChanne;
	stbi_set_flip_vertically_on_load(true);
	unsigned char * data = stbi_load(filename, &width, &height, &nrChanne, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0,internalFormat, width, height, 0, format, 
														GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "load image error." << std::endl;
	}
	stbi_image_free(data);

	return TexBuffer;
}

int main(void) {
	
	#pragma region Open a Window
	//printf("hehihei\n");
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

	// open GLFW Window
	GLFWwindow * window = glfwCreateWindow(1600, 1200, "My OpenGL Game", NULL, NULL);
	// ����һ��GLFW window ����
	if (window == NULL)
	{
		printf("Error in Openwindow.\n");
		glfwTerminate(); // ֹͣ
		return -1;
	}
	glfwMakeContextCurrent(window); // ʹ�����window����
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // �ر��α�
	glfwSetCursorPosCallback(window, mouse_callback);
	// Init GLEW 
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		printf("Error in initing GLEW.\n");
		return -1;
	}
	glViewport(0, 0, 1600, 1200);
	// ��ʼ����shader
	glEnable(GL_DEPTH_TEST);  // ������Ȼ���
	// ��������
#pragma endregion

	#pragma region Init Shader Program
	/*-----------�Զ��� ��ʮ������------------------*/
	Shader* myShader = new Shader("vertexSource.vert", "fragmentSource.frag");
#pragma endregion

	#pragma region Init and Load Model to VAO, VBO
	unsigned int VAO;
	glGenVertexArrays(1, &VAO); // ����һ��VAO δ��VBO
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);  //����һ��VBO�� δ�� Array Buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // ��VBO���� ARRAY Buffer ��
	// �����ݴ�CPU��GPU�Ĵ������� ���Ƶ�GPU������
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// �����ݷ��� Array Bufferͨ��
	glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(6); // ������ ��vbo��vao
	//glVertexAttribPointer(7, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
	//glEnableVertexAttribArray(7); // ��ɫ
	glVertexAttribPointer(8, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(8);  //uv ֵ
	// �������
#pragma endregion

	#pragma region Init and Load Texture
	// create texture buffer
	unsigned int TexBufferA;
	TexBufferA = loadImageToGPU("container.jpg", GL_RGB, GL_RGB, 0);
	unsigned int TexBufferB;
	TexBufferB = loadImageToGPU("awesomeface.png", GL_RGB, GL_RGBA, 0);
#pragma endregion
	
	#pragma region Prepare MVP matrices
	glm::mat4 modelMat;
	glm::mat4 viewMat;
	glm::mat4 projMat;
	projMat = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
	#pragma endregion


	// render loop
	while (!glfwWindowShouldClose(window)) // mean: ���window��Ӧ�ý���
	{

		// Process Input
		processInput(window);

		// Clear Screen
		glClearColor(0.0f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // �����Ȼ���

		

		viewMat = camera.GetViewMatrix();
		for (int i = 0; i < 10; i++)
		{   
			// Set Model matrix
			modelMat = glm::translate(glm::mat4(1.0f), cubePositions[i]);

			// Set view and Projection Matrices if you want.
			//

			// Set Material -> Texture
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, TexBufferA);
			glActiveTexture(GL_TEXTURE3);
			glBindTexture(GL_TEXTURE_2D, TexBufferB);
			//Set Material -> Shader Program
			myShader->use();
			// Set Material -> Uniforms
			glUniform1i(glGetUniformLocation(myShader->ID, "ourTexture"), 0);
			glUniform1i(glGetUniformLocation(myShader->ID, "ourFace"), 3);
			glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat));
			glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
			glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));

			//Set  Model
			glBindVertexArray(VAO);

			//Drawcall
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		
		// Clean up. prepare for next render loop.
		glfwSwapBuffers(window);    // double buffers
		glfwPollEvents();			// ��ȡ�û�����
		camera.UpdateCameraPos();  // ��ȡ���λ�ø���
	}
	// Exit program
	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow * window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camera.speedZ = 1.0f;
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		camera.speedZ = -1.0f;
	}
	else if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.speedX = -1.0f;
	}
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.speedX = 1.0f;
	}
	else
	{
		camera.speedZ = 0;
		camera.speedX = 0;
	}
}
void mouse_callback(GLFWwindow * window,double xPos, double yPos)
{
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}
	else
	{
		float deltaX, deltaY;
		deltaX = xPos - lastX;
		deltaY = yPos - lastY;
		lastX = xPos;
		lastY = yPos;
		camera.ProcessMouseMovement(deltaX, deltaY);
	}
}
