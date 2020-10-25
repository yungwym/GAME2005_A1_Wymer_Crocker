#include "Crate.h"
#include "TextureManager.h"

Crate::Crate()
{
	TextureManager::Instance()->load("../Assets/textures/Crate.png", "Crate");

	getTransform()->position = glm::vec2(400.0f, 93.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;

}

Crate::~Crate()
= default;

void Crate::draw()
{
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	TextureManager::Instance()->draw("Crate", x, y, 0, 255, true);
}

void Crate::update()
{
}

void Crate::clean()
{
}

void Crate::move()
{
	float deltaTime = 1.0f / 60.0f;
	glm::vec2 gravity = glm::vec2(0, 9.8f);

	

}