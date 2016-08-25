#ifndef CAMERA_H
#define CAMERA_H


#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>



enum class Relative_Direction { FORWARD, BACKWARD, LEFT, RIGHT, UP, DOWN };


class Camera {


public:

	Camera(int WindowWidth, int WindowHeight, glm::vec3 initialPos, glm::vec3 initialTarget,  glm::vec3 rotAxisY, glm::vec3 world_up);
	glm::mat4 GetCameraView();

	void RotateCamera(const glm::vec2 &newMousePos);
	void TranslateCamera(const Relative_Direction &direction, const GLfloat &cameraSpeed);
	void SetMouseSensitivity(GLfloat &sensitivity);
	void SetZoom(GLfloat &zoom);


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


	GLfloat rotationAboutX;
	glm::mat4 view;

	glm::vec2 mousePosition;

	void ConstructViewMatrix();
	



};

Camera::Camera(
		int WindowWidth, 
		int WindowHeight,
		glm::vec3 initialPos = glm::vec3(3.0f, 0.0f, 0.0f),
	    glm::vec3 initialTarget = glm::vec3(0.0f,0.0f,0.0f),
		glm::vec3 rotAxisX = glm::vec3(1.0f,0.0f,0.0f), 
		glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f)) : 
		mouseSensitivity(0.00025f), 
	    zoom(45.0f) {
			this->xMid = WindowWidth / 2;
			this->yMid = WindowHeight / 2;
			this->mousePosition = glm::vec2(xMid, yMid);
			this->rotAxisY = rotAxisY;
			this->worldUp = worldUp;
			this->cameraPosition = initialPos;
			this->cameraDirection = glm::normalize(initialPos - initialTarget);
			this->cameraRight = glm::normalize(glm::cross(worldUp, cameraDirection));
			this->cameraUp = glm::cross(cameraDirection, cameraRight);
			ConstructViewMatrix();
}

void Camera::RotateCamera(const glm::vec2 &newMousePos) {
	
   

	GLfloat rotAngleY = (mousePosition.x - newMousePos.x) * mouseSensitivity;
	GLfloat rotAngleX = (mousePosition.y - newMousePos.y) * mouseSensitivity;
	
  

	if ( abs(rotAngleX) > std::numeric_limits<float>::epsilon()) {
		glm::quat rotationX = glm::normalize(glm::angleAxis(glm::degrees(rotAngleX), normalize(cameraRight)));
		cameraDirection = rotationX * cameraDirection;
	}

	if ( abs(rotAngleY) > std::numeric_limits<float>::epsilon()) {
		glm::quat rotationY = glm::normalize(glm::angleAxis(glm::degrees(rotAngleY), normalize(rotAxisY)));
		cameraDirection = rotationY * cameraDirection;
	}

	
	cameraRight = glm::normalize(glm::cross(worldUp, cameraDirection));
	cameraUp = glm::cross(cameraDirection, cameraRight);
	mousePosition = newMousePos;
}

void Camera::TranslateCamera(const Relative_Direction &direction, const GLfloat &cameraSpeed) {
	switch (direction) {
		case Relative_Direction::FORWARD:
			cameraPosition -= glm::normalize(cameraDirection) * cameraSpeed;
			break;
		case Relative_Direction::BACKWARD:
			cameraPosition += glm::normalize(cameraDirection) * cameraSpeed;
			break;
		case Relative_Direction::LEFT:
			cameraPosition -= glm::normalize(cameraRight) * cameraSpeed;
			break;
		case Relative_Direction::RIGHT:
			cameraPosition += glm::normalize(cameraRight) * cameraSpeed;
			break;
	}
}


glm::mat4 Camera::GetCameraView() {
	ConstructViewMatrix();
	return view;
}

void Camera::ConstructViewMatrix() {
	glm::mat4 viewMat = glm::transpose(glm::mat4(glm::vec4(cameraRight, glm::dot(cameraRight, -cameraPosition)),
		glm::vec4(cameraUp, glm::dot(cameraUp, -cameraPosition)),
		glm::vec4(cameraDirection, glm::dot(cameraDirection, -cameraPosition)),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)));
	
	this->view = viewMat;
}

void Camera::SetMouseSensitivity(GLfloat &sensitivity) {
	this->mouseSensitivity = sensitivity;
}

void Camera::SetZoom(GLfloat &zoom) {
	this->zoom = zoom;
}
#endif
