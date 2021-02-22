#include <GLFW/glfw3.h>

#include "Debug.h"

#include "Window.h"

bool Window::glfwIsInitialized = false;

Window::Window() : window(nullptr), title(""), width(0), height(0), vSync(false)
{
}

Window::~Window()
{
	Close();
}

int Window::Init(int width, int height, std::string title)
{
	//First we initialize GLFW, only once in runtime.
	if (!glfwIsInitialized) {
		int glfwInitCode = glfwInit();
		assert(glfwInitCode == GLFW_TRUE);
		glfwIsInitialized = true;
	}

	//Here we define the OpenGL context features we want it to use, like samples number, core Profile mode, etc.
	//Antialiasing with 4 samples
	glfwWindowHint(GLFW_SAMPLES, 4);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

	window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	assert(window != nullptr);

	glfwMakeContextCurrent(window);

	this->title = std::string(title);
	this->width = width;
	this->height = height;
	SetVSyncActive(true);

	return 0;
}

GLFWwindow* Window::GetWindowPointer() const
{
	return window;
}

void Window::SetUserPointer(void* userPointer)
{
	assert(window != nullptr);
	glfwSetWindowUserPointer(window, userPointer);
}

void* Window::GetUserPointer()
{
	assert(window != nullptr);
	return glfwGetWindowUserPointer(window);
}

bool Window::IsVSyncActive()
{
	return vSync;
}

void Window::SetVSyncActive(bool active)
{
	glfwSwapInterval(active == true ? 1 : 0);
	vSync = active;
}

void Window::SwapBuffers()
{
	assert(window != nullptr);
	glfwSwapBuffers(window);
}

void Window::Update()
{
	glfwPollEvents();
}

bool Window::IsRunning()
{
	assert(window != nullptr);
	return !glfwWindowShouldClose(window);
}

void Window::Close()
{
	assert(window != nullptr);
	glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void Window::Destroy()
{
	glfwDestroyWindow(window);
}

int Window::GetWidth()
{
	return width;
}

void Window::SetWidth(int width)
{
	this->width;
}

int Window::GetHeight()
{
	return height;
}

void Window::SetHeight(int height)
{
	this->height;
}

std::string Window::GetTitle()
{
	return title;
}

void Window::SetTitle(std::string title)
{
	assert(window != nullptr);
	this->title = title;
	glfwSetWindowTitle(window, title.c_str());
}
