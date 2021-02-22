#pragma once

#include <string>

class GLFWwindow;

class Window
{
private:
	GLFWwindow* window;

	std::string title;
	int width;
	int height;

	bool vSync;

public:
	Window();
	~Window();

	static bool glfwIsInitialized;

	int Init(int width, int height, std::string title);

	GLFWwindow* GetWindowPointer() const;
	void SetUserPointer(void* userPointer);
	void* GetUserPointer();

	bool IsVSyncActive();
	void SetVSyncActive(bool active);

	void SwapBuffers();
	void Update();

	bool IsRunning();
	void Close();
	void Destroy();

	int GetWidth();
	void SetWidth(int width);

	int GetHeight();
	void SetHeight(int height);

	std::string GetTitle();
	void SetTitle(std::string title);
};

