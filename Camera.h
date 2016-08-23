#ifndef CAMERA_H
#define CAMERA_H


#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>


class Camera {


public:
	Camera(int WindowWidth, int WindowHeight);
	void RotateCamera(glm::vec2 mouseDelta, glm::vec3 rotAxis);
	void UpdateCameraPosition();
	void SetMouseSensitivity(GLfloat sensitivity);
	void SetZoom(GLfloat zoom);

private:
	int xMid; 
	int yMid; 
	
	GLfloat zoom;
	GLfloat mouseSensitivity;

	glm::vec3 rotationAxis;

	glm::vec3 cameraPosition;
	glm::vec3 cameraView;
	glm::vec3 cameraUp;
	glm::vec3 cameraRight;

	glm::vec3 worldUp;

	glm::quat quaternion;

};

Camera::Camera(int WindowWidth, int WindowHeight, glm::vec3 initialPos = glm::vec3(0.0f, 0.0f, 0.0f), world_up glm::vec3(0.0f, 1.0f, 0.0f)) {
	xMid = WindowWidth / 2;
	yMid = WindowHeight / 2;
	cameraPosition = initialPos;
	worldUp = world_up;
}

void Camera::RotateCamera(glm::vec2 mouseDelta, glm::vec3 rotAxisX, glm::vec rotAxisY) {

}

void Camera::UpdateCameraPosition() {

}

void Camera::SetMouseSensitivity(GLfloat sensitivity) {

}

void Camera::SetZoom(GLfloat zoom) {

}
#endif