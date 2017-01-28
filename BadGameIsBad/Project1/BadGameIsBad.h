#pragma once

#include <Windows.h>
#include <map>
#include <vector>
#include <string>
#include <thread>

#include "SoundPlayer.h"
#include "NYTimer.h"
#include "GameVar.h"
#include "Player.h"
#include "Mob.h"
#include "Bullet.h"

using pair_SSND = std::pair < std::string, Sound* >;
class BadGameIsBad
{
public:
	BadGameIsBad();
	~BadGameIsBad();
	void play(void);


private:
	void handleInputs(void);
	void draw( void );
	void update(float);
	void nextWave(void);
	void shoot( void );
	void gameOver(void);
	

	/* Game engine */
	bool	m_isRunning;
	short	m_wlvl; /* wave level */
	NYTimer m_timer;
	float	m_sec;

	/* Game Window */
	HANDLE				m_hOutput;
	COORD				m_dwBufferSize;
	COORD				m_dwBufferCoord;
	SMALL_RECT			m_rcRegion;
	const SMALL_RECT*	p_rcRegion = &m_rcRegion;
	CHAR_INFO			m_buffer[CST::SCREEN_HEIGHT][CST::SCREEN_WIDTH];

	/* SoundHandler */
	SoundPlayer*					m_sndPlayer;
	std::map<std::string, Sound*>	m_regSounds; /* registered sounds*/

	/* inputs */
	const int	INPUT_LEFT = 0x25;
	const int	INPUT_TOP = 0x26;
	const int	INPUT_RIGHT = 0x27;
	const int	INPUT_DOWN = 0x28;
	bool		m_leftIsPressed;
	bool		m_topIsPressed;
	bool		m_rightIsPressed;
	bool		m_downIsPressed;

	/* Game logic */
	Player*				m_player;
	std::vector<Mob*>	m_wave;
	std::vector<Bullet*> m_bullet;

	/* Wave handlers */
	float	m_last_pop_timer;
	size_t	m_pop_c;
	bool	m_pop_toggle;

};

