#pragma once
#include "Uniform.h"
class Texture
{
public:
	Texture(const char* path, int slot = 0);
	~Texture();
	void Bind();
	void Bind(int slot);
	void UnBind();
	void SetSlot(int slot);

private:
	int width = 0, height = 0, bytePerPixel = 0;
	unsigned int textureID = 0;
	int slot = 0;
	unsigned char* textureData = 0;
	Uniform<int>* textureSlot;
	
};