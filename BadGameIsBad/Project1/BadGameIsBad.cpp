#include "BadGameIsBad.h"
#include <iostream>

namespace VAR {
	namespace SND {
		Sound*	MAIN_THEME[CST::SND::MAIN_THEME_t];
		Sound*	MOB_DEATH[CST::SND::MOB_DEATH_t];
		Sound*	MOB_HIT[CST::SND::MOB_HIT_t];
		Sound*	WAVE_START[CST::SND::WAVE_START_t];
		Sound*	WAVE_LOST[CST::SND::WAVE_LOST_t]; // defeat
		Sound*	WAVE_WIN[CST::SND::WAVE_WIN_t]; // lvl_up
		Sound*	PLAYER_HIT[CST::SND::PLAYER_HIT_t];
	}
}

//! ctor
/*
* init the game window and it's components
* init the game entities
* init the sound used in game
*/
BadGameIsBad::BadGameIsBad() : m_isRunning(false), m_wlvl(0)
{
	/* game window */
	m_hOutput = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);
	
	m_dwBufferSize = { CST::SCREEN_WIDTH, CST::SCREEN_HEIGHT };
	m_dwBufferCoord = { 0, 0 };
	m_rcRegion = { 0, 0, CST::SCREEN_WIDTH - 1, CST::SCREEN_HEIGHT - 1 };

	SetConsoleWindowInfo(m_hOutput, true, p_rcRegion);

	/* game entities */

	m_player = new Player();
	for(size_t i=0; i<CST::MOBS_COUNT; ++i)
		m_wave.push_back(new Mob());
	for (size_t i = 0; i<CST::BLTS_COUNT; ++i)
		m_bullet.push_back(new Bullet());

	/* Sound initialization */
	m_sndPlayer = new SoundPlayer();

	m_regSounds.insert(pair_SSND("A7_100", new Sound(CST::HRM::A, 7, 100)));
	m_regSounds.insert(pair_SSND("As7_150", new Sound(CST::HRM::As, 7, 150)));
	m_regSounds.insert(pair_SSND("C5_250", new Sound(CST::HRM::C, 5, 250)));
	m_regSounds.insert(pair_SSND("C5_150", new Sound(CST::HRM::C, 5, 150)));
	m_regSounds.insert(pair_SSND("G5_150", new Sound(CST::HRM::G, 5, 150)));
	m_regSounds.insert(pair_SSND("G5_250", new Sound(CST::HRM::G, 5, 250)));
	m_regSounds.insert(pair_SSND("B9_500", new Sound(CST::HRM::B, 9, 500)));
	m_regSounds.insert(pair_SSND("B7_500", new Sound(CST::HRM::B, 7, 500)));
	m_regSounds.insert(pair_SSND("D3_800", new Sound(CST::HRM::D, 3, 800)));
	m_regSounds.insert(pair_SSND("D5_500", new Sound(CST::HRM::D, 5, 500)));
	m_regSounds.insert(pair_SSND("D7_200", new Sound(CST::HRM::D, 7, 200)));
	m_regSounds.insert(pair_SSND("D9_200", new Sound(CST::HRM::D, 9, 200)));
	m_regSounds.insert(pair_SSND("D9_1000", new Sound(CST::HRM::D, 9, 1000)));

	VAR::SND::MAIN_THEME[0] = m_regSounds["B9_500"];
	VAR::SND::MAIN_THEME[1] = m_regSounds["B7_500"];
	/* ... */

	VAR::SND::MOB_DEATH[0] = m_regSounds["A7_100"];
	VAR::SND::MOB_DEATH[1] = m_regSounds["As7_150"];
	VAR::SND::MOB_DEATH[2] = m_regSounds["C5_250"];

	VAR::SND::MOB_HIT[0] = m_regSounds["C5_150"];
	VAR::SND::MOB_HIT[1] = m_regSounds["G5_250"];

	VAR::SND::WAVE_START[0] = m_regSounds["D7_200"];
	VAR::SND::WAVE_START[1] = m_regSounds["C5_150"];
	VAR::SND::WAVE_START[2] = m_regSounds["D9_200"];

	VAR::SND::WAVE_LOST[0] = m_regSounds["D7_200"];
	VAR::SND::WAVE_LOST[1] = m_regSounds["C5_150"];
	VAR::SND::WAVE_LOST[2] = m_regSounds["D5_500"];
	VAR::SND::WAVE_LOST[3] = m_regSounds["D5_500"];
	VAR::SND::WAVE_LOST[4] = m_regSounds["D3_800"];

	VAR::SND::WAVE_WIN[0] = m_regSounds["D7_200"];
	VAR::SND::WAVE_WIN[1] = m_regSounds["C5_150"];
	VAR::SND::WAVE_WIN[2] = m_regSounds["D7_200"];
	VAR::SND::WAVE_WIN[3] = m_regSounds["D7_200"];
	VAR::SND::WAVE_WIN[4] = m_regSounds["D9_1000"];

	VAR::SND::PLAYER_HIT[0] = m_regSounds["G5_150"];
	VAR::SND::PLAYER_HIT[1] = m_regSounds["C5_250"];
}

