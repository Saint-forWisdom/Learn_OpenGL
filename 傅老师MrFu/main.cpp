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
"layout(location = 6) in vec3 aPos;							\n	   "// location 的值是VAO中放特征值的索引
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
	// 创建一个GLFW window 对象
	if (window == NULL)
	{
		printf("Error in Openwindow.\n");
		glfwTerminate(); // 停止
		return -1;
	}
	glfwMakeContextCurrent(window); // 使用这个window对象

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
	glGenVertexArrays(1, &VAO); // 产生一个VAO 未绑定VBO
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);  //产生一个VBO， 未绑定 Array Buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // 将VBO绑在 ARRAY Buffer 上

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);		// 创建一个vertex shader， 返回shaderID
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // 向创建的shader中传入源代码
	glCompileShader(vertexShader);							// compile shader function

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);		// 创建一个fragment shader， 返回shaderID
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL); // 向创建的shader中传入源代码
	glCompileShader(fragmentShader);							// compile shader function

	// 组装vertex shader 和 fragment shader
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(6);
	// 配置完成

	while (!glfwWindowShouldClose(window)) // mean: 如果window不应该结束
	{
		// 自定义处理用户输入window 中的动作
		// 1,process input 
		processInput(window);

		// 2, render command 渲染
		// 1) 清屏 2）
		glClearColor(0.0f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(VAO);
		glUseProgram(shaderProgram);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// 切换 帧
		glfwSwapBuffers(window);  // double buffers
		glfwPollEvents();			// 获取用户输入
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
