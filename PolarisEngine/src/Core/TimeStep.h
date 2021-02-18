#pragma once

#include <GL/glew.h>

class Time
{
private:
	//Time between frames
	GLfloat deltaTime;

	GLfloat lastFrameTime;

public:
	Time();
	~Time();

	void Init();
	void Update();

	GLfloat GetDeltaTime();

	/// <summary>
	/// Returns the elapsed time since the application started.
	/// </summary>
	/// <returns>Time in seconds</returns>
	GLfloat GetTimeSinceStart();
};