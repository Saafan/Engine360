#include "UniformBlock.h"
#include "GL/glew.h"
#include "Renderer/Renderer.h"
#include "Shader.h"
#include "glm/glm.hpp"

UniformBlock::UniformBlock(const char* blockName, unsigned int bindingPoint, bool isStatic)
{
	this->blockName = blockName;
	this->bindingPoint = bindingPoint;
	for (const auto& shader : Renderer::Get().shaders)
	{
		const unsigned int programID = shader->GetProgramID();
		const unsigned int blockIndex = glGetUniformBlockIndex(programID, blockName);
		glUniformBlockBinding(programID, blockIndex, bindingPoint);
	}
	drawingFlag = isStatic ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW;
	Renderer::Get().uniformBlocks.emplace_back(this);
}

UniformBlock::~UniformBlock()
{
	std::vector<UniformBlock*>& uniformBlock = Renderer::Get().uniformBlocks;
	for (size_t i = 0; i < uniformBlock.size(); i++)
		if (uniformBlock.at(i) == this)
			uniformBlock.erase(uniformBlock.begin() + i);
}

void UniformBlock::UpdateBlockUniform()
{
	for (auto& uniformBlock : blockData)
	{
		SignleUniform& singleUniform = uniformBlock.second;
			if (memcmp(singleUniform.data, singleUniform.oldData, singleUniform.size) == 0)
			continue;
		memcpy(singleUniform.oldData, singleUniform.data, singleUniform.size);
		EditData(uniformBlock.first, singleUniform.data);
	}
}

void UniformBlock::EditData(const char* name, const void* data)
{
	SignleUniform& uniform = blockData[name];
	glBindBuffer(GL_UNIFORM_BUFFER, ubID);
	void* ptr = glMapBufferRange(GL_UNIFORM_BUFFER, uniform.sizeBefore, uniform.size, GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT);
	memcpy(ptr, data, uniform.size);
	glUnmapBuffer(GL_UNIFORM_BUFFER);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UniformBlock::Bind()
{
	glGenBuffers(1, &ubID);

	glBindBuffer(GL_UNIFORM_BUFFER, ubID);
	glBufferData(GL_UNIFORM_BUFFER, blockSize, NULL, drawingFlag);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	glBindBufferRange(GL_UNIFORM_BUFFER, 0, ubID, 0, blockSize);

	size_t offset = 0;
	for (const auto& data : blockData)
	{
		glBindBuffer(GL_UNIFORM_BUFFER, ubID);
		glBufferSubData(GL_UNIFORM_BUFFER, offset, data.second.size, data.second.data);
		offset += data.second.size;
	}
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UniformBlock::InsertData(const char* uniformName, const void* data, size_t size)
{
	SignleUniform singleUniform{ data, size, blockSize };
	blockData[uniformName] = singleUniform;
	blockSize += size;
}