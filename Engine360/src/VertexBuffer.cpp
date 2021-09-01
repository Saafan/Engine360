#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	this->data = data;
	this->size = size;
	glGenVertexArrays(1, &vaID);
	glGenBuffers(1, &vbID);
}

void VertexBuffer::Bind()
{
	glBindVertexArray(vaID);

	glBindBuffer(GL_ARRAY_BUFFER, vbID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

	AttributesBind();
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
	for (size_t i = 0; i < strides.size(); i++)
	{
		size += strides.at(i).size * strides.at(i).count;
	}
	return size;
}
