#include "Target.h"
#include "TextureManager.h"


Target::Target()
{
	TextureManager::Instance()->load("../Assets/textures/Bomb.png","bomb");

	const auto size = TextureManager::Instance()->getTextureSize("bomb");
	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(100.0f, 400.0f);
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->isColliding = false;

	setType(TARGET);
}

Target::~Target()
= default;

void Target::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the target
	TextureManager::Instance()->draw("bomb", x, y, 0, 255, true);
}

void Target::update()
{
	m_move();
	m_checkBounds();
}

void Target::clean()
{
}

void Target::m_move()
{
	float deltaTime = 1.0f / 60.0f;
	glm::vec2 gravity = glm::vec2(0, 9.8f);

	if (isGravityEnabled)
	{
			getRigidBody()->velocity += (getRigidBody()->acceleration + gravity) * deltaTime;
	}
	else
	{
		getRigidBody()->velocity += getRigidBody()->acceleration * deltaTime;
	}
	getTransform()->position += getRigidBody()->velocity * deltaTime;
}

void Target::throwBall()
{
	getTransform()->position = throwPosition;

	getRigidBody()->velocity.x = cos(angle*M_PI/180) * horizontalVelocity * time;
	getRigidBody()->velocity.y = -(sin(angle*M_PI/180) * horizontalVelocity*time-4.8*time*time);

	std::cout << "Velocity X" << getRigidBody()->velocity.x << std::endl;
	std::cout << "Velocity Y " << getRigidBody()->velocity.y << std::endl;
}

void Target::m_checkBounds()
{
}

void Target::m_reset()
{
}
