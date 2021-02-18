#pragma once

namespace TEA {
	enum class CAMERA_MOV_DIR
	{
		FORWARD,
		RIGHTWARD,
		UPWARD
	};

	class Camera
	{
	private:
		glm::vec3 position;
		glm::vec3 lookAtPoint;

		glm::vec3 worldUp;

		glm::vec3 front;
		glm::vec3 right;
		glm::vec3 up;

		GLfloat aspectRel;

		GLfloat fovY;
		GLfloat fovX;

		GLfloat zNear;
		GLfloat zFar;

		glm::mat4 visionMatrix;
		glm::mat4 projectionMatrix;

		/// <summary>
		/// Calculate the FovX based on the current FovY.
		/// </summary>
		void CalculateVisionAngle();

		/// <summary>
		/// Calculate the camera's Front, Right and Up vectors.
		/// </summary>
		void CalculateLocalVectors();

		void CalculateVisionMatrix();
		void CalculateProjectionMatrix();

		/// <summary>
		/// Returns the corresponding camera's vector Up.
		/// </summary>
		/// <returns></returns>
		glm::vec3 VectorUp();

	public:
		Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, -2.5f), glm::vec3 lookAtPoint = glm::vec3(0, 0, 0), GLfloat aspectRel = (1024 / 576));

		Camera(const Camera &other);

		~Camera();

		static Camera* CreateCamera(glm::vec3 position = glm::vec3(0.0f, 0.0f, -2.5f), glm::vec3 lookAtPoint = glm::vec3(0, 0, 0), GLfloat aspectRel = (1024 / 576));

		//------ CAMERA MOVEMENT ------

		/// <summary>
		/// Move the camera in the given direction at given speed.
		/// </summary>
		/// <param name="movement"></param>
		/// <param name="speed"></param>
		void Move(CAMERA_MOV_DIR movementDir, GLfloat speed);

		void Zoom(GLfloat zoom);

		/// <summary>
		/// Rotate the camera X and Y degrees around itself.
		/// </summary>
		/// <param name="degreesX"></param>
		/// <param name="degreesY"></param>
		void Rotate(GLfloat degreesX, GLfloat degreesY);

		/// <summary>
		/// Rotate the camera X and Y degrees around a given point.
		/// </summary>
		/// <param name="degreesX"></param>
		/// <param name="degreesY"></param>
		/// <param name="rotationPoint"></param>
		void RotateAround(GLfloat degreesX, GLfloat degreesY, glm::vec3 rotationPoint);

		//------ GETTERS ------

		glm::vec3 GetPosition();
		glm::vec3 GetLookAtPoint();
		glm::vec3 GetWorldUp();

		glm::vec3 GetFront();
		glm::vec3 GetRight();
		glm::vec3 GetUp();

		GLfloat GetFieldOfViewX();
		GLfloat GetFieldOfViewY();

		GLfloat GetZNear();
		GLfloat GetZFar();

		GLfloat GetAspectRel();

		glm::mat4 GetVisionMatrix();
		glm::mat4 GetProjectionMatrix();


		//------ SETTERS ------

		void SetPosition(glm::vec3 position);
		void SetLookAtPoint(glm::vec3 lookAtPoint);
		void SetWorldUp(glm::vec3 worldUp);

		void SetFieldOfViewX(GLfloat fovX);
		void SetFieldOfViewY(GLfloat fovY);

		void SetZNear(GLfloat zNear);
		void SetZFar(GLfloat zFar);

		void SetAspectRel(GLfloat aspecRel);
	};
}