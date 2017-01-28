#include "Mob.h"

//! ctor
/*
* init directions & status
*/
Mob::Mob()
{
	m_spawned	= false;
	m_spawn		= Direction::NONE;
	m_direction = Direction::NONE;
	m_alive		= true;
}

//! dtor
Mob::~Mob()
{
}

//! update
/*
* update Mob position and direction
*/
void Mob::update(float elapsedTime)
{
	if (m_alive && m_spawned)
	{
		switch (m_direction)
		{
		case Direction::LEFT: {
			m_x -= static_cast<float>(CST::MOBS_SPEED*elapsedTime);
			if (static_cast<int>(m_x) <= 1 )
			{
				m_x = 1;
				switch (m_spawn)
				{
				case Direction::TOP:
				{
					++m_y;
					m_direction = Direction::RIGHT;
				}; break;
				case Direction::DOWN:
				{
					--m_y;
					m_direction = Direction::RIGHT;
				}; break;
				}
			}
		}break;
		case Direction::RIGHT: {
			m_x += static_cast<float>(CST::MOBS_SPEED*elapsedTime);
			if (static_cast<int>(m_x) >= CST::SCREEN_WIDTH - 2)
			{
				m_x = CST::SCREEN_WIDTH - 2;
				switch (m_spawn)
				{
				case Direction::TOP:
				{
					++m_y;
					m_direction = Direction::LEFT;
				}; break;
				case Direction::DOWN:
				{
					--m_y;
					m_direction = Direction::LEFT;
				}; break;
				}
			}
		}break;
		}
	}
}

//! pop
/*
* spawn a mob in a given direction
*/
void Mob::pop(Direction dir)
{
	m_spawned = true;
	m_spawn = dir;
	switch (dir)
	{
	case Direction::TOP :
	{
		m_direction = Direction::RIGHT;
		m_x = .0f;
		m_y = .0f;
	}; break;
	case Direction::DOWN :
	{
		m_direction = Direction::LEFT;
		m_x = static_cast<float>( CST::SCREEN_WIDTH-1);
		m_y = static_cast<float>( CST::SCREEN_HEIGHT-1);
	}; break;
	}
}

//! spawned
/*
* return true if spawned
*/
bool Mob::spawned(void) const
{
	return m_spawned;
}

//! init
/*
* init the mob properties for another wave
*/
void Mob::init(void)
{
	m_spawned = false;
	m_alive = true;
	m_direction = Direction::NONE;
	m_spawn = Direction::NONE;
}
