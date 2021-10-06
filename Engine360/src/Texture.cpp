#include "Texture.h"
#include "Renderer/Renderer.h"
#include "stb_image/stb_image.h"

Texture::Texture(const char* path, int slot)
{
	stbi_set_flip_vertically_on_load(true);
	textureData = stbi_load(path, &width, &height, &bytePerPixel, 0);
	glGenTextures(1, &textureID);
	Bind(slot);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
	glGenerateMipmap(GL_TEXTURE_2D);

	UnBind();

	if (textureData)
		stbi_image_free(textureData);
	else
		std::cout << "Texture File is Not Found" << std::endl;

	textureSlot = new Uniform<int>(SHADER_TEXTURE_SLOT, &(this->slot), Renderer::Get().curShader);
}

Texture::~Texture()
{
	glDeleteTextures(1, &textureID);
}

void Texture::SetSlot(int slot)
{
	this->slot = slot;
}

void Texture::Bind(int slot)
{
	this->slot = slot;
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::Bind()
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::UnBind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}