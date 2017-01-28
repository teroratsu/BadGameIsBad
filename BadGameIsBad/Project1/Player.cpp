#include "Player.h"

//! ctor
/*
* init player properties
*/
Player::Player() : m_last_shot_timer(.0f), m_moving(false)
{
	m_x = static_cast<float>(CST::SCREEN_WIDTH/2);
	m_y = static_cast<float>(CST::SCREEN_HEIGHT/2);
	m_move = Direction::LEFT;
	m_shot = Direction::TOP;
	m_alive = true;
}

//!dtor
Player::~Player()
{
}

//! update
/*
* update player position and shooting status through time
*/
void Player::update(float elapsedTime)
{
	if (m_moving)
	{
		switch (m_move)
		{
		case Direction::RIGHT:
		{
			float x_t = m_x;
			m_x += static_cast<float>(CST::MVT_SPEED*elapsedTime);
			m_x = (m_x < CST::SCREEN_WIDTH) ? m_x : x_t;
		}; break;
		case Direction::LEFT:
		{
			float x_t = m_x;
			m_x -= static_cast<float>(CST::MVT_SPEED*elapsedTime);
			m_x = (m_x > 0) ? m_x : x_t;
		}; break;
		}
	}
	/* shooting mechanic */
	if (m_last_shot_timer*1000 > CST::BLTS_SPWN_RATE)
	{
		m_allowShooting = true;
		m_last_shot_timer = .0f;
	}
	else {
		m_last_shot_timer += elapsedTime;
	}
}

//! allowshooting
/*
* true if is allowing shooting
*/
bool Player::allowShooting(void)
{
	if (m_allowShooting)
	{
		m_allowShooting = false;
		return true;
	}
	else
		return false;
}

//! isMoving
/*
* true if moving
*/
bool Player::isMoving(void) const
{
	return m_moving;
}

//! setMoveDirection
void Player::setMoveDirection(Direction dir)
{
	m_moving = true;
	if(dir == Direction::LEFT || dir == Direction::RIGHT)
		m_move = dir;
}

//! setShotDirection
void Player::setShotDirection(Direction dir)
{
	if (dir == Direction::TOP || dir == Direction::DOWN)
		m_shot = dir;
}

//! disableMove
/*
* disable player movement
*/
void Player::disableMove(void)
{
	m_moving = false;
}

//! getShotDirection
Direction Player::getShotDirection(void) const
{
	return m_shot;
}

//! shot
/*
* turn allowshooting to false
*/
void Player::shot(void)
{
	m_allowShooting = false;
}
