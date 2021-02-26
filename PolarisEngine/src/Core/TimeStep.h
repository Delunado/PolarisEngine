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

	GLdouble lastTimeFPS;
	GLint framesNumber;

	void InitImplementation();
	void FPSImplementation();
	void UpdateImplementation();

	GLfloat GetDeltaTimeImplementation();
	GLfloat GetTimeSinceStartImplementation();
public:
	static void Init();

	static void Update();

	static void FPS();

	static GLfloat GetDeltaTime();

	/// <summary>
	/// Returns the elapsed time since the application started.
	/// </summary>
	/// <returns>Time in seconds</returns>
	static GLfloat GetTimeSinceStart();
};