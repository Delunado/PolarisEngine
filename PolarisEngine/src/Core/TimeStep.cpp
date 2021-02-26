#include "TimeStep.h"
#include <iostream>

#include <GLFW/glfw3.h>

Time* Time::instance = nullptr;

Time::Time() : deltaTime(0), lastFrameTime(0), framesNumber(0), lastTimeFPS(0)
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
	lastTimeFPS = glfwGetTime();
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

void Time::FPS()
{
	instance->FPSImplementation();
}

void Time::FPSImplementation()
{
	GLdouble currentTime = glfwGetTime();
	framesNumber++;

	if (currentTime - lastTimeFPS >= 1.0) {
		printf("%f ms/frame\n", 1000.0 / double(framesNumber));
		framesNumber = 0;
		lastTimeFPS += 1.0;
	}
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
