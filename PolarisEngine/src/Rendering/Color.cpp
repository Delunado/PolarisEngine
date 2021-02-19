#include "Color.h"

namespace Render {
	Color::Color(float r, float g, float b, float a): overflowManagementMode(COLOR_OVERFLOW_MANAGEMENT::SCALE)
	{
		SetColor(r, g, b);
		SetAlpha(a);
	}

	Color::Color(const Color& other)
	{
		this->colorData = other.colorData;
		this->overflowManagementMode = other.overflowManagementMode;
	}

	Color::~Color()
	{
	}

	glm::vec4 Color::GetData() const
	{
		return colorData;
	}

	void Color::SetColor(float r, float g, float b)
	{
		colorData[R] = r;
		colorData[G] = g;
		colorData[B] = b;

		ManageColorOverflow();
	}

	void Color::SetAlpha(float a)
	{
		colorData[A] = a;
	}

	void Color::SetColorOverflowManagement(COLOR_OVERFLOW_MANAGEMENT overflowManagementMode)
	{
		this->overflowManagementMode = overflowManagementMode;
	}

	void Color::ManageColorOverflow()
	{
		for (int i = 0; i < 3; i++) {
			colorData[i] = (colorData[i] < 0.0f) ? 0.0f : colorData[i];
		}

		switch (overflowManagementMode)
		{

		case COLOR_OVERFLOW_MANAGEMENT::SCALE:
		{
			int biggestColorId = -1;
			float biggestColorValue = 0.0f;

			for (int i = 0; i < 3; i++) {
				if (colorData[i] > 1.0f && colorData[i] > biggestColorValue) {
					biggestColorId = i;
					biggestColorValue = colorData[i];
				}
			}

			if (biggestColorId != -1) {
				for (int j = 0; j < 3; j++) {
					colorData[j] /= biggestColorValue;
				}
			}

		}

			break;

		case COLOR_OVERFLOW_MANAGEMENT::CLAMP:
		{
			for (int i = 0; i < 3; i++) {
				colorData[i] = (colorData[i] > 1.0f) ? 1.0f : colorData[i];
			}
		}

			break;

		default:
			break;
		}
	}

	float Color::operator[](const int id)
	{
		return colorData[id];
	}

	Color Color::RED(1.0f, 0.0f, 0.0f);
	Color Color::GREEN(0.0f, 1.0f, 0.0f);
	Color Color::BLUE(0.0f, 0.0f, 1.0f);
	Color Color::BLACK(0.0f, 0.0f, 0.0f);
	Color Color::WHITE(1.0f, 1.0f, 1.0f);
	Color Color::GREY(0.5f, 0.5f, 0.5f);
}
