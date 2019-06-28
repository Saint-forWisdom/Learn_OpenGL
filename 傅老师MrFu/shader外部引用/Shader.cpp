#include "Shader.h"
#include<iostream>
#include<fstream>
#include<sstream>

#define GLEW_STATIC
#include <GL/glew.h>
#include<GLFW/glfw3.h>



Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	std::ifstream vertexFile;
	std::ifstream fragmentFile;
	std::stringstream vertexSStream;
	std::stringstream fragmentSStream;

	// 打开文件 开档 在disk上打开文件 未读入buffer
	vertexFile.open(vertexPath);
	fragmentFile.open(fragmentPath);
	// 处理异常
	vertexFile.exceptions(std::ifstream::failbit || std::ifstream::badbit);
	fragmentFile.exceptions(std::ifstream::failbit || std::ifstream::badbit);

	

	// try catch  处理异常
	try
	{
		if (!vertexFile.is_open() || !fragmentFile.is_open()) // fragmentFile.open error 处理
		{
			throw std::exception("open file error"); // 抛出异常
		}
		vertexSStream << vertexFile.rdbuf();			//  File Buffer --》 string Buffer
		fragmentSStream << fragmentFile.rdbuf();

		vertexString = vertexSStream.str();			// 将string  buffer 写入 string class
		fragmentString = fragmentSStream.str();

		vertexSource = vertexString.c_str();
		fragmentSource = fragmentString.c_str();

		/*printf(vertexSource);
		printf(fragmentSource);*/
		unsigned int vertex, fragment;
		// 编译shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vertexSource, NULL);
		glCompileShader(vertex);
	
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fragmentSource, NULL);
		glCompileShader(fragment);
		// 编译 shader 结束
		// link vertex and fragment, then output program ID
		ID = glCreateProgram();		// 申请 program ID
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);		// 链接   // ID 指定的program 可以用
		// 删除 vertex， fragment shader 删除
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}
	catch (const std::exception& ex)
	{
		printf(ex.what());	// 处理异常
	}
}


void Shader::use()  // call glUseProgram();
{
	glUseProgram(ID);
}

Shader::~Shader()
{
}