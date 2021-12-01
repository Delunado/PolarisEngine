#include "Renderer.h"

#include "Shader.h"

#include "Material.h"

#include "Transform.h"

#include "Color.h"
#include "Input.h"
#include "TimeStep.h"

#include "Debug.h"

#include "Application.h"


Application::Application() : isRunning(false), basicShaderProgram(nullptr), ambientLight(nullptr), normalShaderProgram(nullptr),
vertexShader(nullptr), fragmentShader(nullptr), currentModel(nullptr), basicMaterial(nullptr), dragonMaterial(nullptr),
spotMaterial(nullptr), dragonTexture(nullptr), spotTexture(nullptr), pointLight(nullptr), directionalLight(nullptr),
spotLight(nullptr), posOffset(0.0f)
{}

int Application::Init(GLint windowHeight, GLint windowWidth)
{
	isRunning = true;

	window.Init(windowWidth, windowHeight, "Polaris Engine V-0.2");
	window.SetUserPointer(this);

	//Initializing GLEW
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		Log::PrintMessage("Failed to initialize GLEW");
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
	dragonTexture = Render::Texture::CreateTexture("Assets/Borro.png");

	Render::Texture* diceNormalTexture = Render::Texture::CreateTexture("Assets/DragonNormal.png");
	dragonMaterial->SetShaderProgram(basicShaderProgram);
	dragonMaterial->SetShaderProgramNormalMap(normalShaderProgram);

	dragonMaterial->SetColorTexture(dragonTexture);

	dragonMaterial->SetNormalTexture(diceNormalTexture);
	dragonMaterial->SetNormalMapActive(false);

	//Here we create a model and assign it to the renderer.
	currentModel = Render::Model::CreateModel("Assets/Dragon.fbx", dragonMaterial);
	//currentModel->GetTransform()->SetRotation(glm::vec3(-90.0f, 180.0f, 0.0f));
	//currentModel->GetTransform()->SetScale(glm::vec3(0.25f, 0.25f, 0.25f));

	Render::Renderer::GetInstance()->AddModel(currentModel);

	//Now we create a camera and attach it to the renderer.
	Render::Camera* currentCamera = Render::Camera::CreateCamera();
	currentCamera->SetPosition(glm::vec3(0.0f, 0.0f, -40.0f));
	currentCamera->SetAspectRel((GLfloat)windowWidth / (GLfloat)windowHeight);

	Render::Renderer::GetInstance()->SetCurrentCamera(currentCamera);

	//Here we create the lights and add it to the renderer
	ambientLight = new Render::AmbientLight(Render::Color(0.12f, 0.12f, 0.12f));
	directionalLight = new Render::DirectionalLight(glm::vec3(0.0f, 1.0f, 0.0f), Render::Color(0.8f, 0.8f, 0.8f), Render::Color(0.8f, 0.8f, 0.8f));
	pointLight = new Render::PointLight(glm::vec3(0.0f, 1.0f, 0.0f), Render::Color(0.8f, 0.8f, 0.8f), Render::Color(0.8f, 0.8f, 0.8f));
	spotLight = new Render::SpotLight(glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 1.0f), 0.45f, Render::Color(0.8f, 0.8f, 0.8f), Render::Color(0.8f, 0.8f, 0.8f));

	Render::Renderer::GetInstance()->AddLight(ambientLight);
	Render::Renderer::GetInstance()->AddLight(directionalLight);
	Render::Renderer::GetInstance()->AddLight(pointLight);
	Render::Renderer::GetInstance()->AddLight(spotLight);

	//Here we create the skybox. Make it a class!
	//Render::Texture* skyboxTexture = Render::Texture::CreateTexture("Assets/SkyBoxTexture.png");

	//Render::Material* skyboxMaterial = Render::Material::CreateMaterial(Render::Color(0.5f, 0.5f, 0.5f), Render::Color(0.1f, 0.3f, 0.7f), Render::Color(1.0f, 1.0f, 1.0f), 8.0f);
	//skyboxMaterial->SetColorTexture(skyboxTexture);

	//skyboxModel = Render::Model::CreateModel("Assets/SkyBoxModel.obj", skyboxMaterial);
	//Render::Renderer::GetInstance()->AddModel(skyboxModel);

	//---- INIT MODULES ----
	Time::Init();
	Input::Init(window);

	//This sets the cursor to the center of the screen and disable it.
	Input::SetCursorPos(windowWidth / 2.0f, windowHeight / 2.0f);
	Input::SetCursorLocked(true);

	return 0;
}

void Application::Run()
{
	//Main Loop
	while (isRunning) {

		//Mandatory code in loop
		Time::Update();
		Time::FPS();

		//-----------------------

		/*ROTATION DRAGON*/
		currentModel->GetTransform()->SetRotation(
			glm::vec3(
				currentModel->GetTransform()->GetRotation().x,
				currentModel->GetTransform()->GetRotation().y + 5.0f * Time::GetDeltaTime(),
				currentModel->GetTransform()->GetRotation().z
			)
		);
		/*END ROTATION DRAGON*/

		/*DRAGON MOVEMENT*/
		float movHor = 0.0f;
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
				currentModel->GetTransform()->GetPosition().x + movHor * Time::GetDeltaTime(),
				currentModel->GetTransform()->GetPosition().y + movFront * Time::GetDeltaTime(),
				currentModel->GetTransform()->GetPosition().z + movUp * Time::GetDeltaTime()
			)
		);
		/*END DRAGON MOVEMENT*/

		//currentCamera->SetLookAtPoint(currentModel->GetTransform()->GetPosition());

		cameraController.Update(Time::GetDeltaTime());

		//Mandatory code in loop
		window.Update();

		window_refresh_callback(window.GetWindowPointer());

		if (!window.IsRunning()) {
			isRunning = false;
		}
		//-----------------------
	}
}

