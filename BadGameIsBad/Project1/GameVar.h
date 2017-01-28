#ifndef GAMEVAR_H
#define GAMEVAR_H
#pragma once

/*
===============================================================================
Holds every constant that may be needed to make the game harder/faster/funnier
===============================================================================
*/

namespace CST{
	/* game window */
	const short SCREEN_WIDTH	{ 200 };
	const short SCREEN_HEIGHT	{ 60 };

	/* game param */
	const short MVT_SPEED		{ 100 };
	const short BLTS_SPWN_RATE	{ 200 }; //ms
	const short BLTS_SPEED		{ 70 }; 
	const short MOBS_SPEED		{ 150 };
	const short MOBS_COUNT		{ 40 };
	const short BLTS_COUNT		{ 50 };
	const float MOBS_SPWN_RATE	{ 500 }; //ms
	const float MOBS_SPWN_RATE_D{ 100 }; //ms
	const short HIT_RNG			{ 3 };

	/* sound param (harmonics) */
	namespace HRM{
		const float C	{ 16.35f };
		const float Cs	{ 17.32f };
		const float D	{ 18.35f };
		const float Ds	{ 19.45f };
		const float E	{ 20.60f };
		const float F	{ 21.83f };
		const float Fs	{ 23.12f };
		const float G	{ 24.50f };
		const float Gs	{ 25.96f };
		const float A	{ 27.50f };
		const float As	{ 29.14f };
		const float B	{ 30.87f };
	}
	namespace SND{
		const size_t	MAIN_THEME_t	{ 20 };
		const size_t	MOB_DEATH_t		{ 3 };
		const size_t	MOB_HIT_t		{ 2 };
		const size_t	WAVE_START_t	{ 3 };
		const size_t	WAVE_LOST_t		{ 5 };
		const size_t	WAVE_WIN_t		{ 5 };
		const size_t	PLAYER_HIT_t	{ 2 };
	}
}


#endif