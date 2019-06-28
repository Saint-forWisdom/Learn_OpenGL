#pragma once
#include<string>

class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentpath);
	
	// string buffer �� string class
	std::string vertexString;		
	std::string fragmentString;
	const char* vertexSource;   // const ���� ֻ����vertexSource��д��һ��
	const char* fragmentSource;
	unsigned int ID; // shader program shader
	void use();
	virtual ~Shader();
};

