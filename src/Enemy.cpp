#include "Enemy.h"
#include "TextureManager.h"

Enemy::Enemy() 
{
	TextureManager::Instance()->load("../Assets/textures/Stormtroopers.png", "Stormtroopers");

	getTransform()->position = glm::vec2(585.0f, 400.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(PLAYER);


}

Enemy::~Enemy()
= default;

void Enemy::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	TextureManager::Instance()->draw("Stormtroopers", x, y, 0, 255, true);

}

void Enemy::update()
{
}

void Enemy::clean()
{
}
