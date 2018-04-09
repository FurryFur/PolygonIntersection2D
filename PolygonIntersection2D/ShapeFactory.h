#pragma once

#include <vector>
#include <glm\vec2.hpp>

#include <memory>

class Point;
class Triangle;
class Shape;

class ShapeFactory
{
public:
	ShapeFactory(const ShapeFactory&) = delete;
	ShapeFactory(ShapeFactory&&) = delete;
	~ShapeFactory();

	static ShapeFactory& instance();

	void onClick(int button, int action, double mousex, double mousey);
	const std::vector<std::unique_ptr<Shape>>& getShapeList() const;
	const Triangle* getTriangle() const;
	const Point* getPoint() const;

private:
	ShapeFactory();

	static std::unique_ptr<ShapeFactory> s_instance;
	
	std::vector<std::unique_ptr<Shape>> m_shapeList;
	std::vector<glm::vec2> m_vertices;
};

