#ifndef _GUI_H
#define _GUI_H
#define WIN32_LEAN_AND_MEAN

#include <memory>

#include "entity.h"
#include "constants.h"
#include "textDX.h"

namespace guiNS
{
	// image info
	const int TEXTURE_COLS = 0;
	const int WIDTH = 196;
	const int HEIGHT = 80;
	const int WIDTH_MOCKUP = 196;							// 1280x720, virtual resoultion of 400x240, scale 3x3, NES sprite 32x32
	const int HEIGHT_MOCKUP = 80;							// 1920x1080, virtual resoultion of 400x240, scale 4.5x4.5, NES sprite 32x32
	const float X = 0.0f;
	const float Y = 0.0f;
	const float HI_SCORE_INFO_X = static_cast<float> (GAME_WIDTH) / 2 - 200.0f;
	const float HI_SCORE_INFO_Y = 12.0f;
	const float LOSE_SCORE_INFO_X = static_cast<float> (GAME_WIDTH) / 2 - 400.0f;
	const float LOSE_SCORE_INFO_Y = static_cast<float> (GAME_HEIGHT) / 2 - 144.0f;

	const float STR_LEVEL_X = 650.0f;
	const float STR_LEVEL_Y = 720.0f;
	const float INT_LEVEL_X = 630.0f;
	const float INT_LEVEL_Y = 780.0f;

	const float STR_GOAL_X = 650.0f;
	const float STR_GOAL_Y = 880.0f;
	const float INT_GOAL_X = 630.0f;
	const float INT_GOAL_Y = 938.0f;

	const float STR_SCORE_INFO_X = 1280.0f;
	const float STR_SCORE_INFO_Y = 880.0f;
	const float INT_SCORE_INFO_X = 1320.0f;
	const float INT_SCORE_INFO_Y = 938.0f;

	const float STR_HISCORE_INFO_X = 1280.0f;
	const float STR_HISCORE_INFO_Y = 720.0f;
	const float INT_HISCORE_INFO_X = 1320.0f;
	const float INT_HISCORE_INFO_Y = 780.0f;

	const float NEXT_X = 1280.0f;
	const float NEXT_Y = 130.0f;

	// GUI state and behaviour modifier
	const bool MOCKUP = true;
}

class GUI : public Entity
{
private:
	// initialization
	void mockup_construct();
	void construct();
	bool textureInit_mockup(Game *gamePtr, TextureManager *textureM);
	bool textureInit(Game *gamePtr, TextureManager *textureM);

	//resources
	TextDX text_score;
	TextDX text_lose;
	int num_bullets, score, level, highscore, goal;

public:
	GUI();
	bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);
	void update(float frameTime, int s, int lv, int goal);
	void draw();
	void draw_loseScreen();
	void debug_blocksAvailable(int b);
};

#endif
