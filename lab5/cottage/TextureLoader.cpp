#include "TextureLoader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// устранить рябь на текстурах
// выяснить что такое z-fighting хорошо это или плохо как усилить или избавиться
// для чего нужна нормаль
// разобраться что такое фильтрация текстур
// разобраться с WRAP, когда имеет смысл исполььзовать

// сгенерировать mipmap'ы
Texture TextureLoader::LoadTexture(std::string const& fileName, GLuint level) const
{
	int width, height, nrChannels;
	unsigned char* data = stbi_load(fileName.c_str(), &width, &height, &nrChannels, STBI_rgb);

	if (!data)
	{
		throw std::runtime_error("Failed to load texture");
	}

	GLuint textureName = 0;
	glGenTextures(1, &textureName);
	glBindTexture(GL_TEXTURE_2D, textureName);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_magFilter);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_wrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_wrapT);

	glTexImage2D(GL_TEXTURE_2D, level, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	stbi_image_free(data);

	return Texture(textureName);
}
