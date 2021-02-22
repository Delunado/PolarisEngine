#include <GLFW/glfw3.h>

#include "Window.h"

Window::Window(): window(nullptr)
{
}

int Window::Init(float width, float height, const char* title)
{
	window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	glfwMakeContextCurrent(window);

	if (window == nullptr) {
		glfwTerminate(); //Freeing GLFW resources
		return -1;
	}

	return 0;
}

GLFWwindow* Window::GetWindowPointer() const
{
	return window;
}

void Window::SetUserPointer(void* userPointer)
{
	glfwSetWindowUserPointer(window, userPointer);
}

void* Window::GetUserPointer()
{
	return glfwGetWindowUserPointer(window);
}

void Window::SwapBuffers()
{
	glfwSwapBuffers(window);
}

bool Window::IsRunning()
{
	return !glfwWindowShouldClose(window);
}

void Window::Close()
{
	glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void Window::Destroy()
{
	glfwDestroyWindow(window);
}

void Window::SetCursorPos(int xPos, int yPos)
{
	glfwSetCursorPos(window, xPos, yPos);
}

void Window::SetCursorLocked(bool value)
{
	glfwSetInputMode(window, GLFW_CURSOR, value == true ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
}
