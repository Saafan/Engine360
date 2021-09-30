#pragma once

class Shader;

class UniformBase
{
public:
	UniformBase(const char* name, void (*setShaderUniformFunc)());
	unsigned int GetUniformLocation();
	void UpdateShaderUniform();
	bool isChanged = true;
	bool isStatic = false;

protected:
	unsigned int uniformLocation = 0;
	Shader* shader = nullptr;
	const char* name = "NULL";
	void (*setShaderUniformFunc)();
};


template <typename type>
class Uniform : public UniformBase
{
public:
	Uniform(const char* name, type* dataPtr, Shader* shader, bool isStatic = false);
	Uniform(const char* name, type data, Shader* shader, bool isStatic = false);
	void SetData(type* dataPtr);
	void SetData(type data);
	void UpdateShaderUniform();

private:
	void UpdateShaderUniformHelper();
	type data;
	type oldData;
	bool referenceExist = false;
};