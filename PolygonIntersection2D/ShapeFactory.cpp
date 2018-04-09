#include "ShapeFactory.h"

#include "ConvexShape.h"

#include <GLFW\glfw3.h>
#include <glm\glm.hpp>

using namespace glm;

std::unique_ptr<ShapeFactory> ShapeFactory::s_instance = nullptr;

ShapeFactory::ShapeFactory()
	: m_curShapeIdx{ 0 }
{
}

ShapeFactory::~ShapeFactory()
{
}

ShapeFactory& ShapeFactory::instance()
{
	if (!s_instance)
		s_instance = std::unique_ptr<ShapeFactory>(new ShapeFactory());
	return *s_instance;
}

void ShapeFactory::onClick(int button, int action, double mousex, double mousey)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		vec2 mousePt = { mousex, mousey };

		// Allocate new memory for current shape if necessary
		if (m_curShapeIdx >= m_shapeList.size()) {
			m_shapeList.resize(m_curShapeIdx + 1);
		}

		m_shapeList[m_curShapeIdx].tryAddVertex(mousePt);
	}
}

void ShapeFactory::onKey(int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
		++m_curShapeIdx;

		// After two shapes the spacebar changes to a reset button
		if (m_curShapeIdx == 2) {
			m_curShapeIdx = 0;
			m_shapeList.clear();
		}
	}
}

const std::vector<ConvexShape>& ShapeFactory::getShapeList() const
{
	return m_shapeList;
}