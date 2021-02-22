#pragma once

class GLFWwindow;

class Window
{
private:
	GLFWwindow* window;

public:
	Window();

	int Init(float width, float height, const char* title);

	GLFWwindow* GetWindowPointer() const;
	void SetUserPointer(void* userPointer);
	void* GetUserPointer();

	void SwapBuffers();

	bool IsRunning();
	void Close();
	void Destroy();

	void SetCursorPos(int xPos, int yPos);
	void SetCursorLocked(bool value);
};

