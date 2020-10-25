#include "Triangle.h"
#include "TextureManager.h"
#include "Util.h"

Triangle::Triangle() 
{
	TextureManager::Instance()->load("../Assets/textures/Triangle_F.png", "Triangle");

	getTransform()->position = glm::vec2(400.0f, 482.5f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;

	lineAStart = getTransform()->position;
	lineBStart = getTransform()->position;
	lineAEnd = glm::vec2(getTransform()->position.x, getTransform()->position.y - 200.0f);
	lineBEnd = glm::vec2(getTransform()->position.x + 300.0f, getTransform()->position.y);

}

Triangle::~Triangle()
= default;

void Triangle::draw()
{
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	//TextureManager::Instance()->draw("Triangle", x, y, 0, 255, true);
	drawTriangle();
}

void Triangle::update()
{
	drawTriangle();
}

void Triangle::clean()
{

}

void Triangle::setLineA(float endY)
{
	//lineAStart = getTransform()->position;
	lineAEnd = glm::vec2(getTransform()->position.x, getTransform()->position.y - endY);
}

void Triangle::setLineB(float endX)
{
	//lineBStart = getTransform()->position;
	lineBEnd = glm::vec2(getTransform()->position.x + endX, getTransform()->position.y);
}

void Triangle::drawTriangle()
{
	Util::DrawLine(getTransform()->position, lineAEnd, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	Util::DrawLine(getTransform()->position, lineBEnd, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	Util::DrawLine(lineAEnd, lineBEnd, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
}
