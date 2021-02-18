#pragma once

#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

#include "KeyCodes.h"
#include "MouseCodes.h"

class Input
{
private:
	Input();

	static Input* instance;
	GLFWwindow* window;

	float mouseSensitivity;

	bool GetKeyPressedImplementation(int key);

	bool IsMouseButtonPressedImplementation(int mouseButton);
	float GetMouseXImplementation();
	float GetMouseYImplementation();
	glm::vec2 GetMousePositionImplementation();

public:
	static void Initialize(GLFWwindow* window);

	static bool GetKeyPressed(int key);
	static bool IsMouseButtonPressed(int mouseButton);

	static float GetMouseX();
	static float GetMouseY();
	static glm::vec2 GetMousePosition();
	static float GetMouseSensitivity();
	static float SetMouseSensitivity(float mouseSensitivity);
};

