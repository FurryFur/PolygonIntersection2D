#include "Point.h"

#include "Triangle.h"

#include <glm\glm.hpp>
#include <glm\gtc\constants.hpp>
#include <nanovg.h>

#include <array>

Point::Point(const glm::vec2& position, float size)
	: pos{ position }
	, size{ size }
{
}

Point::~Point()
{
}

void Point::draw(NVGcontext* vg) const
{
	nvgFillColor(vg, nvgRGBA(255, 50, 0, 128));
	nvgStrokeColor(vg, nvgRGBA(255, 50, 0, 255));

	nvgBeginPath(vg);
	nvgMoveTo(vg, pos.x - size, pos.y - size);
	nvgLineTo(vg, pos.x - size, pos.y + size);
	nvgLineTo(vg, pos.x + size, pos.y + size);
	nvgLineTo(vg, pos.x + size, pos.y - size);
	nvgLineTo(vg, pos.x - size, pos.y - size);
	nvgFill(vg);
	nvgStroke(vg);
}

// Compute barycentric coordinates (u, v, w) for
// point p with respect to triangle (a, b, c)
void barycentric(const Point& point, const Triangle& tri, float &u, float &v, float &w)
{
	const glm::vec2& p = point.pos;
	const glm::vec2& a = tri.vertices[0];
	const glm::vec2& b = tri.vertices[1];
	const glm::vec2& c = tri.vertices[2];

	glm::vec2 v0 = b - a, v1 = c - a, v2 = p - a;
	float d00 = glm::dot(v0, v0);
	float d01 = glm::dot(v0, v1);
	float d11 = glm::dot(v1, v1);
	float d20 = glm::dot(v2, v0);
	float d21 = glm::dot(v2, v1);
	float denom = d00 * d11 - d01 * d01;
	v = (d11 * d20 - d01 * d21) / denom;
	w = (d00 * d21 - d01 * d20) / denom;
	u = 1.0f - v - w;
}

bool Point::inside(const Triangle& tri) const
{
	float u, v, w;
	barycentric(*this, tri, u, v, w);

	if (u >= 0 && v >= 0 && w >= 0 && glm::abs(u + v + w - 1) < 0.001)
		return true;
	else
		return false;
}
