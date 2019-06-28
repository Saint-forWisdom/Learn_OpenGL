#include<iostream>

#include"Shader.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include<GLFW/glfw3.h>

float vertices[] = {
	-0.5f, -0.5f, 0.0f, 1.0f, 0, 0,  // 0
	 0.5f, -0.5f, 0.0f, 0,1.0f, 0,  // 1
	 0.0f,  0.5f, 0.0f, 0,  0,1.0f, // 2
	 //0.5f, -0.5f, 0.0f,			// ����ĵ�
	 //0.0f,  0.5f, 0.0f,			// ����ĵ�
	 0.8f,  0.8f, 0.0f, 1.0f, 0, 1.0f	  // 3
};
// 0��1��2   1��2��3
unsigned int indices[] = { // ��������
	0,1,2,
	1,2,3
};

//const char* vertexShaderSource =
//"#version 330 core											\n	   "
//"layout(location = 6) in vec3 aPos;							\n	   "// location ��ֵ��VAO�з�����ֵ������
//"layout(location = 7) in vec3 aColor;							\n	   "
//"out vec4 vertexColor;										\n	   "						
//"void main() {												\n	   "
//"		gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);	    \n		"
//"		vertexColor = vec4(aColor.x, aColor.y, aColor.z, 1.0f);	    \n		"
//"}	\n	   ";
//
//const char*  fragmentShaderSource =
//"#version 330 core									\n	"
//"out vec4 FragColor;								   \n	"
//"uniform vec4 ourColor;								   \n	"
//"in vec4 vertexColor;								   \n	"
//"void main() {										\n	"
//"		FragColor = vertexColor;}	\n	";
//

using namespace std;

void processInput(GLFWwindow * window);

int main(void) {



	//printf("hehihei\n");
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

	// open GLFW Window
	GLFWwindow * window = glfwCreateWindow(800, 600, "My OpenGL Game", NULL, NULL);
	// ����һ��GLFW window ����
	if (window == NULL)
	{
		printf("Error in Openwindow.\n");
		glfwTerminate(); // ֹͣ
		return -1;
	}
	glfwMakeContextCurrent(window); // ʹ�����window����

	// Init GLEW 
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		printf("Error in initing GLEW.\n");
		return -1;
	}

	glViewport(0, 0, 800, 600);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  // ��������ģʽ
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // �رտ���ģʽ
	
	//// ���޳� ������
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK); // GL_BACK �޳����� ������
	//// openGL ��ʱ�����Ϊ�����ε����棿������
	//// �Ѿ����ˡ�������
	// ��ʼ����shader
	Shader* myShader = new Shader("vertexSource.txt", "fragmentSource.txt");
	
	//	unsigned int VAO[10];
	//glGenVertexArrays(10, VAO);
	


	unsigned int VAO;
	glGenVertexArrays(1, &VAO); // ����һ��VAO δ��VBO
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);  //����һ��VBO�� δ�� Array Buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // ��VBO���� ARRAY Buffer ��
	// �����ݴ�CPU��GPU�Ĵ������� ���Ƶ�GPU������
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// �����ݷ��� Array Bufferͨ��

	// declare EBO
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);  // �����ݴ�CPU��GPU�Ĵ������� ���Ƶ�GPU������
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// �����ݷ��� Element  Bufferͨ��


	//unsigned int vertexShader;
	//vertexShader = glCreateShader(GL_VERTEX_SHADER);		// ����һ��vertex shader�� ����shaderID
	//glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // �򴴽���shader�д���Դ����
	//glCompileShader(vertexShader);							// compile shader function

	//unsigned int fragmentShader;
	//fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);		// ����һ��fragment shader�� ����shaderID
	//glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL); // �򴴽���shader�д���Դ����
	//glCompileShader(fragmentShader);							// compile shader function

	//// ��װvertex shader �� fragment shader
	//unsigned int shaderProgram;
	//shaderProgram = glCreateProgram();
	//glAttachShader(shaderProgram, vertexShader);
	//glAttachShader(shaderProgram, fragmentShader);
	//glLinkProgram(shaderProgram);

	glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(6); // ������ ��vbo��vao

	glVertexAttribPointer(7, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(7);
	// �������

	while (!glfwWindowShouldClose(window)) // mean: ���window��Ӧ�ý���
	{
		// �Զ��崦���û�����window �еĶ���
		// 1,process input 
		processInput(window);

		// 2, render command ��Ⱦ
		// 1) ���� 2��
		glClearColor(0.0f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

		/*float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f + 0.5f);
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		glUseProgram(shaderProgram);
		glUniform4f(vertexColorLocation, 0.0f,greenValue, 0.0f, 1.0f);*/
		myShader->use();
		//glDrawArrays(GL_TRIANGLES, 0, 6); // ʹ��EBO ����Ҫ��һ��
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// �л� ֡
		glfwSwapBuffers(window);  // double buffers
		glfwPollEvents();			// ��ȡ�û�����
	}

	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow * window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}
