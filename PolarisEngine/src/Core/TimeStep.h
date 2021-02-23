#pragma once

#include <GL/glew.h>

class Time
{
private:
	Time();
	~Time();

	static Time* instance;

	//Time between frames
	GLfloat deltaTime;

	GLfloat lastFrameTime;

public:
	static void Init();
	void InitImplementation();

	static void Update();
	void UpdateImplementation();

	static GLfloat GetDeltaTime();
	GLfloat GetDeltaTimeImplementation();

	/// <summary>
	/// Returns the elapsed time since the application started.
	/// </summary>
	/// <returns>Time in seconds</returns>
	static GLfloat GetTimeSinceStart();
	static GLfloat GetTimeSinceStartImplementation();

};