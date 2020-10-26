#include "Crate.h"
#include "TextureManager.h"
#include "Util.h"
#include "CollisionManager.h"

Crate::Crate()
{
	TextureManager::Instance()->load("../Assets/textures/Crate.png", "Crate");

	getTransform()->position = glm::vec2(205.0f, 137.5f);
	//getTransform()->rotation = glm::vec2(37.0f, 0.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setHeight(91.0f);
	setWidth(91.0f);

	m_mass = 13;
	m_friction = 42;
	m_theta = 0;
}

Crate::~Crate()
= default;

void Crate::draw()
{
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	TextureManager::Instance()->draw("Crate", x, y, m_theta, 255, true);

	Util::DrawLine(collisionLineStart, collisionLineEnd);
}

void Crate::update()
{
	m_move();
}

void Crate::clean()
{
}

void Crate::m_move()
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

void Crate::dropCrate(float triH, float triW)
{
	std::cout << "Drop Crate" << std::endl;

	float fCO = (m_friction / 100.0f);
	float deltaTime = 1.0f / 60.0f;
	glm::vec2 gravity = glm::vec2(0, 9.8f);

	//Net Force = mgSin(0) 
	//Nornal Force: N = mg		
	//Friction: f = ukN		
	//Acceleration: a = f/m

	float netForce = (m_mass * gravity.y * sin(m_theta*M_PI/180));
	float normalForce = (m_mass * gravity.y);
	float frictionForce = (fCO * normalForce);
	float acceleration = (frictionForce / m_mass);
	float velocity = sqrt(2 * (9.8) * triH);

	getRigidBody()->velocity.x = cos(m_theta * M_PI / 180) * velocity;
	getRigidBody()->velocity.y = sin(m_theta * M_PI / 180) * velocity;

	getRigidBody()->velocity += (getRigidBody()->acceleration + (acceleration * gravity) * deltaTime);
	getTransform()->position += getRigidBody()->velocity * deltaTime;


	std::cout << std::endl << std::endl;
	std::cout << "********** ************** **********" << std::endl;
	std::cout << "********** Key Statistics **********" << std::endl;
	std::cout << "********** ************** **********" << std::endl << std::endl << std::endl;
	std::cout << "Net Force : " << netForce << " N" << std::endl;
	std::cout << "Normal Force : " << normalForce << " N"<< std::endl;
	std::cout << "Friction Force : " << frictionForce << " N" << std::endl;
	std::cout << "Velocity : " << velocity << " m/s" << std::endl;
	std::cout << "Acceleration : " << acceleration << " m/s^2" << std::endl;
	std::cout << "Coefficient of Friction : " << fCO << std::endl << std::endl << std::endl;
	std::cout << "********** ************** **********" << std::endl << std::endl;
}

glm::vec2 Crate::getCollisionLineStart()
{
	return collisionLineStart;
}

glm::vec2 Crate::getCollisionLineEnd()
{
	return collisionLineEnd;
}

void Crate::setTheta(float opp, float adj)
{
	float hyp = sqrt(pow(opp, 2) + pow(adj, 2));
	m_theta = 180 / M_PI * cos((adj * adj + hyp * hyp - opp * opp) / (2*adj*hyp));

	std::cout << "Theta : " << m_theta << std::endl;

}

float Crate::getTheta()
{
	return m_theta;
}

void Crate::setMass(int mass)
{
	m_mass = mass;
}

float Crate::getMass()
{
	return m_mass;
}

void Crate::setFriction(int friction)
{
	m_friction = friction;
}

float Crate::getFriction()
{
	return m_friction;
}

