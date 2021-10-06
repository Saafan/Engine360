#pragma once
#include <map>

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
	UniformBlock(const char* blockName, unsigned int bindingPoint, bool isStatic = true);
	~UniformBlock();
	void InsertData(const char* uniformName, const void* data, size_t size);
	void EditData(const char* name,const void* data);
	void Bind();
	void UpdateBlockUniform();
private:
	unsigned int ubID = 0;
	unsigned int bindingPoint = 0;
	const char* blockName = "";

	std::map<const char*, SignleUniform> blockData;
	unsigned int drawingFlag  = 0x88E4;
	size_t blockSize = 0;
};
