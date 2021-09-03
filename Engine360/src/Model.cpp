#include "Model.h"
#include <array>
#include "Data/ModelVertices.h"
#include "Renderer/Renderer.h"

void Model::Model::Render()
{
	vb->Bind();
	if (indexed)
		glDrawElements(drawTarget, count, GL_UNSIGNED_INT, nullptr);
	else
		glDrawArrays(drawTarget, 0, count);
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

Model::Cube::Cube(int length, int width, int height, bool visible)
{
	float data[] = CUBE_DATA(length, width, height);

	vb = new VertexBuffer(data, sizeof(data));
	vb->InsertStride<float>(3);
	vb->InsertStride<float>(3);
	vb->InsertStride<float>(2);

	SetDrawAttributes(false, CUBE_VERTICES_COUNT, GL_TRIANGLES);
	this->visible = visible;
}

Model::Cylinder::Cylinder(float radius, float height, int sides, bool visible)
{
	std::vector<glm::vec3> vertices;
	vertices.reserve((360 / sides) * 2);
	
	std::vector<unsigned int> indices;
	indices.reserve((360 / sides) * 4);

	size_t counter = 0;
	for (float i = 0; i <= 360; i += 360.0f / sides)
	{
		glm::vec3 vertTop(glm::cos(glm::radians(i)), height / 2.0f, glm::sin(glm::radians(i)));
		glm::vec3 vertBottom(glm::cos(glm::radians(i)), -height / 2.0f, glm::sin(glm::radians(i)));
		vertices.emplace_back(vertTop * radius);
		vertices.emplace_back(vertBottom * radius);
		if (i != 0)
		{
			indices.emplace_back(counter);
			indices.emplace_back(counter+1);
			indices.emplace_back(counter+3);
			indices.emplace_back(counter+2);
			counter += 2;
		}
	}
	indices.emplace_back(counter++);
	indices.emplace_back(counter++);
	indices.emplace_back(0);
	indices.emplace_back(1);

	vb = new VertexBuffer(&vertices.at(0), sizeof(float) * vertices.size() * 3, &indices.at(0), sizeof(unsigned int) * indices.size());
	vb->InsertStride<float>(3);

	SetDrawAttributes(true, indices.size(), GL_QUADS);

	this->visible = visible;
}
