#pragma once

#include "Shape.h"

#include <glm\vec2.hpp>

#include <array>

class Triangle : public Shape
{
public:
	Triangle(const glm::vec2& point1, const glm::vec2& point2, const glm::vec2& point3);
	~Triangle();

	// Inherited via Shape
	virtual void draw(NVGcontext*) const override;

	std::array<glm::vec2, 3> vertices;
};

