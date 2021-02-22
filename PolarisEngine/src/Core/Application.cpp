#include <iostream>

#include "Renderer.h"

#include "Shader.h"

#include "Material.h"

#include "Transform.h"

#include "Color.h"
#include "Input.h"

#include "Application.h"


Application::Application(GLint windowHeight, GLint windowWidth) : windowHeight(windowHeight), windowWidth(windowWidth)
{
	
}

int Application::Init()
{
	//First we initialize GLFW, only once in runtime.
	if (glfwInit() != GLFW_TRUE) {
		std::cout << "Failed to initialize GLFW" << std::endl;
		return -1;
	}

	//Here we define the OpenGL context features we want it to use, like samples number, core Profile mode, etc.
	//Antialiasing with 4 samples
	glfwWindowHint(GLFW_SAMPLES, 4);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

	GLint windowCode = window.Init(windowWidth, windowHeight, "Polaris Engine V-0.2");
	assert(windowCode != -1);

	window.SetUserPointer(this);

	//Initializing GLEW
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW" << std::endl;
		glfwDestroyWindow(window.GetWindowPointer());
		glfwTerminate();
		return -3;
	}

	//Here we set the callbacks
	glfwSetWindowRefreshCallback(window.GetWindowPointer(), window_refresh_callback);
	glfwSetFramebufferSizeCallback(window.GetWindowPointer(), framebuffer_size_callback);
	glfwSetKeyCallback(window.GetWindowPointer(), key_callback);
	glfwSetMouseButtonCallback(window.GetWindowPointer(), mouse_button_callback);
	glfwSetCursorPosCallback(window.GetWindowPointer(), mouse_move_callback);
	glfwSetScrollCallback(window.GetWindowPointer(), scroll_callback);

	//This sets the cursor to the center of the screen and disable it.
	window.SetCursorPos(windowWidth / 2.0f, windowHeight / 2.0f);
	window.SetCursorLocked(true);

	//---- Init Polaris Classes ----
	Render::Renderer::GetInstance()->InitRenderer();

	//First we create the vertex and fragment shaders.
	vertexShader = Render::Shader::CreateShader(GL_VERTEX_SHADER, "Shaders/BasicVertexShader.glsl");
	fragmentShader = Render::Shader::CreateShader(GL_FRAGMENT_SHADER, "Shaders/BasicFragmentShader.glsl");

	//Now we create the shader program, attach the shaders and link the program.
	basicShaderProgram = Render::ShaderProgram::CreateShaderProgram(vertexShader, fragmentShader);

	//Same for normal mapping shaders
	Render::Shader* normalVertexShader = Render::Shader::CreateShader(GL_VERTEX_SHADER, "Shaders/NormalMapVertexShader.glsl");
	Render::Shader* normalFragmentShader = Render::Shader::CreateShader(GL_FRAGMENT_SHADER, "Shaders/NormalMapFragmentShader.glsl");

	normalShaderProgram = Render::ShaderProgram::CreateShaderProgram(normalVertexShader, normalFragmentShader);

	//Here we create a basic material
	basicMaterial = Render::Material::CreateMaterial(Render::Color(0.5f, 0.5f, 0.5f), Render::Color(0.1f, 0.3f, 0.7f), Render::Color(1.0f, 1.0f, 1.0f), 8.0f);
	basicMaterial->SetShaderProgram(basicShaderProgram);

	spotMaterial = Render::Material::CreateMaterial(Render::Color(0.1f, 0.3f, 0.7f), Render::Color(0.1f, 0.3f, 0.7f), Render::Color(1.0f, 1.0f, 1.0f), 8.0f);
	spotMaterial->SetShaderProgram(basicShaderProgram);
	spotTexture = Render::Texture::CreateTexture("Assets/spot_texture.png");
	spotMaterial->SetColorTexture(spotTexture);

	dragonMaterial = Render::Material::CreateMaterial(Render::Color::GREEN, Render::Color(0.5f, 0.5f, 0.5f), Render::Color(1.0f, 1.0f, 1.0f), 8.0f);
	dragonTexture = Render::Texture::CreateTexture("Assets/DragonColor.png");
	Render::Texture* diceNormalTexture = Render::Texture::CreateTexture("Assets/DragonNormal.png");
	dragonMaterial->SetShaderProgram(basicShaderProgram);

	dragonMaterial->SetShaderProgramNormalMap(normalShaderProgram);
	dragonMaterial->SetColorTexture(dragonTexture);

	dragonMaterial->SetNormalTexture(diceNormalTexture);
	dragonMaterial->SetNormalMapActive(true);

	//Here we create a model and assign it to the renderer.
	currentModel = Render::Model::CreateModel("Assets/Dragon.fbx", dragonMaterial);
	currentModel->GetTransform()->SetRotation(glm::vec3(-90.0f, 180.0f, 0.0f));
	currentModel->GetTransform()->SetScale(glm::vec3(0.25f, 0.25f, 0.25f));

	Render::Renderer::GetInstance()->AddModel(currentModel);

	//Now we create a camera and attach it to the renderer.
	Render::Camera* currentCamera = Render::Camera::CreateCamera();
	currentCamera->SetPosition(glm::vec3(0.0f, 0.0f, -40.0f));
	currentCamera->SetAspectRel((GLfloat)windowWidth / (GLfloat)windowHeight);

	Render::Renderer::GetInstance()->SetCurrentCamera(currentCamera);

	//Here we create the lights and add it to the renderer
	ambientLight = new Render::AmbientLight(Render::Color(0.12f, 0.12f, 0.12f));
	directionalLight = new Render::DirectionalLight(glm::vec3(0.0f, 1.0f, 0.0f), Render::Color::RED, Render::Color::GREEN);
	pointLight = new Render::PointLight(glm::vec3(0.0f, 1.0f, 0.0f), Render::Color::RED, Render::Color::GREEN);
	spotLight = new Render::SpotLight(glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 1.0f), 0.45f, Render::Color::RED, Render::Color::GREEN);

	Render::Renderer::GetInstance()->AddLight(ambientLight);
	Render::Renderer::GetInstance()->AddLight(directionalLight);
	Render::Renderer::GetInstance()->AddLight(pointLight);
	Render::Renderer::GetInstance()->AddLight(spotLight);
	//---- ----
	
	posOffset = 0.0f;

	time.Init();
	Input::Initialize(window);

	return 0;
}

