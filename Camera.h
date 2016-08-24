#ifndef CAMERA_H
#define CAMERA_H


#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>


enum class Relative_Direction { UP, DOWN, LEFT, RIGHT };


class Camera {


public:
	Camera(int WindowWidth, int WindowHeight, glm::vec3 initialPos, glm::vec3 initialTarget, glm::vec3 rotAxisX, glm::vec3 rotAxisY, glm::vec3 world_up);
	void RotateCamera(glm::vec2 mouseDelta);
	void TranslateCamera(Relative_Direction direction, GLfloat cameraSpeed);
	void SetMouseSensitivity(GLfloat sensitivity);
	void SetZoom(GLfloat zoom);

private:

	int xMid; 
	int yMid; 

	// Reference vectors
	glm::vec3 worldUp;
	glm::vec3 rotAxisX;
	glm::vec3 rotAxisY;

	
	// Camera Position
	glm::vec3 cameraPosition;
	glm::vec3 lastPosition;

	// Camera Orientation 
	glm::vec3 cameraDirection;
	glm::vec3 cameraUp;
	glm::vec3 cameraRight;


	// Environment variables
	GLfloat zoom;
	GLfloat mouseSensitivity;


	glm::mat4 rotation;
	glm::mat4 view;



};

Camera::Camera(
		int WindowWidth, 
		int WindowHeight,
		glm::vec3 initialPos = glm::vec3(0.0f, 0.0f, 3.0f),
	    glm::vec3 initialTarget = glm::vec3(0.0f,0.0f,0.0f),
		glm::vec3 rotAxisX = glm::vec3(1.0f,0.0f,0.0f), 
		glm::vec3 rotAxisY = glm::vec3(0.0f,1.0f,0.0f), 
		glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f)) : 
		mouseSensitivity(0.5f), 
	    zoom(45.0f) {
			this->xMid = WindowWidth / 2;
			this->yMid = WindowHeight / 2;
			this->rotAxisX = rotAxisX;
			this->rotAxisY = rotAxisY;
			this->cameraPosition = initialPos;
			this->cameraDirection = glm::normalize(initialPos - initialTarget);
			this->worldUp = worldUp;
}

void Camera::RotateCamera(glm::vec2 mouseDelta) {
	GLfloat rotAngleX = 2.0f; //mouseDelta.x / mouseSensitivity;
	GLfloat rotAngleY = 2.0f; //mouseDelta.y / mouseSensitivity;

	glm::quat rotation = glm::angleAxis(glm::degrees(rotAngleY), normalize(rotAxisY)) * glm::angleAxis(glm::degrees(rotAngleX), normalize(rotAxisX));
	cameraDirection = rotation * cameraDirection;
	cameraRight = glm::normalize(glm::cross(worldUp, cameraDirection));
	cameraUp = glm::cross(cameraDirection, cameraRight);
    
}

void Camera::TranslateCamera(Relative_Direction direction, GLfloat cameraSpeed) {
	switch (direction) {
		case Relative_Direction::UP:
//#TODO
				break;
		case Relative_Direction::DOWN:
				break;
		case Relative_Direction::LEFT:
				break;
		case Relative_Direction::RIGHT:
				break;
	}
}

void Camera::SetMouseSensitivity(GLfloat sensitivity) {

}

void Camera::SetZoom(GLfloat zoom) {

}
#endif
