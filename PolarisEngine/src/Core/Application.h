#pragma once

#include <GL/glew.h>

#include "ShaderProgram.h"
#include "Model.h"
#include "Texture.h"
#include "Camera.h"

#include "AmbientLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "DirectionalLight.h"

#include "TimeStep.h"
#include "CameraController.h"
#include "Window.h"

class Application
{
public:
	Application();

	int Init(GLint windowHeight = 1080, GLint windowWidth = 1920);
	void Run();
	void Close();

	void PrintAppInfo();

private:

	CameraController cameraController;
	Window window;

	Time time;

	//Constants
	const GLfloat COLOR_MOUSE_WHEEL_MULTIPLIER = 0.01f;

	Render::ShaderProgram* basicShaderProgram;
	Render::ShaderProgram* normalShaderProgram;
	Render::Shader* vertexShader;
	Render::Shader* fragmentShader;

	Render::Model* currentModel;
	Render::Material* basicMaterial;
	Render::Material* dragonMaterial;
	Render::Material* spotMaterial;

	Render::Texture* dragonTexture;
	Render::Texture* spotTexture;

	Render::AmbientLight* ambientLight;
	Render::PointLight* pointLight;
	Render::DirectionalLight* directionalLight;
	Render::SpotLight* spotLight;

	GLfloat posOffset;


	//Este callback será llamado cada vez que el área de dibujo OpenGL deba ser redibujada
	inline static void window_refresh_callback(GLFWwindow* window) {
		Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
		app->Refresh();
	}

	void Refresh();


	//Este callback será llamado cada vez que se cambie el tamaño del área de dibujo OpenGL
	inline static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
		Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
		app->ResizeWindow(width, height);
	}

	void ResizeWindow(GLint width, GLint height); 


	//Este callback será llamado cada vez que se pulse una tecla dirigida al área de dibujo OpenGL
	inline static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
		app->KeyPressed(key, action);
	}

	void KeyPressed(GLint key, GLint action);


	//Este callback será llamado cada vez que se pulse algún botón del ratón sobre el área de dibujo OpenGL
	inline static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
		Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
		app->MousePressed(button, action);
	}

	void MousePressed(GLint button, GLint action);


	inline static void mouse_move_callback(GLFWwindow* window, double xpos, double ypos) {
		Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
		app->MouseMovement(xpos, ypos);
	}

	void MouseMovement(GLdouble xpos, GLdouble ypos);


	inline static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
		Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
		app->MouseScroll(xoffset, yoffset);
	}

	void MouseScroll(GLdouble xoffset, GLdouble yoffset);
};