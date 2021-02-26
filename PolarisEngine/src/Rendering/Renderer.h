#pragma once

#ifndef PAGRENDERER_H
#define PAGRENDERER_H
#include <GL/glew.h>

#include <vector>
#include "Color.h"

namespace Render {
	class Model;
	class Camera;
	class Light;

	class Renderer
	{
	private:
		static Renderer* instance;
		Renderer();

		//Models
		std::vector<Model*> modelsList;

		//Lights
		std::vector<Light*> lights;

		//Camera
		Camera* currentCamera;

		//Background Color
		Color currentColor;

		//Clear the color with the actual color
		void ApplyColor();

		long renderFunctionTime = 0;
		long renderFunctionTimesCalled = 0;
		long renderFunctionAvrg = 0;
	public:
		virtual ~Renderer();

		static Renderer* GetInstance();

		//Initialize some rendering propierties. You have to call this method first.
		void InitRenderer();

		//Refresh the window
		void Refresh();

		//Sets a new Viewport size for the window.
		void SetWindowViewport(int width, int height);

		//Prints the actual 3D Context Propierties
		void PrintContextProperties();

		//Change the background color, indicating the 3 color coordinates
		void SetBackgroundColor(Color& newColor);

		//Returns the actual background color
		Color& GetBackgroundColor();

		//Sets the model to render
		void AddModel(Model* model);
		void RemoveFirstModel();
		void RemoveLastModel();
		void RemoveAllModels();

		void AddLight(Light* light);

		void SetModelRepresentationToTexture();
		void SetModelRepresentationToSolid();
		void SetModelRepresentationToWireframe();

		std::vector<Model*> GetModelsList() const;

		//Sets the camera to use
		void SetCurrentCamera(Camera* camera);
		Camera* GetCurrentCamera();
	};
}
#endif /* PAGRENDERER_H */