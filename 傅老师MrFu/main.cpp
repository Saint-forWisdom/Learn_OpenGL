#include<iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include<GLFW/glfw3.h>

float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f,
	 0.8f,  0.8f, 0.0f
};

const char* vertexShaderSource =
"#version 330 core											\n	   "
"layout(location = 6) in vec3 aPos;							\n	   "// location ��ֵ��VAO�з�����ֵ������
"void main() {												\n	   "
"		gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);}	\n	   ";

const char*  fragmentShaderSource =
"#version 330 core									\n	"
"out vec4 FragColor;								\n	"
"void main() {										\n	"
"		FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);}	\n	";


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
	
//	unsigned int VAO[10];
//glGenVertexArrays(10, VAO);
	unsigned int VAO;
	glGenVertexArrays(1, &VAO); // ����һ��VAO δ��VBO
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);  //����һ��VBO�� δ�� Array Buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // ��VBO���� ARRAY Buffer ��

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);		// ����һ��vertex shader�� ����shaderID
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // �򴴽���shader�д���Դ����
	glCompileShader(vertexShader);							// compile shader function

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);		// ����һ��fragment shader�� ����shaderID
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL); // �򴴽���shader�д���Դ����
	glCompileShader(fragmentShader);							// compile shader function

	// ��װvertex shader �� fragment shader
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(6);
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
		glUseProgram(shaderProgram);
		glDrawArrays(GL_TRIANGLES, 0, 6);
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
