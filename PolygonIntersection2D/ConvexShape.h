#pragma once

#include "Shape.h"

#include <glm\vec2.hpp>

#include <vector>

class ConvexShape: public Shape
{
public:
	ConvexShape();
	~ConvexShape();

	// Inherited via Shape
	virtual void draw(NVGcontext*) const override;

	// Try adding a vertex.
	// Returns false if adding the vertex would make shape concave.
	bool tryAddVertex(const glm::vec2&);

	bool intersects(const ConvexShape& other) const;

private:
	std::vector<glm::vec2> getNormals() const;
	void getProjMinMax(const ConvexShape&, glm::vec2 axis, float& min, float& max) const;

	std::vector<glm::vec2> m_vertices;
};

