#include "ShapeFactory.h"

#include "Point.h"
#include "Triangle.h"

#include <GLFW\glfw3.h>
#include <glm\glm.hpp>

using namespace glm;

std::unique_ptr<ShapeFactory> ShapeFactory::s_instance = nullptr;

ShapeFactory::ShapeFactory()
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

		if (m_vertices.size() == 4) {
			m_shapeList.clear();
			m_vertices.clear();
		}

		m_vertices.push_back(mousePt);
		if (m_vertices.size() == 3) {
			m_shapeList.emplace_back(new Triangle(m_vertices[0], m_vertices[1], m_vertices[2]));
		}

		if (m_vertices.size() == 4) {
			m_shapeList.emplace_back(new Point(m_vertices[3]));
		}
	}
		
}

const std::vector<std::unique_ptr<Shape>>& ShapeFactory::getShapeList() const
{
	return m_shapeList;
}

const Triangle* ShapeFactory::getTriangle() const
{
	if (m_shapeList.size() >= 1)
		return static_cast<Triangle*>(m_shapeList[0].get());
	else
		return nullptr;
}

const Point* ShapeFactory::getPoint() const
{
	if (m_shapeList.size() == 2)
		return static_cast<Point*>(m_shapeList[1].get());
	else
		return nullptr;
}
