#include "ConvexShape.h"

#include <glm\glm.hpp>
#include <nanovg.h>

ConvexShape::ConvexShape()
{
}


ConvexShape::~ConvexShape()
{
}

void ConvexShape::draw(NVGcontext* vg) const
{
	if (m_vertices.empty())
		return;

	nvgFillColor(vg, nvgRGBA(255, 192, 0, 128));
	nvgStrokeColor(vg, nvgRGBA(255, 192, 0, 255));

	nvgBeginPath(vg);
	nvgMoveTo(vg, m_vertices[0].x, m_vertices[0].y);
	for (size_t i = 0; i < m_vertices.size(); ++i) {
		const glm::vec2& vert = m_vertices[(i + 1) % m_vertices.size()];
		nvgLineTo(vg, vert.x, vert.y);
	}
	nvgFill(vg);
	nvgStroke(vg);
}

float crossSign(const glm::vec2& A, const glm::vec2& B, const glm::vec2& C) 
{
	return glm::sign((B.x - A.x) * (C.y - B.y) - (B.y - A.y) * (C.x - B.x));
}

bool ConvexShape::tryAddVertex(const glm::vec2& vert)
{
	m_vertices.push_back(vert);

	// Can always add the first 3 verts
	if (m_vertices.size() <= 3)
		return true;

	float targetSign = crossSign(m_vertices[0], m_vertices[1], m_vertices[2]);
	for (size_t i = 1; i < m_vertices.size(); ++i) {
		glm::vec2 A = m_vertices[i];
		glm::vec2 B = m_vertices[(i + 1) % m_vertices.size()];
		glm::vec2 C = m_vertices[(i + 2) % m_vertices.size()];
		if (crossSign(A, B, C) != targetSign) {
			m_vertices.pop_back();
			return false;
		}
	}
	
	return true;
}

bool ConvexShape::intersects(const ConvexShape& other) const
{
	// Get axes to project along
	auto normals = this->getNormals();
	auto theirNormals = other.getNormals();
	normals.insert(normals.end(), theirNormals.begin(), theirNormals.end());

	for (const glm::vec2& axis : normals) {
		// Get min/max projection for each shape
		float thisProjMin, thisProjMax;
		float otherProjMin, otherProjMax;
		getProjMinMax(*this, axis, thisProjMin, thisProjMax);
		getProjMinMax(other, axis, otherProjMin, otherProjMax);

		// If found separation on one axes then shapes do not intersect
		if (otherProjMin > thisProjMax || thisProjMin > otherProjMax)
			return false;
	}

	// Return true when no separation is found
	return true;
}

std::vector<glm::vec2> ConvexShape::getNormals() const
{
	std::vector<glm::vec2> result;

	for (size_t i = 0; i < m_vertices.size() - 1; ++i) {
		glm::vec2 edgeDir = glm::normalize(m_vertices[i + 1] - m_vertices[i]);

		result.emplace_back(edgeDir.y, -edgeDir.x);
	}

	return result;
}

void ConvexShape::getProjMinMax(const ConvexShape& shape, glm::vec2 axis, float& min, float& max) const
{
	const auto& vertices = shape.m_vertices;

	bool initializedMinMax = false;
	for (const auto& vert : vertices) {
		float proj = glm::dot(vert, axis);

		// Init min/max on first iteration
		if (!initializedMinMax) {
			min = proj;
			max = proj;
			initializedMinMax = true;
		}

		if (proj < min)
			min = proj;
		if (proj > max)
			max = proj;
	}
}
