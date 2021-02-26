#include "CameraController.h"

#include "Renderer.h"
#include "Input.h"
#include "Camera.h"

CameraController::CameraController(float speed) : speed(speed), lastMousePos(glm::vec2(0.0f, 0.0f))
{

}

float CameraController::GetSpeed()
{
	return speed;
}

void CameraController::SetSpeed(float speed)
{
	this->speed = speed;
}

void CameraController::Update(float deltaTime)
{
	const glm::vec2& mousePos = Input::GetMousePosition();
	glm::vec2 deltaPos = (mousePos - lastMousePos) * 0.06f;
	lastMousePos = mousePos;
	MouseMovement(deltaPos.x, -deltaPos.y);

	if (Input::GetKeyPressed(KEYCODE_LEFT_ALT)) {
		float finalCameraSpeed = speed * deltaTime;
		KeyboardMovement(finalCameraSpeed);
	}
}

void CameraController::MouseMovement(double mouseOffsetX, double mouseOffsetY)
{
	float finalSpeed = Input::GetMouseSensitivity() * speed;
	double xOffset = mouseOffsetX * finalSpeed;
	double yOffset = mouseOffsetY * finalSpeed;

	if (Input::IsMouseButtonPressed(MOUSE_CODE_BUTTON_MIDDLE)) { //Zoom
		CameraZoom(yOffset);
	}
	else {
		if (!Input::IsMouseButtonPressed(MOUSE_CODE_BUTTON_LEFT) && !Input::IsMouseButtonPressed(MOUSE_CODE_BUTTON_RIGHT)) { //Pan/Tilt
			CameraPan(xOffset);
			CameraTilt(yOffset);
		}
		else if (Input::IsMouseButtonPressed(MOUSE_CODE_BUTTON_LEFT) && !Input::IsMouseButtonPressed(MOUSE_CODE_BUTTON_RIGHT)) { //Dolly
			CameraDolly(0.0f, yOffset);
			CameraDolly(xOffset, 0.0f);
		}
		else if (!Input::IsMouseButtonPressed(MOUSE_CODE_BUTTON_LEFT) && Input::IsMouseButtonPressed(MOUSE_CODE_BUTTON_RIGHT)) { //Crane
			CameraCrane(yOffset);
		}
		else if (Input::IsMouseButtonPressed(MOUSE_CODE_BUTTON_LEFT) && Input::IsMouseButtonPressed(MOUSE_CODE_BUTTON_RIGHT)) { //Orbit
			CameraOrbit(xOffset, yOffset);
		}
	}
}

void CameraController::KeyboardMovement(float speed)
{
	//Dolly
	if (Input::GetKeyPressed(GLFW_KEY_W))
		CameraDolly(0.0f, speed);
	if (Input::GetKeyPressed(GLFW_KEY_S))
		CameraDolly(0.0f, -speed);
	if (Input::GetKeyPressed(GLFW_KEY_A))
		CameraDolly(-speed, 0.0f);
	if (Input::GetKeyPressed(GLFW_KEY_D))
		CameraDolly(speed, 0.0f);

	//Crane
	if (Input::GetKeyPressed(GLFW_KEY_Q))
		CameraCrane(-speed);
	if (Input::GetKeyPressed(GLFW_KEY_E))
		CameraCrane(speed);
}

void CameraController::CameraDolly(GLfloat x, GLfloat z)
{
	Render::Renderer::GetInstance()->GetCurrentCamera()->Move(Render::CAMERA_MOV_DIR::FORWARD, z);
	Render::Renderer::GetInstance()->GetCurrentCamera()->Move(Render::CAMERA_MOV_DIR::RIGHTWARD, x);
}

void CameraController::CameraCrane(GLfloat y)
{
	Render::Renderer::GetInstance()->GetCurrentCamera()->Move(Render::CAMERA_MOV_DIR::UPWARD, y);
}

void CameraController::CameraZoom(GLfloat zoom)
{
	Render::Renderer::GetInstance()->GetCurrentCamera()->Zoom(zoom);
}

void CameraController::CameraPan(GLfloat angle)
{
	Render::Renderer::GetInstance()->GetCurrentCamera()->Rotate(angle, 0.0f);
}

void CameraController::CameraTilt(GLfloat angle)
{
	Render::Renderer::GetInstance()->GetCurrentCamera()->Rotate(0.0f, angle);
}

void CameraController::CameraOrbit(GLfloat angleX, GLfloat angleY)
{
	Render::Renderer::GetInstance()->GetCurrentCamera()->RotateAround(angleX, angleY, Render::Renderer::GetInstance()->GetCurrentCamera()->GetLookAtPoint());
}
