#include "Input.h"
#include "Debug.h"

Input* Input::instance = nullptr;

Input::Input(): window(nullptr), mouseSensitivity(0.02f) {

}

void Input::Init(const Window& window)
{
	instance = new Input();

	instance->window = window.GetWindowPointer();
}


//---KEY METHODS---
bool Input::GetKeyPressedImplementation(int key)
{
	assert(window != nullptr);
	return glfwGetKey(window, key) == (GLFW_PRESS || GLFW_REPEAT);
}

bool Input::GetKeyPressed(int key)
{
	return instance->GetKeyPressedImplementation(key);
}


//---MOUSE METHODS---
bool Input::IsMouseButtonPressedImplementation(int mouseButton)
{
	assert(window != nullptr);
	return glfwGetMouseButton(window, mouseButton) == GLFW_PRESS;
}

glm::vec2 Input::GetMousePositionImplementation()
{
	assert(window != nullptr);

	double xPos, yPos;
	glfwGetCursorPos(window, &xPos, &yPos);

	return glm::vec2((float)xPos, (float)yPos);
}

void Input::SetCursorPosImplementation(int xPos, int yPos)
{
	glfwSetCursorPos(window, xPos, yPos);
}

void Input::SetCursorLockedImplementation(bool value)
{
	glfwSetInputMode(window, GLFW_CURSOR, value == true ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
}

float Input::GetMouseXImplementation()
{
	return GetMousePositionImplementation().x;
}

float Input::GetMouseYImplementation()
{
	return GetMousePositionImplementation().y;
}

glm::vec2 Input::GetMousePosition()
{
	return instance->GetMousePositionImplementation();
}

float Input::GetMouseSensitivity()
{
	return instance->mouseSensitivity;
}

float Input::SetMouseSensitivity(float mouseSensitivity)
{
	return instance->mouseSensitivity = mouseSensitivity;
}

void Input::SetCursorPos(int xPos, int yPos)
{
	return instance->SetCursorPosImplementation(xPos, yPos);
}

void Input::SetCursorLocked(bool value)
{
	return instance->SetCursorLockedImplementation(value);
}

bool Input::IsMouseButtonPressed(int mouseButton)
{
	return instance->IsMouseButtonPressedImplementation(mouseButton);
}

float Input::GetMouseX()
{
	return instance->GetMouseX();
}

float Input::GetMouseY()
{
	return instance->GetMouseY();
}