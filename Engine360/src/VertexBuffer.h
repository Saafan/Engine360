#pragma once

#include <vector>
#include "Helpers/Printer.h"

class VertexBuffer
{
public:
	VertexBuffer(const void* data, size_t size, bool interleaved = true);
	VertexBuffer(const void* data, size_t size, const void* indicies, size_t indicesSize, bool interleaved = true);
	template<typename type> void InsertStride(int count);
	template<typename type, unsigned int verticesCount> void InsertStride(int count);
	template<typename type, unsigned int& verticesCount> void InsertStride(int count);
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
	const size_t GetStrideSize();
	std::vector<Type> strides;
};

template<typename type>
void VertexBuffer::InsertStride(int count)
{
	Type strideDetails = ConvertTypeToGLType<type>();
	strideDetails.count = count;
	strides.emplace_back(strideDetails);
};

template<typename type, unsigned int verticesCount>
void VertexBuffer::InsertStride(int count)
{
	Type strideDetails = ConvertTypeToGLType<type>();
	strideDetails.count = count;
	strideDetails.elementsCount = verticesCount * count;
	strides.emplace_back(strideDetails);
}

template<typename type, unsigned int& verticesCount>
void VertexBuffer::InsertStride(int count)
{
	Type strideDetails = ConvertTypeToGLType<type>();
	strideDetails.count = count;
	strideDetails.elementsCount = verticesCount * count;
	strides.emplace_back(strideDetails);
}