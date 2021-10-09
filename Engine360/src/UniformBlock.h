#pragma once

#include <vector>

class Shader;
#include "glm/fwd.hpp"

struct SingleUniform
{
	SingleUniform(const void* data, size_t size, size_t sizeBefore, size_t actualSize)
	{
		this->data = data, this->size = size, this->sizeBefore = sizeBefore, this->actualSize = actualSize;
		oldData = malloc(size);
		memcpy(oldData, data, actualSize);
	}
	SingleUniform() = default;
	const void* data = nullptr;
	void* oldData = nullptr;
	size_t size = 0;
	size_t actualSize = 0;
	size_t sizeBefore = 0;
};

class UniformBlock
{
public:
	UniformBlock(const char* blockName, unsigned int bindingPoint, Shader* shader = nullptr, bool isStatic = true);
	~UniformBlock();

	template <typename T>
	void InsertData(const char* uniformName, const void* data);
	void EditData(SingleUniform& uniform, const void* data);


	void Bind();
	void UnBind();

	void UpdateBlockUniform();
private:
	unsigned int ubID = 0;
	unsigned int bindingPoint = 0;
	const char* blockName = "";

	std::vector<std::pair<const char*, SingleUniform>> blockData;
	unsigned int drawingFlag = 0x88E4;
	size_t blockSize = 0;
};

template <typename T>
inline
void UniformBlock::InsertData(const char* uniformName, const void* data)
{
	size_t size = sizeof(T);
	if (typeid(T) == typeid(glm::vec3))
		size = sizeof(glm::vec4);
	SingleUniform singleUniform{ data, size, blockSize, sizeof(T) };
	blockData.emplace_back(std::pair<const char*, SingleUniform>(uniformName, singleUniform));

	blockSize += size >= 16 ? size : 16;
}