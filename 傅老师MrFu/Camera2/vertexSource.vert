#version 330 core												  
layout(location = 6) in vec3 aPos;				
layout(location = 7) in vec3 aColor;			
layout(location = 8) in vec2 aTexCoord;   // uv		


//uniform mat4 transform; // 通过uniform， 导入变换矩阵
uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

out vec4 vertexColor;											  						
out vec2 TexCoord;
void main() {													  
		gl_Position = projMat * viewMat * modelMat * vec4(aPos.x, aPos.y, aPos.z, 1.0);	    		// 变换矩阵
		vertexColor = vec4(aColor.x+0.5, aColor.y, aColor.z, 1.0f);
		TexCoord = aTexCoord;     // uv传输
		}
