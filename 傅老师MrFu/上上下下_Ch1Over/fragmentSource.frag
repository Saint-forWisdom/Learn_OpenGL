#version 330 core								
out vec4 FragColor;								   
//uniform vec4 ourColor;							 
in vec4 vertexColor;		
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform sampler2D ourFace;

void main() {		
		// FragColor = vertexColor; 
		FragColor = mix(texture(ourTexture, TexCoord), texture(ourFace, TexCoord), 0.2);
		//FragColor = texture(ourFace, TexCoord);
		}