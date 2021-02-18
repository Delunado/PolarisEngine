#pragma once

#include <glm/glm.hpp>

namespace TEA {
	typedef enum COLOR_INDICES{
		R = 0,
		G = 1,
		B = 2,
		A = 3
	};

	enum class COLOR_OVERFLOW_MANAGEMENT
	{
		SCALE,
		CLAMP
	};

	class Color
	{
	private:
		COLOR_OVERFLOW_MANAGEMENT overflowManagementMode;

		glm::vec4 colorData;

		void ManageColorOverflow();

	public:
		Color(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f);

		Color(const Color& other);

		~Color();

		glm::vec4 GetData() const;

		void SetColor(float r, float g, float b);
		void SetAlpha(float a);

		//Sets how we want the color to manage it's overflow
		void SetColorOverflowManagement(COLOR_OVERFLOW_MANAGEMENT overflowManagementMode);

		//Only read
		float operator[](const int id);

		static Color RED;
		static Color GREEN;
		static Color BLUE;
		static Color BLACK;
		static Color WHITE;
		static Color GREY;
	};
}