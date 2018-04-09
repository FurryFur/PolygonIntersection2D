#include "Triangle.h"

#include <nanovg.h>

Triangle::Triangle(const glm::vec2& point1, const glm::vec2& point2, const glm::vec2& point3)
	: vertices{ point1, point2, point3 }
{
}

Triangle::~Triangle()
{
}

void Triangle::draw(NVGcontext* vg) const
{
	nvgFillColor(vg, nvgRGBA(255, 192, 0, 128));
	nvgStrokeColor(vg, nvgRGBA(255, 192, 0, 255));

	nvgBeginPath(vg);
	nvgMoveTo(vg, vertices[0].x, vertices[0].y);
	nvgLineTo(vg, vertices[1].x, vertices[1].y);
	nvgLineTo(vg, vertices[2].x, vertices[2].y);
	nvgLineTo(vg, vertices[0].x, vertices[0].y);
	nvgFill(vg);
	nvgStroke(vg);
}
