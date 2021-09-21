#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, size_t size, bool interleaved)
{
	this->data = data;
	this->size = size;

	glGenVertexArrays(1, &vaID);
	glGenBuffers(1, &vbID);
	this->interleaved = interleaved;
}

VertexBuffer::VertexBuffer(const void* data, size_t size, const void* indices, size_t indicesSize, bool interleaved) : VertexBuffer(data, size)
{
	this->indices = indices;
	this->indicesSize = indicesSize;

	glGenBuffers(1, &ibID);
	this->interleaved = interleaved;
}

void VertexBuffer::Bind()
{
	glBindVertexArray(vaID);
}

void VertexBuffer::BindData()
{
	glBindVertexArray(vaID);
	glBindBuffer(GL_ARRAY_BUFFER, vbID);

	glBufferData(GL_ARRAY_BUFFER, size, interleaved ? data : 0, GL_STATIC_DRAW);
	if (!interleaved)
	{
		size_t offset = 0;
		for (const auto& stride : strides)
		{
			const size_t strideSize = stride.elementsCount * stride.size;
			const unsigned int offsetSize = (size_t)data + offset;
			glBufferSubData(GL_ARRAY_BUFFER, offset, strideSize, (const void*)offsetSize);
			offset += strideSize;
		}
	}

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
	for (size_t i = 0; i < strides.size(); i++)
	{
		const Type& curStride = strides.at(i);
		const unsigned int strideSize = interleaved ? GetStrideSize() : curStride.count * curStride.size;
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, curStride.count, curStride.type, GL_FALSE, strideSize, (const void*)offset);
		offset += (interleaved ? curStride.count : curStride.elementsCount) * curStride.size;
	}
}


const size_t VertexBuffer::GetStrideSize()
{
	size_t size = 0;
	for (const auto& stride : strides)
		size += stride.size * stride.count;

	return size;
}