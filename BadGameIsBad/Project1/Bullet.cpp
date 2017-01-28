#include "Bullet.h"

//! Ctor
/*
* set direction to none
*/
Bullet::Bullet()
{
	m_direction = Direction::NONE;
}

//! dtor
Bullet::~Bullet()
{
}

//! update
/*
* update bullet position and status
*/
void Bullet::update(float elapsedTime)
{
	if (m_alive) {
		switch (m_direction)
		{
		case Direction::TOP:
		{
			m_y -= static_cast<float>(CST::BLTS_SPEED*elapsedTime);
		}; break;
		case Direction::DOWN:
		{
			m_y += static_cast<float>(CST::BLTS_SPEED*elapsedTime);
		}; break;
		}
		if (m_y < 0 || m_y >= CST::SCREEN_HEIGHT)
			m_alive = false;
	}
}

//! pop
/*
* spawn a bullet in a given position to a given direction
*/
void Bullet::pop(Direction dir, float x, float y)
{
	m_direction = dir;
	m_x = x;
	m_y = y;
	m_alive = true;
}
