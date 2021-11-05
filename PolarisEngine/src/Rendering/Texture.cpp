#include <GL/glew.h>
#include <iostream>

#include "lodepng.h"
#include <png.hpp>
#include "Texture.h"

namespace Render {

	Texture::Texture(std::string texturePath) : width(0), height(0), image(std::vector<unsigned char>()), id(0)
	{
		try {
			Load(texturePath);
		}
		catch (std::exception & e) {
			const std::string message = " - in function Texture()";
			throw std::runtime_error(e.what() + message);
		}
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &id);
	}

	Texture* Texture::CreateTexture(std::string texturePath)
	{
		Texture* texture = new Texture(texturePath);
		return texture;
	}

	GLuint Texture::GetID()
	{
		return id;
	}

	void Texture::ActivateTexture(GLint textureLevel)
	{
		if (image.size() <= 0) {
			throw std::runtime_error("There is no image loaded!");
		}

		switch (textureLevel)
		{
		case 0:
			glActiveTexture(GL_TEXTURE0);
			break;
		case 1:
			glActiveTexture(GL_TEXTURE1);
			break;
		default:
			break;
		}

		glBindTexture(GL_TEXTURE_2D, id);
	}

	void Texture::Load(std::string texturePath)
	{
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);

		//Load imag
		GLuint error = lodepng::decode(image, width, height, texturePath);
		//png::image<png::rgb_pixel> image(texturePath);

		if (error) {
			throw std::runtime_error("Can't load texture: " + texturePath);
		}

		//Reverse texture image
		unsigned char* img = &image[0];
		int colorComponents = 4;
		int widthIncrement = 4 * width; //bytes
		unsigned char* top = nullptr;
		unsigned char* bot = nullptr;
		unsigned char temp = 0;

		for (int i = 0; i < height / 2; i++) {
			top = img + i * widthIncrement;
			bot = img + (height-i-1) * widthIncrement;

			for (int j = 0; j < widthIncrement; j++) {
				temp = *top;
				*top = *bot;
				*bot = temp;
				++top;
				++bot;
			}
		}

		//Config texture
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data());

		glGenerateMipmap(GL_TEXTURE_2D);
	}
}
