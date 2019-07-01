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

	// ���ļ� ���� ��disk�ϴ��ļ� δ����buffer
	vertexFile.open(vertexPath);
	fragmentFile.open(fragmentPath);
	// �����쳣
	vertexFile.exceptions(std::ifstream::failbit || std::ifstream::badbit);
	fragmentFile.exceptions(std::ifstream::failbit || std::ifstream::badbit);

	

	// try catch  �����쳣
	try
	{
		if (!vertexFile.is_open() || !fragmentFile.is_open()) // fragmentFile.open error ����
		{
			throw std::exception("open file error"); // �׳��쳣
		}
		vertexSStream << vertexFile.rdbuf();			//  File Buffer --�� string Buffer
		fragmentSStream << fragmentFile.rdbuf();

		vertexString = vertexSStream.str();			// ��string  buffer д�� string class
		fragmentString = fragmentSStream.str();

		vertexSource = vertexString.c_str();
		fragmentSource = fragmentString.c_str();

		/*printf(vertexSource);
		printf(fragmentSource);*/
		unsigned int vertex, fragment;
		// ����shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vertexSource, NULL);
		glCompileShader(vertex);
		checkCompileError(vertex, "VERTEX");
	
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fragmentSource, NULL);
		glCompileShader(fragment);
		checkCompileError(fragment, "FRAGMENT");
		// ���� shader ����
		// link vertex and fragment, then output program ID
		ID = glCreateProgram();		// ���� program ID
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);		// ����   // ID ָ����program ������
		checkCompileError(ID, "PROGRAM");
		// ɾ�� vertex�� fragment shader ɾ��
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}
	catch (const std::exception& ex)
	{
		printf(ex.what());	// �����쳣
	}
}


void Shader::use()  // call glUseProgram();
{
	glUseProgram(ID);
}

Shader::~Shader()
{
}

void Shader::checkCompileError(unsigned int ID, std::string type)
{
	int success;
	char infoLog[512];
	if (type != "PROGRAM")  // ��� compile ���� vertex �� fragment ����
	{
		glGetShaderiv(ID, GL_COMPILE_STATUS, &success);		// ��ѯID ����ı���״̬
		if (!success)
		{
			glGetShaderInfoLog(ID, 512, NULL, infoLog);
			std::cout << "shader compile error: " << infoLog << std::endl;
		}
	}
	else
	{
		glGetShaderiv(ID, GL_LINK_STATUS, &success);  // ���linkʱ����
		if (!success)
		{
			glGetProgramInfoLog(ID, 512, NULL, infoLog);
			std::cout << "shader link error: " << infoLog << std::endl;
		}
	}
}
