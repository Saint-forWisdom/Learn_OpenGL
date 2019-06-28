#include<iostream>

#include"Shader.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include<GLFW/glfw3.h>

float vertices[] = {
	-0.5f, -0.5f, 0.0f, 1.0f, 0, 0,  // 0
	 0.5f, -0.5f, 0.0f, 0,1.0f, 0,  // 1
	 0.0f,  0.5f, 0.0f, 0,  0,1.0f, // 2
	 //0.5f, -0.5f, 0.0f,			// 多余的点
	 //0.0f,  0.5f, 0.0f,			// 多余的点
	 0.8f,  0.8f, 0.0f, 1.0f, 0, 1.0f	  // 3
};
// 0，1，2   1，2，3
unsigned int indices[] = { // 索引绘制
	0,1,2,
	1,2,3
};

//const char* vertexShaderSource =
//"#version 330 core											\n	   "
//"layout(location = 6) in vec3 aPos;							\n	   "// location 的值是VAO中放特征值的索引
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

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  // 开启框线模式
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // 关闭框线模式
	
	//// 面剔除 ？？？
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK); // GL_BACK 剔除背面 ？？？
	//// openGL 逆时针点作为三角形的正面？？？？
	//// 已经懂了。。。。
	// 开始配置shader
	Shader* myShader = new Shader("vertexSource.txt", "fragmentSource.txt");
	
	//	unsigned int VAO[10];
	//glGenVertexArrays(10, VAO);
	


	unsigned int VAO;
	glGenVertexArrays(1, &VAO); // 产生一个VAO 未绑定VBO
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);  //产生一个VBO， 未绑定 Array Buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // 将VBO绑在 ARRAY Buffer 上
	// 把数据从CPU到GPU的传输线上 复制到GPU缓存上
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 把数据放入 Array Buffer通道

	// declare EBO
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);  // 把数据从CPU到GPU的传输线上 复制到GPU缓存上
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// 把数据放入 Element  Buffer通道


	//unsigned int vertexShader;
	//vertexShader = glCreateShader(GL_VERTEX_SHADER);		// 创建一个vertex shader， 返回shaderID
	//glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // 向创建的shader中传入源代码
	//glCompileShader(vertexShader);							// compile shader function

	//unsigned int fragmentShader;
	//fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);		// 创建一个fragment shader， 返回shaderID
	//glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL); // 向创建的shader中传入源代码
	//glCompileShader(fragmentShader);							// compile shader function

	//// 组装vertex shader 和 fragment shader
	//unsigned int shaderProgram;
	//shaderProgram = glCreateProgram();
	//glAttachShader(shaderProgram, vertexShader);
	//glAttachShader(shaderProgram, fragmentShader);
	//glLinkProgram(shaderProgram);

	glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(6); // 挖数据 从vbo到vao

	glVertexAttribPointer(7, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(7);
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
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

		/*float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f + 0.5f);
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		glUseProgram(shaderProgram);
		glUniform4f(vertexColorLocation, 0.0f,greenValue, 0.0f, 1.0f);*/
		myShader->use();
		//glDrawArrays(GL_TRIANGLES, 0, 6); // 使用EBO 不需要这一步
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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
