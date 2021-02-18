#include <GL/glew.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"

namespace TEA {
	Camera::Camera(glm::vec3 position, glm::vec3 lookAtPoint, GLfloat aspectRel) : position(position), 
		           lookAtPoint(lookAtPoint), aspectRel(aspectRel), worldUp(glm::vec3(0, 1, 0)), fovX(7.5f),
		           zNear(0.1f), zFar(200.0f)
	{
		CalculateVisionAngle();
		CalculateLocalVectors();

		CalculateVisionMatrix();
		CalculateProjectionMatrix();
	}

	Camera::Camera(const Camera& other)
	{
		this->aspectRel = other.aspectRel;
		this->fovX = other.fovX;
		this->fovY = other.fovY;
		this->front = other.front;
		this->right = other.right;
		this->up = other.up;
		this->worldUp = other.worldUp;
		this->lookAtPoint = other.lookAtPoint;
		this->position = other.position;
		this->zFar = other.zFar;
		this->zNear = other.zNear;
		this->visionMatrix = other.visionMatrix;
		this->projectionMatrix = other.projectionMatrix;
	}

	Camera::~Camera()
	{
	}

	Camera* Camera::CreateCamera(glm::vec3 position, glm::vec3 lookAtPoint, GLfloat aspectRel)
	{
		Camera* camera = new Camera(position, lookAtPoint, aspectRel);
		return camera;
	}

#pragma region CONTROL
	void Camera::Move(CAMERA_MOV_DIR movement, GLfloat speed)
	{
		glm::vec3 direction = glm::vec3(0.0f);

		switch (movement)
		{
		case CAMERA_MOV_DIR::FORWARD:
			direction = -front * speed;
			break;
		case CAMERA_MOV_DIR::RIGHTWARD:
			direction = right * speed;
			break;
		case CAMERA_MOV_DIR::UPWARD:
			direction = glm::vec3(0.0f, 1.0f, 0.0f) * speed;
			break;
		default:
			break;
		}

		glm::mat4 translation = glm::translate(glm::mat4(1.0f), direction);
		position = translation * glm::vec4(position, 1.0f);
		lookAtPoint = translation * glm::vec4(lookAtPoint, 1.0f);

		CalculateVisionMatrix();
	}

	void Camera::Zoom(GLfloat zoom)
	{
		fovX -= zoom;
		fovX = glm::clamp(fovX, 0.01f, 2.0f);

		CalculateVisionAngle();
		CalculateProjectionMatrix();
	}

	void Camera::Rotate(GLfloat degreesX, GLfloat degreesY)
	{
		glm::mat4 rotationTilt = glm::rotate(glm::mat4(1.0f), glm::radians(degreesY), right);

		glm::mat4 rotationPan = glm::rotate(glm::mat4(1.0f), glm::radians(-degreesX), up);

		glm::mat4 transformation = glm::translate(glm::mat4(1.0f), position) * rotationTilt * rotationPan * glm::translate(glm::mat4(1.0f), -position);

		lookAtPoint = transformation * glm::vec4(lookAtPoint, 1.0f);

		CalculateLocalVectors();
		CalculateVisionMatrix();
	}

	void Camera::RotateAround(GLfloat degreesX, GLfloat degreesY, glm::vec3 rotationPoint)
	{
		glm::mat4 rotationMatrixX = glm::rotate(glm::mat4(1.0f), glm::radians(degreesX), glm::normalize(up));
		glm::mat4 rotationMatrixY = glm::rotate(glm::mat4(1.0f), glm::radians(degreesY), glm::normalize(right));

		glm::mat4 transformation = glm::translate(glm::mat4(1.0f), rotationPoint) * rotationMatrixY * rotationMatrixX * glm::translate(glm::mat4(1.0f), -rotationPoint);

		position = transformation * glm::vec4(position, 1.0f);

		CalculateLocalVectors();
		CalculateVisionMatrix();
	}
#pragma endregion

#pragma region GETTERS
	glm::vec3 Camera::GetPosition()
	{
		return position;
	}

	glm::vec3 Camera::GetLookAtPoint()
	{
		return lookAtPoint;
	}

	glm::vec3 Camera::GetWorldUp()
	{
		return worldUp;
	}

	glm::vec3 Camera::GetFront()
	{
		return front;
	}

	glm::vec3 Camera::GetRight()
	{
		return right;
	}

	glm::vec3 Camera::GetUp()
	{
		return up;
	}

	GLfloat Camera::GetFieldOfViewY()
	{
		return fovY;
	}

	GLfloat Camera::GetFieldOfViewX()
	{
		return fovX;
	}

	GLfloat Camera::GetZNear()
	{
		return zNear;
	}

	GLfloat Camera::GetZFar()
	{
		return zFar;
	}

	glm::mat4 Camera::GetVisionMatrix()
	{
		return visionMatrix;
	}

	glm::mat4 Camera::GetProjectionMatrix()
	{
		return projectionMatrix;
	}

	GLfloat Camera::GetAspectRel()
	{
		return aspectRel;
	}
#pragma endregion

#pragma region SETTERS
	void Camera::SetPosition(glm::vec3 position)
	{
		this->position = position;
		CalculateLocalVectors();
		CalculateVisionMatrix();
	}

	void Camera::SetLookAtPoint(glm::vec3 lookAtPoint)
	{
		this->lookAtPoint = lookAtPoint;
		CalculateLocalVectors();
		CalculateVisionMatrix();
	}

	void Camera::SetWorldUp(glm::vec3 worldUp)
	{
		this->worldUp = worldUp;
		CalculateLocalVectors();
		CalculateVisionMatrix();
	}

	void Camera::SetFieldOfViewX(GLfloat fovX)
	{
		this->fovX = fovX;
		CalculateVisionAngle();
		CalculateProjectionMatrix();
	}

	void Camera::SetFieldOfViewY(GLfloat fovY)
	{
		this->fovY = fovY;
		CalculateProjectionMatrix();
	}

	void Camera::SetZNear(GLfloat zNear)
	{
		this->zNear = zNear;
		CalculateProjectionMatrix();
	}

	void Camera::SetZFar(GLfloat zFar)
	{
		this->zFar = zFar;
		CalculateProjectionMatrix();
	}

	void Camera::SetAspectRel(GLfloat aspecRel)
	{
		this->aspectRel = aspecRel;
		CalculateProjectionMatrix();
	}
#pragma endregion

#pragma region CALCULATIONS
	void Camera::CalculateVisionAngle()
	{
		fovY = 2 * glm::atan(glm::tan(fovX / 2) / aspectRel);
	}

	void Camera::CalculateLocalVectors()
	{
		front = -glm::normalize((lookAtPoint - position));

		right = glm::normalize(glm::cross(VectorUp(), front));

		up = glm::normalize(glm::cross(front, right));
	}

	void Camera::CalculateVisionMatrix()
	{
		visionMatrix = glm::lookAt(position, lookAtPoint, up);
	}

	void Camera::CalculateProjectionMatrix()
	{
		projectionMatrix = glm::perspective(fovY, aspectRel, zNear, zFar);
	}

	glm::vec3 Camera::VectorUp()
	{
		glm::vec3 currentUp = worldUp;

		if (glm::all(glm::epsilonEqual(front, worldUp, 0.001f)))
			currentUp = glm::vec3(0, 0, 1);
		else if (glm::all(glm::epsilonEqual(front, -worldUp, 0.001f)))
			currentUp = glm::vec3(0, 0, -1);

		return currentUp;
	}

#pragma endregion
}