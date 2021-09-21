#pragma once

#include <vector>
#include "GL/glew.h"

struct Type
{
	Type(unsigned int type, size_t size) { this->type = type; this->size = size; };
	unsigned int type = 0;
	size_t size = 0;
	size_t elementsCount = 0;
	unsigned int count = 0;
};


class VertexBuffer
{
public:
	VertexBuffer(const void* data, size_t size, bool interleaved = true);
	VertexBuffer(const void* data, size_t size, const void* indicies, size_t indicesSize, bool interleaved = true);
	template<typename type> void InsertStride(int count);
	template<typename type, unsigned int elementsCount> void InsertStride(int count);
	void Bind();
	void BindData();

	void SetVertexData(const void* data, size_t size);
	void SetIndiciesData(const void* data, size_t size);

private:
	unsigned int vbID = 0;
	unsigned int vaID = 0;
	unsigned int ibID = 0;

	const void* data = nullptr;
	size_t size = 0;

	const void* indices = nullptr;
	size_t indicesSize = 0;

	bool interleaved = true;

	void AttributesBind();
	size_t GetStrideSize();
	std::vector<Type> strides;
};

template <typename type>
static Type ConvertTypeToGLType()
{
	if (typeid(type) == typeid(float)) return Type(GL_FLOAT, sizeof(type));
	if (typeid(type) == typeid(unsigned int)) return Type(GL_UNSIGNED_INT, sizeof(type));
	if (typeid(type) == typeid(int)) return Type(GL_INT, sizeof(type));
	if (typeid(type) == typeid(double)) return Type(GL_DOUBLE, sizeof(type));
	if (typeid(type) == typeid(short)) return Type(GL_SHORT, sizeof(type));
	if (typeid(type) == typeid(unsigned short)) return Type(GL_UNSIGNED_SHORT, sizeof(type));
	if (typeid(type) == typeid(char)) return Type(GL_BYTE, sizeof(type));
	if (typeid(type) == typeid(unsigned char)) return Type(GL_UNSIGNED_BYTE, sizeof(type));
	return Type(GL_INT, 4);
}


template<typename type>
void VertexBuffer::InsertStride(int count)
{
	Type strideDetails = ConvertTypeToGLType<type>();
	strideDetails.count = count;
	strides.emplace_back(strideDetails);

};

template<typename type, unsigned int elementCount>
void VertexBuffer::InsertStride(int count)
{
	Type strideDetails = ConvertTypeToGLType<type>();
	strideDetails.count = count;
	strideDetails.elementsCount = elementCount;
	strides.emplace_back(strideDetails);
}