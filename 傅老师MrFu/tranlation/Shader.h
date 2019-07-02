#pragma once
#include<string>

class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentpath);
	
	// string buffer 到 string class
	std::string vertexString;	 // 生命周期 要持续到shader实例被释放	
	std::string fragmentString;
	const char* vertexSource;   // const 修饰 只能让vertexSource被写入一次
	const char* fragmentSource;
	unsigned int ID; // shader program shader
	void use();
	virtual ~Shader();
private:
	void checkCompileError(unsigned int ID, std::string type);
};

