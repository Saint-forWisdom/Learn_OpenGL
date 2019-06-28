#pragma once
#include<string>

class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentpath);
	
	// string buffer 到 string class
	std::string vertexString;		
	std::string fragmentString;
	const char* vertexSource;   // const 修饰 只能让vertexSource被写入一次
	const char* fragmentSource;
	unsigned int ID; // shader program shader
	void use();
	virtual ~Shader();
};

