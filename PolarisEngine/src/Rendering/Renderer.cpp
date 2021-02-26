#include <exception>
#include <iostream>

#include "Model.h"
#include "Camera.h"
#include "Mesh.h"
#include "Transform.h"
#include "Light.h"

#include "Debug.h"

#include "Renderer.h"

#include <chrono>

namespace Render {
	Renderer* Renderer::instance = nullptr;

	Renderer::Renderer() : currentColor(Color::GREY), modelsList(std::vector<Model*>()), currentCamera(nullptr), lights(std::vector<Light*>())
	{

	}

	Renderer::~Renderer()
	{
		instance = nullptr;
	}

	Renderer* Renderer::GetInstance()
	{
		//Lazy Initialization
		if (instance == nullptr) {
			instance = new Renderer();
		}

		return instance;
	}

	void Renderer::InitRenderer()
	{
		//We indicate OpenGL the background color
		ApplyColor();

		//We indicate OpenGL to be aware of the depth when drawing.
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		glEnable(GL_MULTISAMPLE);

		glEnable(GL_BLEND);
	}

	void Renderer::Refresh()
	{
		auto start = std::chrono::high_resolution_clock::now();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		try 
		{
			RenderData renderInfo;

			for (int j = 0; j < lights.size(); j++) 
			{
				glBlendFunc(GL_SRC_ALPHA, j == 0 ? GL_ONE_MINUS_SRC_ALPHA : GL_ONE);

				for (int i = 0; i < modelsList.size(); i++) 
				{
					if (modelsList[i] != nullptr) 
					{
						if (currentCamera != nullptr) {
							renderInfo.lightData = lights[j]->GetLightData();
							renderInfo.mvMatrix = currentCamera->GetVisionMatrix() * modelsList[i]->GetTransform()->GetModelMatrix();
							renderInfo.mvITMatrix = glm::transpose(glm::inverse(renderInfo.mvMatrix));
							renderInfo.mvpMatrix = currentCamera->GetProjectionMatrix() * renderInfo.mvMatrix;

							modelsList[i]->Render(renderInfo);
						}
					}
				}
			}
		}
		catch (std::exception& e) {
			const std::string message = " - in function Refresh()";
			throw std::runtime_error(e.what() + message);
		}

		auto stop = std::chrono::high_resolution_clock::now();

		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

		renderFunctionTimesCalled++;
		renderFunctionTime += duration.count();
		renderFunctionAvrg = (renderFunctionTime / renderFunctionTimesCalled);

		//std::cout << "Render Function Time: " << renderFunctionAvrg << std::endl;
	}

	void Renderer::SetWindowViewport(int width, int height)
	{
		glViewport(0, 0, width, height);

		if (currentCamera != nullptr)
			currentCamera->SetAspectRel((float)width / (float)height);
	}

	void Renderer::PrintContextProperties()
	{
		std::string glRenderer((const char*)glGetString(GL_RENDERER));
		std::string glVendor((const char*) glGetString(GL_VENDOR));
		std::string glVersion((const char*)glGetString(GL_VERSION));
		std::string glShadingLanguageVersion((const char*)glGetString(GL_SHADING_LANGUAGE_VERSION));

		Log::PrintMessage(glRenderer);
		Log::PrintMessage(glVendor);
		Log::PrintMessage(glVersion);
		Log::PrintMessage(glShadingLanguageVersion);
	}

	void Renderer::SetBackgroundColor(Color& newColor)
	{
		currentColor = newColor;

		ApplyColor();
	}

	void Renderer::ApplyColor()
	{
		glClearColor(currentColor[R], currentColor[G], currentColor[B], currentColor[A]);
	}

	Color& Renderer::GetBackgroundColor()
	{
		return currentColor;
	}

	void Renderer::SetCurrentCamera(Camera* camera)
	{
		this->currentCamera = camera;
	}

	Camera* Renderer::GetCurrentCamera()
	{
		return currentCamera;
	}

	void Renderer::AddModel(Model* model)
	{
		this->modelsList.push_back(model);
	}

	void Renderer::RemoveFirstModel()
	{
		if (modelsList.size() > 0) {
			if (modelsList[0] != nullptr)
				delete modelsList[0];

			modelsList.erase(modelsList.begin());
		}
	}

	void Renderer::RemoveLastModel()
	{
		if (modelsList.size() > 0) {
			if (modelsList[modelsList.size() - 1] != nullptr)
				delete modelsList[modelsList.size() - 1];

			modelsList.pop_back();
		}
	}

	void Renderer::RemoveAllModels()
	{
		for (int i = 0; i < modelsList.size(); i++) {
			if (modelsList[i] != nullptr)
				delete modelsList[i];
		}

		modelsList.clear();
	}

	void Renderer::SetModelRepresentationToTexture()
	{
		for (int i = 0; i < modelsList.size(); i++) {
			modelsList[i]->SetModelRepresentation(MODEL_REPRESENTATION::TEXTURE);
		}
	}

	void Renderer::SetModelRepresentationToSolid()
	{
		for (int i = 0; i < modelsList.size(); i++) {
			modelsList[i]->SetModelRepresentation(MODEL_REPRESENTATION::SOLID);
		}
	}

	void Renderer::SetModelRepresentationToWireframe()
	{
		for (int i = 0; i < modelsList.size(); i++) {
			modelsList[i]->SetModelRepresentation(MODEL_REPRESENTATION::WIREFRAME);
		}
	}

	std::vector<Model*> Renderer::GetModelsList() const
	{
		return modelsList;
	}

	void Renderer::AddLight(Light* light)
	{
		lights.push_back(light);
	}
}