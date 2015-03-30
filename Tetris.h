#ifndef _TETRIS_H         
#define _TETRIS_H         
#define WIN32_LEAN_AND_MEAN

#include <memory>
#include <random>

#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "gui.h"
#include "block.h"
#include "generic_cube.h"
#include "cubeo.h"
#include "cubei.h"
#include "cubej.h"
#include "cubel.h"
#include "cubes.h"
#include "cubet.h"
#include "cubez.h"

namespace tetrisNS
{
	// engine states and behaviour modifier
	const float MAP_START_X = 780.0f;
	const float MAP_START_Y = 150.0f;
	const float START_X = 780.0f;			//far left
	const float START_Y = 150.0f;
	const float TIME_STEP = 0.5f;					// seconds

	const int MAP_WIDTH = 10;
	const int MAP_HEIGTH = 20;
	const int MAP_TILE_HEIGHT = 36;
	const int MAP_TILE_WIDTH = 36;
	const int LINE_POINTS = 100;
	const int STARTING_GOAL = 5;
}

class Tetris : public Game
{
public:
	Tetris();
	virtual ~Tetris();

	void initialize(HWND hwnd);
	void update();    
	void ai();          
	void collisions();  
	void render();     
	void releaseAll();
	void resetAll();

private:
	enum GamePhases{
		INSERT,
		MOVE,
		DELETION,
		LOSE
	} phase;

	// initialization
	void init_textures();
	void init_images();
	void init_entities();
	void createPiece();
	void create_O_Piece(int n);
	int get_rdm_number(int d1, int d2);
	void restartNewGame();

	//update logic
	void setPiece();
	void getDirection();
	bool checkMap(float frameTime, int dx, int dy);
	bool isBlocked();
	void tick(float frameTime);
	void check_ifLose();
	int checkDeletion(int& l);
	void deleteRow(int row);
	void checkLevel(int rowDel);
	std::vector<std::vector<std::shared_ptr<Block>>> markMap(std::vector<std::vector<std::shared_ptr<Block>>>& m);
	std::vector<std::vector<std::shared_ptr<Block>>> moveAllblocksDown(std::vector<std::vector<std::shared_ptr<Block>>>& m, int rows, int l);
	inline void resetTime(){ t_step = tetrisNS::TIME_STEP; }

	// resources
	TextureManager chunck_T, background_t, gui_t, back2_t, nextb_t;
	Image background, back2, nextb;
	std::vector<std::vector<std::shared_ptr<Block>>> map;
	std::vector<std::shared_ptr<Block>> vecBlocks;
	std::vector<TextureManager *> textures; 
	CubeO cubeO;
	CubeI cubeI;
	CubeJ cubeJ;
	CubeL cubeL;
	CubeS cubeS;
	CubeT cubeT;
	CubeZ cubeZ;
	GenericCube* cube_ptr;
	GUI gui;

	// built-in types
	float t_step;
	int dx, dy, level, points, startingGoal, goal, nextblock_buffer;
	bool down_points;
};

#endif
