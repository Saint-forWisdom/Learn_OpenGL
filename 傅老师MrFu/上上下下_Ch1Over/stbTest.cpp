#include<iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main(void)
{
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	// 调整y坐标 和OpenGL匹配
	unsigned char *data = stbi_load("fox.bmp", &width, &height, &nrChannels, 0);

	for (size_t i = 0; i < 300; i += 3)
	{
		// std::cout << data[i] << std::endl;
		printf("%4d%4d%4d\n", data[i], data[i+1], data[i+2]);
	}

	stbi_image_free(data);
	while (true) {
		// do nothing
	}

	return 0;
}