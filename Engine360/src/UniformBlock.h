#pragma once
#include <map>

class Shader;
#include "glm/fwd.hpp"

struct SignleUniform
{
	SignleUniform(const void* data, size_t size, size_t sizeBefore)
	{
		this->data = data, this->size = size, this->sizeBefore = sizeBefore;
		oldData = malloc(size);
	}
	SignleUniform() = default;
	const void* data = nullptr;
	void* oldData = nullptr;
	size_t size = 0;
	size_t sizeBefore = 0;
};

class UniformBlock
{
public:
	UniformBlock(const char* blockName, unsigned int bindingPoint, Shader* shader = nullptr, bool isStatic = true);
	~UniformBlock();

	template <typename T>
	void InsertData(const char* uniformName, const void* data);
	void EditData(const char* name, const void* data);

	void SetShader(Shader* shader);

	void Bind();
	void UpdateBlockUniform();
private:
	unsigned int ubID = 0;
	unsigned int bindingPoint = 0;
	const char* blockName = "";

	std::map<const char*, SignleUniform> blockData;
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
	SignleUniform singleUniform{ data, size, blockSize };
	blockData[uniformName] = singleUniform;

	blockSize += size;
}