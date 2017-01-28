#pragma once

#include "GameVar.h"

/*
===============================================================================
Basic component used as a base for more complex GameObject
===============================================================================
*/

enum class Direction
{
	LEFT,
	TOP,
	RIGHT,
	DOWN,
	NONE
};

class GameObject
{
public:
	GameObject();
	~GameObject();
	virtual float x(void) const;
	virtual float y(void) const;
	virtual void update(float) = 0;
	virtual bool isAlive(void) const;
	virtual void active(void);
	virtual void disactive(void);

protected:
	float	m_x;
	float	m_y;
	bool	m_alive;
};

