#pragma once

#include <vector>
#include <glm\vec2.hpp>

#include <memory>

class ConvexShape;

class ShapeFactory
{
public:
	ShapeFactory(const ShapeFactory&) = delete;
	ShapeFactory(ShapeFactory&&) = delete;
	~ShapeFactory();

	static ShapeFactory& instance();

	void onClick(int button, int action, double mousex, double mousey);
	void onKey(int key, int scancode, int action, int mods);
	const std::vector<ConvexShape>& getShapeList() const;

private:
	ShapeFactory();

	static std::unique_ptr<ShapeFactory> s_instance;
	
	std::vector<ConvexShape> m_shapeList;
	size_t m_curShapeIdx;
	//std::vector<glm::vec2> m_vertices;
};

