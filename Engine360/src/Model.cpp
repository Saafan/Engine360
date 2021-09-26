#include "Model.h"

#include "gtc/matrix_transform.hpp"
#include "Data/ModelVertices.h"
#include "Renderer/Renderer.h"

void Model::Model::Render()
{
	vb->Bind();

	Renderer::Get().curShader->SetUniformMat4(SHADER_MODEL, model);
	if (indexed)
		glDrawElements(drawTarget, count, GL_UNSIGNED_INT, nullptr);
	else
		glDrawArrays(drawTarget, 0, count);
}

void Model::Model::SetPosition(glm::vec3 value)
{
	model = glm::translate(glm::mat4(1.0f), value);
}

void Model::Model::SetPosition(float v1, float v2, float v3)
{
	model = glm::translate(model, glm::vec3(v1, v2, v3));
}

Model::Model::Model()
{
	Renderer::Get().models.push_back(this);
}

Model::Model::~Model()
{
	std::vector<Model*>& models = Renderer::Get().models;
	for (size_t i = 0; i < models.size(); i++)
		if (models.at(i) == this)
			models.erase(models.begin() + i);
}

void Model::Model::SetDrawAttributes(bool indexed, unsigned int count, unsigned int drawTarget)
{
	vb->Bind();
	this->indexed = indexed;
	this->count = count;
	this->drawTarget = drawTarget;
}

Model::Cube::Cube(float length, float width, float height, bool visible /*= true*/)
{
	float data[] = CUBE_DATA(length, width, height);

	vb = new VertexBuffer(data, sizeof(data));
	vb->InsertStride<float>(3);
	vb->InsertStride<float>(3);
	vb->InsertStride<float>(2);
	vb->BindData();
	SetDrawAttributes(false, CUBE_VERTICES_COUNT, GL_TRIANGLES);
	this->visible = visible;
}


Model::Cylinder::Cylinder(float radius, float height, unsigned int sides, bool visible)
{
	std::vector<glm::vec3> vertices;
	vertices.reserve((360 / sides) * 2);
	vertices.emplace_back(0.0f, height / 2.0f, 0.0f);
	vertices.emplace_back(0.0f, -(height / 2.0f), 0.0f);

	std::vector<unsigned int> indices;
	indices.reserve((360 / sides) * 4);
	std::vector<glm::vec3> topCap;
	std::vector<glm::vec3> bottomCap;
	size_t counter = 2;
	for (float i = 0; i <= 360; i += 360.0f / sides)
	{
		glm::vec3 vertTop(glm::cos(glm::radians(i)), height / 2.0f, glm::sin(glm::radians(i)));
		glm::vec3 vertBottom(glm::cos(glm::radians(i)), -height / 2.0f, glm::sin(glm::radians(i)));
		vertices.emplace_back(vertTop * radius);
		vertices.emplace_back(vertBottom * radius);

		topCap.emplace_back(vertTop * radius);
		bottomCap.emplace_back(vertBottom * radius);
		if (i != 0)
		{
			//Cylinder Sides
			indices.emplace_back(counter);
			indices.emplace_back(counter + 1);
			indices.emplace_back(counter + 3);
			indices.emplace_back(counter + 2);

			counter += 2;
		}
	}

	indices.emplace_back(counter++);
	indices.emplace_back(counter++);
	indices.emplace_back(2);
	indices.emplace_back(3);

	const size_t sideVerticesCount = vertices.size();

	vertices.insert(vertices.end(), topCap.begin(), topCap.end());
	vertices.insert(vertices.end(), bottomCap.begin(), bottomCap.end());

	vertices.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	vertices.push_back(glm::vec3(0.0f, -1.0f, 0.0f));

	for (size_t i = 2; i < sideVerticesCount; i += 2)
	{
		vertices.push_back(glm::normalize(vertices.at(i) - vertices.at(0)));
		vertices.push_back(glm::normalize(vertices.at(i + 1) - vertices.at(1)));
	}

	std::vector<glm::vec3> topNormals;
	std::vector<glm::vec3> bottomNormals;
	for (size_t i = 0; i < topCap.size(); i++)
	{
		topNormals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
		bottomNormals.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
	}

	for (size_t i = 0; i < topCap.size() / 2; i++)
	{
		indices.push_back(counter++);
		indices.push_back(counter++);
		indices.push_back(counter);
		indices.push_back(0);
	}
	counter++;
	for (size_t i = 0; i < bottomCap.size() / 2; i++)
	{
		indices.push_back(counter++);
		indices.push_back(counter++);
		indices.push_back(counter);
		indices.push_back(1);
	}


	vertices.insert(vertices.end(), topNormals.begin(), topNormals.end());
	vertices.insert(vertices.end(), bottomNormals.begin(), bottomNormals.end());

	static unsigned int verticesSize = vertices.size() / 2;
	vb = new VertexBuffer(&vertices.at(0), sizeof(float) * vertices.size() * 3, &indices.at(0), sizeof(unsigned int) * indices.size(), false);
	vb->InsertStride<float, verticesSize>(3);
	vb->InsertStride<float, verticesSize>(3);
	vb->BindData();

	SetDrawAttributes(true, indices.size(), GL_QUADS);
	this->visible = visible;
}

