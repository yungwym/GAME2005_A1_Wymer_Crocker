#pragma once
#ifndef __CRATE__
#define __CRATE__

#include "Sprite.h"

class Crate final : public Sprite
{
public:
	Crate();
	~Crate();

	//Life Cycle 
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	void move();
};

#endif // !__CRATE__