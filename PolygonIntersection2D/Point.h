#pragma once

#include "Shape.h"

#include <glm\vec2.hpp>

class Triangle;

class Point : public Shape
{
public:
	Point(const glm::vec2& position, float size = 5);
	~Point();

	// Inherited via Shape
	virtual void draw(NVGcontext*) const override;

	bool inside(const Triangle&) const;

	glm::vec2 pos;
	float size;
};

