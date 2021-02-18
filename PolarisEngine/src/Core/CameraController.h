#pragma once

#include "glm/vec2.hpp"

class CameraController
{
private:
	float speed;

	glm::vec2 lastMousePos;

	void MouseMovement(double mouseOffsetX, double mouseOffsetY);
	void KeyboardMovement(float speed);

	//Move the position of the camera
	void CameraDolly(float x, float z);

	void CameraCrane(float y);

	void CameraZoom(float zoom);

	void CameraPan(float angle);

	void CameraTilt(float angle);

	void CameraOrbit(float angleX, float angleY);

public:
	CameraController(float speed = 2.5f);

	float GetSpeed();
	void SetSpeed(float speed);

	void Update(float deltaTime);
};

