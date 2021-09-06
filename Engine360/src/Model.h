#pragma once

#include "VertexBuffer.h"
#include "glm.hpp"

namespace Model
{

	class Model {

	public:
		void Render();
		bool visible = true;

		void SetPosition(glm::mat4 value);
		void SetPosition(float v1, float v2, float v3);

	protected:
		Model() ;
		~Model();
		void SetDrawAttributes(bool indexed, unsigned int count, unsigned int drawTarget);

		VertexBuffer* vb = nullptr;
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 oldModel = glm::mat4(1.0f);

		bool indexed = false;
		unsigned int count = 0;
		unsigned int drawTarget = 0;

	};

	struct Cube : public Model {
		Cube(float length, float width, float height, bool visible = true);
	};

	struct Cylinder : public Model {
		Cylinder(float radius, float height, int sides = 18, bool visible = true);
	};

	struct Cone : public Model {
		Cone(int radius, int height, bool visible = true);
	};

	struct Torus : public Model {
		Torus(int innerRadius, int outerRadius, bool visible = true);
	};

	struct Sphere : public Model {
		Sphere(int radius, bool visible = true);
	};

	struct Plane : public Model {
		Plane(int length, int width, bool visible = true);
	};

	class Ground : public Model {
		Ground(int width, int height, bool visible = true);
	};
};