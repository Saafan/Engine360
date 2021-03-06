#include "UniformBlock.h"
#include "Renderer/Renderer.h"
#include "Shader.h"
#include "glm/glm.hpp"

UniformBlock::UniformBlock(const char* blockName, unsigned int bindingPoint, Shader* shader, bool isStatic)
{
	this->blockName = blockName;
	this->bindingPoint = bindingPoint;
	for (auto& shaderRef : Renderer::Get().shaders)
	{
		if (shader)
			shaderRef = shader;

		const unsigned int programID = shaderRef->GetProgramID();
		const unsigned int blockIndex = glGetUniformBlockIndex(programID, blockName);

		if (blockIndex == GL_INVALID_INDEX)
		{
			std::cout << "Uniform Block " << blockName << " doesn't exist in Shader[ " << shaderRef->GetName() << " ]" << std::endl;
			continue;
		}

		glUniformBlockBinding(programID, blockIndex, bindingPoint);
		if (shader)
			break;
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
		SingleUniform& singleUniform = uniformBlock.second;
		if (memcmp(singleUniform.data, singleUniform.oldData, singleUniform.size) == 0)
			continue;
		memcpy(singleUniform.oldData, singleUniform.data, singleUniform.actualSize);
		EditData(singleUniform, singleUniform.data);
	}
}

void UniformBlock::Report()
{
	for (const auto& data : blockData)
	{
		std::cout << "Name: " << data.first << "\nData: " << std::endl;
		PrintValue(data.second.dataType, data.second.data);
	}
}

void UniformBlock::EditData(SingleUniform& uniform, const void* data)
{
	glBindBuffer(GL_UNIFORM_BUFFER, ubID);
	void* ptr = glMapBufferRange(GL_UNIFORM_BUFFER, uniform.sizeBefore, uniform.size, GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT);
	if (!ptr)
		glCheckError();
	memcpy(ptr, data, uniform.actualSize);
	glUnmapBuffer(GL_UNIFORM_BUFFER);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UniformBlock::Bind()
{
	glGenBuffers(1, &ubID);

	glBindBuffer(GL_UNIFORM_BUFFER, ubID);
	glBufferData(GL_UNIFORM_BUFFER, blockSize, NULL, drawingFlag);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	glBindBufferRange(GL_UNIFORM_BUFFER, bindingPoint, ubID, 0, blockSize);

	size_t offset = 0;
	for (const auto& data : blockData)
	{
		glBindBuffer(GL_UNIFORM_BUFFER, ubID);
		glBufferSubData(GL_UNIFORM_BUFFER, offset, data.second.size, data.second.data);
		offset += data.second.size >= 16 ? data.second.size : 16;
	}
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UniformBlock::UnBind()
{
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