void Application::Run()
{
	//Main Loop
	while (window.IsRunning()) {

		//Mandatory code in loop
		time.Update();
		//-----------------------

		/*ROTATION DRAGON*/
		//currentModel->GetTransform()->SetRotation(
		//	glm::vec3(
		//		currentModel->GetTransform()->GetRotation().x,
		//		currentModel->GetTransform()->GetRotation().y + 5.0f * time.GetDeltaTime(),
		//		currentModel->GetTransform()->GetRotation().z
		//	)
		//);
		/*END ROTATION DRAGON*/

		/*DRAGON MOVEMENT*/
		/*float movHor = 0.0f;
		float movFront = 0.0f;
		float movUp = 0.0f;

		if (Input::GetKeyPressed(KEYCODE_D)) movHor += 20.0f;
		if (Input::GetKeyPressed(KEYCODE_A)) movHor -= 20.0f;
		if (Input::GetKeyPressed(KEYCODE_W)) movFront -= 20.0f;
		if (Input::GetKeyPressed(KEYCODE_S)) movFront += 20.0f;
		if (Input::GetKeyPressed(KEYCODE_Q)) movUp -= 20.0f;
		if (Input::GetKeyPressed(KEYCODE_E)) movUp += 20.0f;

		currentModel->GetTransform()->SetPosition(
			glm::vec3(
				currentModel->GetTransform()->GetPosition().x + movHor * time.GetDeltaTime(),
				currentModel->GetTransform()->GetPosition().y + movUp * time.GetDeltaTime(),
				currentModel->GetTransform()->GetPosition().z + movFront * time.GetDeltaTime()
			)
		);*/
		/*END DRAGON MOVEMENT*/

		//currentCamera->SetLookAtPoint(currentModel->GetTransform()->GetPosition());

		cameraController.Update(time.GetDeltaTime());

		//Mandatory code in loop
		window_refresh_callback(window.GetWindowPointer());

		glfwPollEvents();
		//-----------------------
	}
}

