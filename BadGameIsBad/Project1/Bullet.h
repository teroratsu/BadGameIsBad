#pragma once
#include "GameObject.h"

/*
===============================================================================
Bullet is inherited from the GameObject base class
bullet logic is implemented here
===============================================================================
*/

class Bullet : public GameObject
{
public:
	Bullet();
	~Bullet();
	void update(float) override;
	void pop(Direction, float x, float y);
private:
	Direction m_direction;
};

