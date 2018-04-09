#pragma once

struct NVGcontext;

class Shape
{
public:
	virtual ~Shape();
	
	virtual void draw(NVGcontext*) const = 0;

protected:
	Shape();
};

