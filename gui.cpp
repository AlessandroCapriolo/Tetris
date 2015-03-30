#include "gui.h"
using namespace guiNS;

GUI::GUI() : Entity(), num_bullets{ 0 }, score{ 0 }, level{ 1 }, highscore{ 1000 }, goal{ 0 }
{
	if (MOCKUP == true)
		mockup_construct();
	else
		construct();
	spriteData.x = X;
	spriteData.y = Y;
}

void GUI::mockup_construct()
{
	spriteData.width = WIDTH_MOCKUP;           // size of GUI
	spriteData.height = HEIGHT_MOCKUP;
	spriteData.rect.bottom = HEIGHT_MOCKUP;    // rectangle to select parts of an image
	spriteData.rect.right = WIDTH_MOCKUP;
}

void GUI::construct()
{
	spriteData.width = WIDTH;           // size of GUI
	spriteData.height = HEIGHT;
	spriteData.rect.bottom = HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = WIDTH;
}

//=============================================================================
// Initialize GUI with texture
//=============================================================================
bool GUI::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM)
{
	if (MOCKUP == true)
		return textureInit_mockup(gamePtr, textureM);
	else{
		return textureInit(gamePtr, textureM);
	}
}

//=============================================================================
// process of texture initialization - mockup version
//=============================================================================
bool GUI::textureInit_mockup(Game *gamePtr, TextureManager *textureM)
{
	if (text_score.initialize(gamePtr->getGraphics(), 30, false, false, "Arial") == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX text_score"));

	if (text_lose.initialize(gamePtr->getGraphics(), 80, false, false, "Terminal") == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX text_lose"));

	return(Entity::initialize(gamePtr, WIDTH_MOCKUP, HEIGHT_MOCKUP, TEXTURE_COLS, textureM));
}

//=============================================================================
// process of texture initialization - normal version
//=============================================================================
bool GUI::textureInit(Game *gamePtr, TextureManager *textureM)
{

	return(Entity::initialize(gamePtr, WIDTH, HEIGHT, TEXTURE_COLS, textureM));
}

//=============================================================================
// update stats on screen
//=============================================================================
void GUI::update(float frameTime, int s, int lv, int g)
{
	score = s;
	level = lv;
	if (score > highscore)
		highscore = score;
	goal = g;
}

//=============================================================================
// draw stats on screen
//=============================================================================
void GUI::draw()
{
	//Image::draw();
	text_score.print("LEVEL", static_cast<int>(this->getX() + STR_LEVEL_X), static_cast<int>(this->getY() + STR_LEVEL_Y));
	text_score.print("" + std::to_string(level), static_cast<int>(this->getX() + INT_LEVEL_X), static_cast<int>(this->getY() + INT_LEVEL_Y));

	text_score.print("SCORE", static_cast<int>(this->getX() + STR_SCORE_INFO_X), static_cast<int>(this->getY() + STR_SCORE_INFO_Y));
	text_score.print("" + std::to_string(score), static_cast<int>(this->getX() + INT_SCORE_INFO_X), static_cast<int>(this->getY() + INT_SCORE_INFO_Y));

	text_score.print("NEXT BEST SCORE", static_cast<int>(this->getX() + STR_HISCORE_INFO_X), static_cast<int>(this->getY() + STR_HISCORE_INFO_Y));
	text_score.print("" + std::to_string(highscore), static_cast<int>(this->getX() + INT_HISCORE_INFO_X), static_cast<int>(this->getY() + INT_HISCORE_INFO_Y));

	text_score.print("GOAL", static_cast<int>(this->getX() + STR_GOAL_X), static_cast<int>(this->getY() + STR_GOAL_Y));
	text_score.print("" + std::to_string(goal), static_cast<int>(this->getX() + INT_GOAL_X), static_cast<int>(this->getY() + INT_GOAL_Y));

	text_score.print("NEXT", static_cast<int>(this->getX() + NEXT_X), static_cast<int>(this->getY() + NEXT_Y));
}

//=============================================================================
// draw final score on screen
//=============================================================================
void GUI::draw_loseScreen()
{
	text_lose.print("SCORE: " + std::to_string(score), static_cast<int>(LOSE_SCORE_INFO_X), static_cast<int>(LOSE_SCORE_INFO_Y));
	text_score.print("Press Enter to restart", static_cast<int>(LOSE_SCORE_INFO_X + 144), static_cast<int>(LOSE_SCORE_INFO_Y + 144));
}

//=============================================================================
// debug, write on screen blocks disactivated
//=============================================================================
void GUI::debug_blocksAvailable(int b)
{
	text_score.print("blocks availables: " + std::to_string(b), static_cast<int>(this->getX() + 500), static_cast<int>(this->getY() + INT_LEVEL_Y));
}
