#pragma once

#include "GameObject.h"

/*
===============================================================================
Player is inherited from the GameObject base class
The main use of this class is to hold player information
===============================================================================
*/

class Player : public GameObject
{
public:
	Player();
	~Player();
	void update(float) override;
	bool allowShooting( void );
	bool isMoving(void) const;
	void setMoveDirection( Direction );
	void setShotDirection( Direction );
	void disableMove( void);
	Direction getShotDirection(void) const;
	void shot(void);
private:
	Direction	m_move;
	Direction	m_shot;
	float		m_last_shot_timer;
	bool		m_moving;
	bool		m_allowShooting;
};

