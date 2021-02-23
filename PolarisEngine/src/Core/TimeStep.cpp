#include "TimeStep.h"

#include <GLFW/glfw3.h>

Time* Time::instance = nullptr;

Time::Time() : deltaTime(0), lastFrameTime(0)
{

}

Time::~Time()
{
}

void Time::Init()
{
	instance = new Time();

	instance->InitImplementation();
}

void Time::InitImplementation()
{
	glfwSetTime(0);

	lastFrameTime = glfwGetTime();
}

void Time::Update()
{
	instance->UpdateImplementation();
}

void Time::UpdateImplementation()
{
	GLfloat currentTime = glfwGetTime();
	deltaTime = currentTime - lastFrameTime;
	lastFrameTime = currentTime;
}

GLfloat Time::GetDeltaTime()
{
	return instance->GetDeltaTimeImplementation();
}

GLfloat Time::GetDeltaTimeImplementation()
{
	return deltaTime;
}

GLfloat Time::GetTimeSinceStart()
{
	return instance->GetDeltaTimeImplementation();
}

GLfloat Time::GetTimeSinceStartImplementation()
{
	return glfwGetTime();
}
