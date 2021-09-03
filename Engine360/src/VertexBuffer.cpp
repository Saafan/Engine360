#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, size_t size)
{
	this->data = data;
	this->size = size;

	glGenVertexArrays(1, &vaID);
	glGenBuffers(1, &vbID);
}

VertexBuffer::VertexBuffer(const void* data, size_t size, const void* indices, size_t indicesSize) : VertexBuffer(data, size)
{
	this->indices = indices;
	this->indicesSize = indicesSize;

	glGenBuffers(1, &ibID);
}

void VertexBuffer::Bind()
{
	static bool first = true;
	if (first)
	{
		BindData();
		first = false;
	}
	else
		glBindVertexArray(vaID);
}

void VertexBuffer::BindData()
{
	glBindVertexArray(vaID);

	glBindBuffer(GL_ARRAY_BUFFER, vbID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

	if (ibID != 0)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);
	}

	AttributesBind();
}

void VertexBuffer::SetVertexData(const void* data, size_t size)
{
	this->data = data;
	this->size = size;
}

void VertexBuffer::SetIndiciesData(const void* IndicesData, size_t IndicesSize)
{
	this->data = IndicesData;
	this->size = IndicesSize;
}

void VertexBuffer::AttributesBind()
{
	unsigned int offset = 0;
	unsigned int strideSize = GetStrideSize();
	for (size_t i = 0; i < strides.size(); i++)
	{
		Type& curStride = strides.at(i);
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, curStride.count, curStride.type, GL_FALSE, strideSize, (const void*)offset);
		offset += curStride.count * curStride.size;
	}
}

size_t VertexBuffer::GetStrideSize()
{
	size_t size = 0;
	for (const auto & stride : strides)
		size += stride.size * stride.count;

	return size;
}