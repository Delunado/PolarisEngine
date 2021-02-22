#include "Input.h"
#include "Debug.h"

Input* Input::instance = nullptr;


Input::Input(): window(nullptr), mouseSensitivity(0.02f) {

}

void Input::Initialize(const Window& window)
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