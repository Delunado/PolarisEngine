#include "TimeStep.h"

#include <GLFW/glfw3.h>

Time::Time() : deltaTime(0), lastFrameTime(0)
{

}

Time::~Time()
{
}

void Time::Init()
{
	glfwSetTime(0);

	lastFrameTime = glfwGetTime();
}

void Time::Update()
{
	GLfloat currentTime = glfwGetTime();
	deltaTime = currentTime - lastFrameTime;
	lastFrameTime = currentTime;
}

GLfloat Time::GetDeltaTime()
{
	return deltaTime;
}

GLfloat Time::GetTimeSinceStart()
{
	return glfwGetTime();
}