//! dtor
/*
* destroy game entities and sound's harmonics
*/
BadGameIsBad::~BadGameIsBad()
{
	delete m_player;
	for (auto& m : m_wave)
	{
		delete m;
	}
	for (auto& b : m_bullet)
	{
		delete b;
	}
	delete m_sndPlayer;
	for (auto& snd : m_regSounds)
	{
		delete snd.second;
	}
}

//! play
/*
* play the game
*/
void BadGameIsBad::play(void)
{
	m_timer.start();
	m_sec = m_timer.getElapsedSeconds();
	nextWave();
	m_isRunning = true;
	while (m_isRunning) {
		float timer = m_timer.getElapsedSeconds();
		handleInputs();
		update(timer - m_sec);
		m_sec = timer;
		draw();
	}
}

//! handleInputs
/*
* refresh input status
*/
void BadGameIsBad::handleInputs(void)
{
	m_leftIsPressed = (GetKeyState(INPUT_LEFT) & 0x8000) ? true : false;
	m_topIsPressed = (GetKeyState(INPUT_TOP) & 0x8000) ? true : false;
	m_rightIsPressed = (GetKeyState(INPUT_RIGHT) & 0x8000) ? true : false;
	m_downIsPressed = (GetKeyState(INPUT_DOWN) & 0x8000) ? true : false;
}

//! draw
/*
* draw gameObjects on screen
*/
void BadGameIsBad::draw(void)
{
	ReadConsoleOutput(m_hOutput, (CHAR_INFO *)m_buffer, m_dwBufferSize,
		m_dwBufferCoord, &m_rcRegion);

	/* clear */
	for (size_t i = 0; i < CST::SCREEN_WIDTH; i++)
	{
		for (size_t j = 0; j < CST::SCREEN_HEIGHT; j++)
		{
			m_buffer[j][i].Char.AsciiChar = ' ';
			m_buffer[j][i].Attributes = 0x00;
		}
	}

	for (size_t i = 0; i < CST::SCREEN_WIDTH; i++)
	{
		for (size_t j = 0; j < CST::SCREEN_HEIGHT; j++)
		{
			m_buffer[j][i].Char.AsciiChar = '.';
			m_buffer[j][i].Attributes = 0x05;
		}
	}
	/* actual draw */
	size_t x, y;
	x = static_cast<size_t>( m_player->x());
	y = static_cast<size_t>( m_player->y());
	m_buffer[y][x].Char.AsciiChar = (m_player->getShotDirection() == Direction::TOP) ? '^' : 'v';
	m_buffer[y][x].Attributes = 0x0F;
	if (x - 1 >= 0) {
		m_buffer[y][x - 1].Char.AsciiChar = '<';
		m_buffer[y][x - 1].Attributes = 0x0F;
	}
	if (x + 1 <= CST::SCREEN_WIDTH - 1) {
		m_buffer[y][x + 1].Char.AsciiChar = '>';
		m_buffer[y][x + 1].Attributes = 0x0F;
	}
	for(auto& m : m_wave)
	{
		if (m->isAlive() && m->spawned()) {
			x = static_cast<size_t>(m->x());
			y = static_cast<size_t>(m->y());
			m_buffer[y][x].Char.AsciiChar = 'w';
			m_buffer[y][x].Attributes = 0x0B;
			if (x - 1 >= 0) {
				m_buffer[y][x - 1].Char.AsciiChar = '[';
				m_buffer[y][x - 1].Attributes = 0x0B;
			}
			if (x + 1 <= CST::SCREEN_WIDTH - 1) {
				m_buffer[y][x + 1].Char.AsciiChar = ']';
				m_buffer[y][x + 1].Attributes = 0x0B;
			}
		}
	}
	for (auto& b : m_bullet)
	{
		if (b->isAlive()) {
			x = static_cast<size_t>(b->x());
			y = static_cast<size_t>(b->y());
			m_buffer[y][x].Char.AsciiChar = 'o';
			m_buffer[y][x].Attributes = 0x0A;
		}
	}

	// prompt wave on screen
	m_buffer[1][CST::SCREEN_WIDTH - 8].Char.AsciiChar = 'W';
	m_buffer[1][CST::SCREEN_WIDTH - 7].Char.AsciiChar = 'A';
	m_buffer[1][CST::SCREEN_WIDTH - 6].Char.AsciiChar = 'V';
	m_buffer[1][CST::SCREEN_WIDTH - 5].Char.AsciiChar = 'E';
	m_buffer[1][CST::SCREEN_WIDTH - 8].Attributes = 0x0D;
	m_buffer[1][CST::SCREEN_WIDTH - 7].Attributes = 0x0D;
	m_buffer[1][CST::SCREEN_WIDTH - 6].Attributes = 0x0D;
	m_buffer[1][CST::SCREEN_WIDTH - 5].Attributes = 0x0D;
	if (m_wlvl < 10) {
		m_buffer[1][CST::SCREEN_WIDTH - 3].Char.AsciiChar = '0';
		m_buffer[1][CST::SCREEN_WIDTH - 2].Char.AsciiChar = static_cast<char>(m_wlvl + '0');
	}
	else
	{
		m_buffer[1][CST::SCREEN_WIDTH - 3].Char.AsciiChar = '1';
		m_buffer[1][CST::SCREEN_WIDTH - 2].Char.AsciiChar = static_cast<char>((m_wlvl - 10) + '0');
	}

	WriteConsoleOutput(m_hOutput, (CHAR_INFO *)m_buffer, m_dwBufferSize, m_dwBufferCoord, &m_rcRegion);
}

