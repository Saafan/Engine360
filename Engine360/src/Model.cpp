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


void Model::Model::SetPosition(glm::mat4 value)
{
	model = value;
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

Model::Cylinder::Cylinder(float radius, float height, int sides, bool visible)
{
	std::vector<glm::vec3> vertices;
	vertices.reserve((360 / sides) * 2);
	vertices.emplace_back(0.0f, height / 2.0f, 0.0f);
	vertices.emplace_back(0.0f, 1.0f, 0.0f);
	vertices.emplace_back(0.0f, -(height / 2.0f), 0.0f);
	vertices.emplace_back(0.0f, -(1.0f), 0.0f);

	std::vector<unsigned int> indices;
	indices.reserve((360 / sides) * 4);

	size_t counter = 2;
	for (float i = 0; i <= 360; i += 360.0f / sides)
	{
		glm::vec3 vertTop(glm::cos(glm::radians(i)), height / 2.0f, glm::sin(glm::radians(i)));
		glm::vec3 vertBottom(glm::cos(glm::radians(i)), -height / 2.0f, glm::sin(glm::radians(i)));
		vertices.emplace_back(vertTop * radius);
		vertices.emplace_back(vertTop - vertices.at(0));
		vertices.emplace_back(vertBottom * radius);
		vertices.emplace_back(vertBottom - vertices.at(1));
		if (i != 0)
		{
			//Cylinder Sides
			indices.emplace_back(counter);
			indices.emplace_back(counter + 1);
			indices.emplace_back(counter + 3);
			indices.emplace_back(counter + 2);

			if (i < 360)
			{

			//Cylinder Cap Top
			indices.emplace_back(counter);
			indices.emplace_back(counter + 2);
			indices.emplace_back(counter + 4);
			indices.emplace_back(0);

			//Cylinder Cap Bottom
			indices.emplace_back(counter + 1);
			indices.emplace_back(counter + 3);
			indices.emplace_back(counter + 5);
			indices.emplace_back(1);
			}


			counter += 2;
		}
	}
	indices.emplace_back(counter++);
	indices.emplace_back(counter++);
	indices.emplace_back(2);
	indices.emplace_back(3);

	vb = new VertexBuffer(&vertices.at(0), sizeof(float) * vertices.size() * 6, &indices.at(0), sizeof(unsigned int) * indices.size());
	vb->InsertStride<float>(3);
	vb->InsertStride<float>(3);
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
