#pragma once
#ifndef __TRIANGLE__
#define __TRIANGLE__

#include "Sprite.h"

class Triangle final : public Sprite
{
public:
	Triangle();
	~Triangle();

	//Life Cycle 
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	void setLineA(float endY);
	void setLineB(float endX);

private:

	glm::vec2 lineAStart;
	glm::vec2 lineAEnd;
	glm::vec2 lineBStart;
	glm::vec2 lineBEnd;
	glm::vec2 lineCStart;
	glm::vec2 lineCEnd;

	void drawTriangle();

};

#endif // !__TRIANGLE__