void Application::Close()
{
	window.Destroy();
	glfwTerminate();

	//Remove all this code, using a manager for each type that deletes everything itself @TODO
	if (ambientLight != nullptr)
		delete ambientLight;

	if (pointLight != nullptr)
		delete pointLight;

	if (directionalLight != nullptr)
		delete directionalLight;

	if (spotLight != nullptr)
		delete spotLight;

	if (currentModel != nullptr)
		delete currentModel;

	if (dragonTexture != nullptr)
		delete dragonTexture;

	if (spotTexture != nullptr)
		delete spotTexture;

	if (basicShaderProgram != nullptr)
		delete basicShaderProgram;

	if (vertexShader != nullptr)
		delete vertexShader;

	if (fragmentShader != nullptr)
		delete fragmentShader;
}

void Application::PrintAppInfo()
{
	std::cout << "X/C: LOCK MOUSE CURSOR/UNLOCK MOUSE CURSOR " << std::endl;
	std::cout << "--" << std::endl;

	std::cout << "CAMERA: " << std::endl;
	std::cout << "-- KEYBOARD --" << std::endl;
	std::cout << "- W/S: FORWARD/BACKWARD: " << std::endl;
	std::cout << "- A/D: LEFT/RIGHT: " << std::endl;
	std::cout << "- Q/E: UP/DOWN: " << std::endl;

	std::cout << "-- MOUSE --" << std::endl;
	std::cout << "- MOVE MOUSE: PAN/TILT " << std::endl;
	std::cout << "- MOVE MOUSE + LEFT CLICK: DOLLY " << std::endl;
	std::cout << "- MOVE MOUSE + RIGHT CLICK: CRANE " << std::endl;
	std::cout << "- MOVE MOUSE + LEFT CLICK + RIGHT CLICK: ORBIT " << std::endl;
	std::cout << "- MOVE MOUSE + MIDDLE CLICK: ZOOM " << std::endl;

	std::cout << "--" << std::endl;

	std::cout << "FUNCTIONS: " << std::endl;
	std::cout << "- 1: LOAD TRIANGLE " << std::endl;
	std::cout << "- 2: LOAD TETRAHEDRO " << std::endl;
	std::cout << "- 3: LOAD COW MODEL " << std::endl;
	std::cout << "- 4: LOAD DICE MODEL " << std::endl;
	std::cout << "- V: REMOVE LAST CREATED MODEL " << std::endl;
	std::cout << "- B: REMOVE OLDER MODEL " << std::endl;
	std::cout << "- N: REMOVE ALL MODELS " << std::endl;
	std::cout << "- F: ACTIVE SOLID MODE " << std::endl;
	std::cout << "- G: ACTIVE WIREFRAME MODE " << std::endl;
	std::cout << "- H: ACTIVE TEXTURE MODE " << std::endl;
	std::cout << "- J: DEACTIVATE NORMAL MAPPING " << std::endl;
	std::cout << "- K: ACTIVATE NORMAL MAPPING " << std::endl;
}

void Application::Refresh()
{
	try {
		Render::Renderer::GetInstance()->Refresh();
	}
	catch (std::exception& e) {
		const std::string message = " - in function Refresh()";
		std::cout << e.what() << std::endl;
		window.Close();
	}

	window.SwapBuffers();
}

void Application::ResizeWindow(GLint width, GLint height) {
	Render::Renderer::GetInstance()->SetWindowViewport(width, height);
}