Model::Plane::Plane(int length, int width, bool visible)
{
	float data[] = PLANE_DATA(length, width, height);

	vb = new VertexBuffer(data, sizeof(data));
	vb->InsertStride<float>(3);
	vb->InsertStride<float>(3);
	vb->InsertStride<float>(2);
	vb->BindData();
	SetDrawAttributes(false, PLANE_VERTICES_COUNT, GL_TRIANGLES);
	this->visible = visible;
}

void PrintQeued(std::vector<glm::vec3>& data, unsigned int numOfAttrib)
{
	const size_t length = data.size() / numOfAttrib;
	for (size_t i = 0; i < length; i++)
	{
		std::cout << i << ") ";
		for (size_t j = 0; j < numOfAttrib; j++)
			std::cout << " (x: " << data.at(i + length * j).x << ", y:" << data.at(i + length * j).y << ", z:" << data.at(i + length * j).z << ")" << "	|||	  ";
		std::cout << std::endl;
	}
}

void PrintInterleaved(std::vector<glm::vec3>& data, unsigned int numOfAttrib)
{
	for (size_t i = 0; i < data.size(); i += numOfAttrib)
	{
		std::cout << i << ") ";
		for (size_t j = 0; j < numOfAttrib; j++)
			std::cout << " (x: " << data.at(i + j).x << ", y:" << data.at(i + j).y << ", z:" << data.at(i + j).z << ")" << "	|||	  ";
		std::cout << std::endl;
	}
}

Model::Cone::Cone(float radius, float height, unsigned int sides, bool visible)
{
	std::vector<glm::vec3> vertices;
	std::vector<unsigned int> indices;

	const float inc = 360.0f / sides;
	for (float i = 0; i <= 360; i += inc)
	{
		const glm::vec3 vec1(glm::cos(glm::radians(i)), 0.0f, glm::sin(glm::radians(i)));
		const glm::vec3 vec2(0.0f, height, 0.0f);
		const glm::vec3 futureVec(glm::cos(glm::radians(i + inc)), 0.0f, glm::sin(glm::radians(i + inc)));

		glm::vec3 normal = glm::normalize(glm::cross(vec2 - vec1, futureVec - vec1));

		vertices.push_back(vec1);
		vertices.push_back(normal);
		vertices.push_back(vec2);
		vertices.push_back(normal);
	}

	size_t counter = 0;
	for (size_t i = 0; i < vertices.size() / 4-1; i++)
	{
		indices.emplace_back(counter++);
		indices.emplace_back(counter++);
		indices.emplace_back(counter);
	}
	PrintInterleaved(vertices, 2);

	vb = new VertexBuffer(&vertices.at(0), vertices.size() * 3 * sizeof(float), &indices.at(0), indices.size() * sizeof(unsigned int));

	vb->InsertStride<float>(3);
	vb->InsertStride<float>(3);

	vb->BindData();

	SetDrawAttributes(true, indices.size(), GL_TRIANGLES);
	this->visible = visible;
}
