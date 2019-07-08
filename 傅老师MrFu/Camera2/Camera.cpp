#include "Camera.h"



Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldup)
{
	Position = position;
	Worldup = worldup;
	Forward = glm::normalize(target - position);
	Right = glm::normalize(glm::cross(Forward, Worldup)); 
	Up = glm::normalize(glm::cross(Forward, Right));
}

Camera::Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldup)
{
	Position = position;
	Worldup = worldup;
	Pitch = pitch;
	Yaw = yaw;
	// elur position
	Forward.x = glm::cos(Pitch) * glm::sin(Yaw);
	Forward.y = glm::sin(Pitch);
	Forward.z = glm::cos(Pitch) * glm::cos(Yaw);

	Right = glm::normalize(glm::cross(Forward, Worldup));
	Up = glm::normalize(glm::cross(Forward, Right));
}


Camera::~Camera()
{
}

glm::mat4 Camera::GetViewMatrix() {
	return glm::lookAt(Position, Position + Forward, Worldup);
}

void Camera::ProcessMouseMovement(float deltaX, float deltaY)
{
	Pitch -= deltaY*SenseX;
	Yaw -= deltaX*SenseY;
	UpdateCameraVectors();
}

void Camera::UpdateCameraPos()
{
	//Position += glm::vec3(0, 0, -speedZ*0.1f);
	Position += Forward * speedZ * 0.1f;
}

void Camera::UpdateCameraVectors()
{
	Forward.x = glm::cos(Pitch) * glm::sin(Yaw);
	Forward.y = glm::sin(Pitch);
	Forward.z = glm::cos(Pitch) * glm::cos(Yaw);
	Right = glm::normalize(glm::cross(Forward, Worldup));
	Up = glm::normalize(glm::cross(Forward, Right));
}