void Application::KeyPressed(GLint key, GLint action) {
	if (action == GLFW_PRESS) {
		switch (key) {
		case GLFW_KEY_C: //Clamp the cursor in the screen.
			window.SetCursorLocked(false);
			break;

		case GLFW_KEY_X: //Free the cursor in the screen.
			window.SetCursorLocked(true);
			break;

		case GLFW_KEY_2: //Create a Tetrahedron Model
		{
			posOffset += 2.5f;
			Render::Model* newModel = new Render::Model(Render::MODEL_TYPE::TETRAHEDRON, basicMaterial);
			newModel->GetTransform()->SetPosition(glm::vec3(posOffset, 0, 0));

			Render::Renderer::GetInstance()->AddModel(newModel);
			std::cout << "Tetrahedron Model Loaded" << std::endl;
		}
		break;

		case GLFW_KEY_1: //Create a Triangle Model
		{
			posOffset += 2.5f;
			Render::Model* newModel = new Render::Model(Render::MODEL_TYPE::TRIANGLE, basicMaterial);
			newModel->GetTransform()->SetPosition(glm::vec3(posOffset, 0, 0));

			Render::Renderer::GetInstance()->AddModel(newModel);
			std::cout << "Triangle Model Loaded" << std::endl;
		}
		break;

		case GLFW_KEY_3: //Create a Spot Model
		{
			posOffset += 2.5f;
			Render::Model* newModel = Render::Model::CreateModel("Assets/spot.obj", spotMaterial);
			newModel->GetTransform()->SetPosition(glm::vec3(posOffset, 0.0f, 0.0f));
			newModel->GetTransform()->SetRotation(glm::vec3(-90.0f, 0.0f, 0.0f));
			newModel->GetTransform()->SetScale(glm::vec3(0.75f, 0.75f, 0.75f));

			Render::Renderer::GetInstance()->AddModel(newModel);
			std::cout << "Cow Model Loaded" << std::endl;
		}
		break;

		case GLFW_KEY_4: //Create a Dice model
		{
			posOffset += 2.5f;
			Render::Material* newMaterial = Render::Material::CreateMaterial(Render::Color(0.1f, 0.3f, 0.7f), Render::Color(0.1f, 0.3f, 0.7f), Render::Color(1.0f, 1.0f, 1.0f), 8.0f);
			newMaterial->SetColorTexture(Render::Texture::CreateTexture("Assets/dado.png"));
			newMaterial->SetNormalTexture(Render::Texture::CreateTexture("Assets/dadoNormalMap.png"));
			newMaterial->SetShaderProgram(basicShaderProgram);
			newMaterial->SetShaderProgramNormalMap(normalShaderProgram);
			Render::Model* newModel = new Render::Model("Assets/dado.obj", newMaterial);
			newMaterial->SetNormalMapActive(true);
			newModel->GetTransform()->SetPosition(glm::vec3(posOffset, 0.0f, 0.0f));

			Render::Renderer::GetInstance()->AddModel(newModel);
			std::cout << "Dice Model Loaded" << std::endl;
		}
		break;

		case GLFW_KEY_N: //Deletes all models and show no one
		{
			posOffset = -2.5f;
			Render::Renderer::GetInstance()->RemoveAllModels();

			std::cout << "Models Removed" << std::endl;
		}
		break;

		case GLFW_KEY_B: //Deletes the older model in the scene
		{
			posOffset -= 2.5f;
			Render::Renderer::GetInstance()->RemoveFirstModel();

			std::cout << "First Model Removed" << std::endl;
		}
		break;

		case GLFW_KEY_V: //Deletes the last added model
		{
			Render::Renderer::GetInstance()->RemoveLastModel();

			std::cout << "Last Model Removed" << std::endl;
		}
		break;

		case GLFW_KEY_F:
			Render::Renderer::GetInstance()->SetModelRepresentationToSolid();
			break;

		case GLFW_KEY_H:
			Render::Renderer::GetInstance()->SetModelRepresentationToTexture();
			break;

		case GLFW_KEY_G:
			Render::Renderer::GetInstance()->SetModelRepresentationToWireframe();
			break;

		case GLFW_KEY_J:
			dragonMaterial->SetNormalMapActive(false);
			break;

		case GLFW_KEY_K:
			dragonMaterial->SetNormalMapActive(true);
			break;

		case GLFW_KEY_ESCAPE: //Close the application
			window.Close();
			break;

		default:
			break;
		}
	}

	window_refresh_callback(window.GetWindowPointer());
}

void Application::MousePressed(GLint button, GLint action) 
{
	//MOUSE BUTTON EVENTS
}

void Application::MouseMovement(GLdouble xpos, GLdouble ypos)
{
	//MOUSE MOVEMENT EVENTS
}

void Application::MouseScroll(GLdouble xoffset, GLdouble yoffset)
{
	Render::Color& bgColor = Render::Renderer::GetInstance()->GetBackgroundColor();

	bgColor.SetColor(
		bgColor[Render::R] + COLOR_MOUSE_WHEEL_MULTIPLIER * yoffset,
		bgColor[Render::G] + COLOR_MOUSE_WHEEL_MULTIPLIER * yoffset,
		bgColor[Render::B] + COLOR_MOUSE_WHEEL_MULTIPLIER * yoffset
	);

	Render::Renderer::GetInstance()->SetBackgroundColor(bgColor);

	window_refresh_callback(window.GetWindowPointer());
}