void Application::Close()
{
	window.Close();
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
	Log::PrintMessage("X/C: LOCK MOUSE CURSOR/UNLOCK MOUSE CURSOR ");
	Log::PrintMessage("--");

	Log::PrintMessage("CAMERA: ");
	Log::PrintMessage("-- KEYBOARD --");
	Log::PrintMessage("- W/S: FORWARD/BACKWARD: ");
	Log::PrintMessage("- A/D: LEFT/RIGHT: ");
	Log::PrintMessage("- Q/E: UP/DOWN: ");

	Log::PrintMessage("-- MOUSE --");
	Log::PrintMessage("- MOVE MOUSE: PAN/TILT ");
	Log::PrintMessage("- MOVE MOUSE + LEFT CLICK: DOLLY ");
	Log::PrintMessage("- MOVE MOUSE + RIGHT CLICK: CRANE ");
	Log::PrintMessage("- MOVE MOUSE + LEFT CLICK + RIGHT CLICK: ORBIT ");
	Log::PrintMessage("- MOVE MOUSE + MIDDLE CLICK: ZOOM ");

	Log::PrintMessage("--");

	Log::PrintMessage("FUNCTIONS: ");
	Log::PrintMessage("- 1: LOAD TRIANGLE ");
	Log::PrintMessage("- 2: LOAD TETRAHEDRO ");
	Log::PrintMessage("- 3: LOAD COW MODEL ");
	Log::PrintMessage("- 4: LOAD DICE MODEL ");
	Log::PrintMessage("- V: REMOVE LAST CREATED MODEL ");
	Log::PrintMessage("- B: REMOVE OLDER MODEL ");
	Log::PrintMessage("- N: REMOVE ALL MODELS ");
	Log::PrintMessage("- F: ACTIVE SOLID MODE ");
	Log::PrintMessage("- G: ACTIVE WIREFRAME MODE ");
	Log::PrintMessage("- H: ACTIVE TEXTURE MODE ");
	Log::PrintMessage("- J: DEACTIVATE NORMAL MAPPING ");
	Log::PrintMessage("- K: ACTIVATE NORMAL MAPPING ");
}

void Application::Refresh()
{
	try {
		Render::Renderer::GetInstance()->Refresh();
	}
	catch (std::exception& e) {
		const std::string message = " - in function Refresh()";
		Log::PrintMessage(e.what());
		window.Close();
	}

	window.SwapBuffers();
}

void Application::ResizeWindow(GLint width, GLint height) {
	Render::Renderer::GetInstance()->SetWindowViewport(width, height);
	window.SetHeight(height);
	window.SetHeight(width);
}

void Application::KeyPressed(GLint key, GLint action) {
	
	if (action == GLFW_PRESS) {
		
		switch (key) {
		case GLFW_KEY_C: //Clamp the cursor in the screen.
			Input::SetCursorLocked(false);
			break;

		case GLFW_KEY_X: //Free the cursor in the screen.
			Input::SetCursorLocked(true);
			break;

		case GLFW_KEY_2: //Create a Tetrahedron Model
		{
			posOffset += 2.5f;
			Render::Model* newModel = new Render::Model(Render::MODEL_TYPE::TETRAHEDRON, basicMaterial);
			newModel->GetTransform()->SetPosition(glm::vec3(posOffset, 0, 0));

			Render::Renderer::GetInstance()->AddModel(newModel);
			Log::PrintMessage("Tetrahedron Model Loaded");
		}
		break;

		case GLFW_KEY_1: //Create a Triangle Model
		{
			posOffset += 2.5f;
			Render::Model* newModel = new Render::Model(Render::MODEL_TYPE::TRIANGLE, basicMaterial);
			newModel->GetTransform()->SetPosition(glm::vec3(posOffset, 0, 0));

			Render::Renderer::GetInstance()->AddModel(newModel);
			Log::PrintMessage("Triangle Model Loaded");
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
			Log::PrintMessage("Cow Model Loaded");
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
			Log::PrintMessage("Dice Model Loaded");
		}
		break;

		case GLFW_KEY_N: //Deletes all models and show no one
		{
			posOffset = -2.5f;
			Render::Renderer::GetInstance()->RemoveAllModels();

			Log::PrintMessage("Models Removed");
		}
		break;

		case GLFW_KEY_B: //Deletes the older model in the scene
		{
			posOffset -= 2.5f;
			Render::Renderer::GetInstance()->RemoveFirstModel();

			Log::PrintMessage("First Model Removed");
		}
		break;

		case GLFW_KEY_V: //Deletes the last added model
		{
			Render::Renderer::GetInstance()->RemoveLastModel();

			Log::PrintMessage("Last Model Removed");
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
			isRunning = false;
			break;

		default:
			break;
		}
	}

	//window_refresh_callback(window.GetWindowPointer());
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