//! update
/*
* update the game logic & gameObjects
*/
void BadGameIsBad::update(float timeElapsed)
{
	//update player info
	if (m_leftIsPressed && !m_rightIsPressed)
	{
		m_player->setMoveDirection(Direction::LEFT);
	}
	else if(!m_leftIsPressed && m_rightIsPressed){
		m_player->setMoveDirection(Direction::RIGHT);
	}
	else {
		if(m_player->isMoving())
			m_player->disableMove();
	}
	if (m_topIsPressed && !m_downIsPressed)
	{
		m_player->setShotDirection(Direction::TOP);
		if (m_player->allowShooting()) shoot();
	}
	else if (!m_topIsPressed && m_downIsPressed)
	{
		m_player->setShotDirection(Direction::DOWN);
		if(m_player->allowShooting()) shoot();
	}
	//updates
	m_player->update(timeElapsed);
	const float y_t = m_player->y();
	for (auto& b : m_bullet)
	{
		b->update(timeElapsed);
		if (b->isAlive()) {
			const short y_b_t = static_cast<short>(b->y());
			const short x_b_t = static_cast<short>(b->x());
			for (auto& m : m_wave)
			{
				if (m->isAlive()) {
					if (static_cast<short>(m->y()) == y_b_t)
					{
						if (std::abs(static_cast<short>(m->x()) - x_b_t) < CST::HIT_RNG)
						{
							m->disactive();
							b->disactive();
							std::thread(&SoundPlayer::play, std::ref(m_sndPlayer), VAR::SND::MOB_HIT, CST::SND::MOB_HIT_t).detach();
						}
					}
				}
			}
		}
	}
	short alv_c = 0;
	for (auto& m : m_wave)
	{
		m->update(timeElapsed);
		if (m->isAlive())
		{
			++alv_c;
		}
		if (m->y() == y_t)
		{
			gameOver();
		}
	}
	/* pop mobs at regular interval*/
	const float interval = (CST::MOBS_SPWN_RATE - (CST::MOBS_SPWN_RATE_D*m_wlvl));
	if (m_last_pop_timer > interval / 1000 && m_pop_c < m_wave.size())
	{
		m_pop_toggle = !m_pop_toggle;
		Direction d = (m_pop_toggle) ? Direction::TOP: Direction::DOWN;
		m_wave[m_pop_c]->pop(d);
		++alv_c;
		++m_pop_c;
		m_last_pop_timer = .0f;
	}
	else {
		m_last_pop_timer += timeElapsed;
	}

	if (m_pop_c == m_wave.size() && alv_c == 0)
	{
		std::thread(&SoundPlayer::play, std::ref(m_sndPlayer), VAR::SND::WAVE_WIN, CST::SND::WAVE_WIN_t).join();
		nextWave();
	}
}

//! nextWave
/*
* wave up
*/
void BadGameIsBad::nextWave(void)
{
	std::thread(&SoundPlayer::play, std::ref(m_sndPlayer), VAR::SND::WAVE_START, CST::SND::WAVE_START_t).join();
	++m_wlvl;
	for (auto& m : m_wave)
	{
		m->init();
	}
	for (auto& m : m_bullet)
	{
		m->disactive();
	}
	m_last_pop_timer = .0f;
	m_pop_toggle	 = false;
	m_pop_c			 = 0;
	//TODOD : init entities - prepare buffer
}

//! shoot
/*
* shoot a bullet in the shooting direction
*/
void BadGameIsBad::shoot(void)
{
	for(auto & b : m_bullet)
	{
		if (!b->isAlive())
		{
			b->pop(m_player->getShotDirection(), m_player->x(), m_player->y());
			m_player->shot();
			break;
		}
	}
}

//! gameOver
/*
* finish the game
*/
void BadGameIsBad::gameOver(void)
{
	std::thread(&SoundPlayer::play, std::ref(m_sndPlayer), VAR::SND::PLAYER_HIT, CST::SND::PLAYER_HIT_t).join();
	std::thread(&SoundPlayer::play, std::ref(m_sndPlayer), VAR::SND::WAVE_LOST, CST::SND::WAVE_LOST_t).join();
	m_isRunning = false;

	std::cout << "You survived " << m_wlvl << " waves" << std::endl;
	std::cin.get();

}
