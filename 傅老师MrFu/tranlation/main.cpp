#include<iostream>
#include"Shader.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include<GLFW/glfw3.h>
// GLM 矩阵运算 库
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

//float vertices[] = {
//	-0.5f, -0.5f, 0.0f, 1.0f, 0, 0,			// 0
//	 0.5f, -0.5f, 0.0f, 0,1.0f, 0,			// 1
//	 0.0f,  0.5f, 0.0f, 0,  0,1.0f,			// 2
//	 0.8f,  0.8f, 0.0f, 1.0f, 0, 1.0f	    // 3
//};
//// 0，1，2   1，2，3
float vertices[] = {
	//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
};
unsigned int indices[] = { // 索引绘制
	0,1,2,
	2,3,0
};

using namespace std;
// 自定义处理函数的声明
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
	
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK); // GL_BACK 剔除背面 ？？？
	// 开始配置shader
	
	Shader* myShader = new Shader("vertexSource.txt", "fragmentSource.txt");
	
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

	glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(6); // 挖数据 从vbo到vao
	glVertexAttribPointer(7, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(7); // 颜色
	glVertexAttribPointer(8, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(8); //uv 值
	// 配置完成

	// create texture buffer
	unsigned int TexBufferA;
	glGenTextures(1, &TexBufferA);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TexBufferA);
	
	int width, height, nrChanne;
	stbi_set_flip_vertically_on_load(true);
	unsigned char * data = stbi_load("container.jpg", &width, &height, &nrChanne, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "load image error." << std::endl;
	}
	stbi_image_free(data);
	// TexBuffer B
	unsigned int TexBufferB;
	glActiveTexture(GL_TEXTURE3);
	glGenTextures(1, &TexBufferB);
	glBindTexture(GL_TEXTURE_2D, TexBufferB);
	unsigned char* data2 = stbi_load("awesomeface.png", &width, &height, &nrChanne, 0);
	if (data2)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
		glGenerateMipmap(GL_TEXTURE_2D);// 这句 不懂

	}
	else {
		std::cout << "load image error." << std::endl;
	}
	stbi_image_free(data2);

	// 矩阵运算 calculate our transformation matrix here
	glm::mat4 trans;			// declare trans
	trans = glm::translate(trans, glm::vec3(-0.5f,0.0f, 0.0f)); // 0
	trans = glm::rotate(trans,glm::radians(45.f) , glm::vec3(0, 0, 1)); // 1 (float)glfwGetTime()
	trans = glm::scale(trans, glm::vec3(2.0f, 1.0f, 1.0f));				// 2
	//trans = glm::rotate(trans, glm::radians(45.0f), glm::vec3(0, 0, 1));	// 绕z轴转
	//trans = glm::scale(trans, glm::vec3(2.0f, 2.0f, 2.0f));

	while (!glfwWindowShouldClose(window)) // mean: 如果window不应该结束
	{
		// 自定义处理用户输入window 中的动作

		processInput(window);

		// 刷 屏
		glClearColor(0.0f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// 将 TexBufferA 和 TexBufferB分别绑定
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, TexBufferA);
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, TexBufferB);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

		/*float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f + 0.5f);
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		glUseProgram(shaderProgram);
		glUniform4f(vertexColorLocation, 0.0f,greenValue, 0.0f, 1.0f);*/
		myShader->use();

		glUniform1i(glGetUniformLocation(myShader->ID, "ourTexture"), 0);
		glUniform1i(glGetUniformLocation(myShader->ID, "ourFace"), 3);
		glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "transform"), 1, GL_FALSE, glm::value_ptr(trans));
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// 切换 帧
		glfwSwapBuffers(window);    // double buffers
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
