#pragma once
#ifndef __CRATE__
#define __CRATE__

#include "Sprite.h"
#include "Triangle.h"

class Crate final : public Sprite
{
public:
	Crate();
	~Crate();

	//Life Cycle 
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	glm::vec2 getCollisionLineStart();
	glm::vec2 getCollisionLineEnd();

	void setTheta(float opp, float adj);
	float getTheta();

	void setMass(int mass);
	float getMass();

	void setFriction(int friction);
	float getFriction();

	bool isGravityEnabled = false;

	void dropCrate(float triH, float triW);

private:

	float m_theta;
	int m_mass;
	int m_friction;

	void m_move();

	glm::vec2 collisionLineStart;
	glm::vec2 collisionLineEnd;

};

#endif // !__CRATE__