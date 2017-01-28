#pragma once

#include "GameObject.h"

/*
===============================================================================
Mob is inherited from the GameObject base class
keep information about a mob and its status
===============================================================================
*/

class Mob : public GameObject
{
public:
	Mob();
	~Mob();
	void update(float) override;
	void pop(Direction);
	bool spawned(void) const;
	void init(void);

private:
	Direction	m_direction;
	Direction	m_spawn;
	bool		m_spawned;
};

