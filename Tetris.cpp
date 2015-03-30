#include "Tetris.h"
using namespace tetrisNS;

//=============================================================================
// Constructor, initialize gamestatus
//=============================================================================
Tetris::Tetris() :
phase{ INSERT }, dx{ 0 }, dy{ 0 }, t_step{ TIME_STEP }, level{ 1 }, points{ 0 }, 
startingGoal{ STARTING_GOAL }, goal{ STARTING_GOAL }, down_points{ false }, nextblock_buffer{ -1 }
{
	map.resize(MAP_HEIGTH);
	for (int i = 0; i < MAP_HEIGTH; ++i)
		map[i].resize(MAP_WIDTH);

	for (int i = 0; i < MAP_HEIGTH; ++i)
		for (int j = 0; j < MAP_WIDTH; ++j)
			map[i][j] = nullptr;

	// pointer to polimorphic object (there are 6 different cubes in Tetris, 
	// all concrete specializations from abstract class "generic_cube")
	cube_ptr = nullptr;
}

//=============================================================================
// Destructor
//=============================================================================
Tetris::~Tetris()
{
	releaseAll();

}

//=============================================================================
// Initialize engine components (graphics system, sound system etc.)
// Throws GameError on error (no texture file found, sound system failed to initialize etc.)
//=============================================================================
void Tetris::initialize(HWND hwnd)
{
	// initialize graphics, input, sound, timer, etc.
    Game::initialize(hwnd); 
	
	// Loads the texture file(s) from disk.
	init_textures();

	// Initialize an Image with texture and tranformation data
	init_images();

	// Initialize entities with a texture
	init_entities();

	return;
}

//=============================================================================
// Update game items, checks if Grid have available a free slot for a coin
// if so, use a an-used coin in the specified col and row by Grid
//=============================================================================
void Tetris::update()
{	
	bool isMovingDown = false;
	int rowDeleted = 0;
	down_points = false;

	switch (phase)
	{
	case INSERT:
		resetTime();
		createPiece();
		setPiece();
		check_ifLose();
		break;
	case MOVE:
		gui.update(frameTime, points, level, goal);
		getDirection();
		tick(frameTime);
		if (t_step <= 0.0f){
			isMovingDown = checkMap(frameTime, dx, 1);				//check and move down
			if (isMovingDown)
				resetTime();
		}
		else{
			isMovingDown = checkMap(frameTime, dx, dy);			//check map and player choose
			if (isMovingDown){
				resetTime();
				if (down_points)
					points += 1;
			}
		}
		//pBlock->update(frameTime);
		cube_ptr->update(frameTime);
		if ((isBlocked() && t_step <= 0.0f) || (isBlocked() && dy == 1)){
			map = markMap(map);
			cube_ptr = nullptr;
			phase = DELETION;
		}
		break;
	case DELETION:
		int line;							// indicates the last line where deletion occurs (if line!= 0)
		rowDeleted = checkDeletion(line);
		//if (rowDeleted > 0){
			//map = moveAllblocksDown(map, rowDeleted, line);
			//points += rowDeleted * LINE_POINTS;
		//}
		points += rowDeleted * LINE_POINTS;
		checkLevel(rowDeleted);
		phase = INSERT;
		break;
	case LOSE:
		if (input->wasKeyPressed(VK_RETURN)){
			restartNewGame();
		}
		break;
	default:
		break;
	}
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void Tetris::ai()
{}

//=============================================================================
// Handle collisions
//=============================================================================
void Tetris::collisions()
{
	
}

//=============================================================================
// Render game items
//=============================================================================
void Tetris::render()
{
    graphics->spriteBegin();                // begin drawing sprites

	switch (level)
	{
	case 1:
		back2.draw();
		break;
	case 2:
	case 3:
	case 4:
		back2.draw(graphicsNS::BLUE);
		break;
	case 5:
	case 6:
		back2.draw(graphicsNS::GREEN);
		break;
	default:
		back2.draw(graphicsNS::RED);
		break;
	}
	background.draw();

	//pBlock->draw();
	for (std::shared_ptr<Block> b : vecBlocks)
		b->draw();

	if (cube_ptr != nullptr)
		cube_ptr->draw();

	gui.draw();

	if (phase == LOSE)
		gui.draw_loseScreen();

	int blockd = 0;
	for (std::shared_ptr<Block> b : vecBlocks){
		if (b->activate == false){
			++blockd;
		}
	}
	//gui.debug_blocksAvailable(blockd);

	nextb.draw();

    graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Tetris::releaseAll()
{
	for (TextureManager* t : textures)
		t->onLostDevice();

    Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void Tetris::resetAll()
{
	for (TextureManager* t : textures)
		t->onResetDevice();

    Game::resetAll();
    return;
}

//=============================================================================
// positioning chunck in game
//=============================================================================
void Tetris::setPiece()
{
	cube_ptr->setPieces();
}

//=============================================================================
// take next move from keyboard
//=============================================================================
void Tetris::getDirection()
{
	if (input->wasKeyPressed(VK_LEFT))
		dx = -1;
	else if (input->wasKeyPressed(VK_RIGHT))
		dx = 1;
	else
		dx = 0;

	if (input->wasKeyPressed(VK_DOWN)){
		dy = 1;
		down_points = true;
	}
	else
		dy = 0;

	if (input->wasKeyPressed(0x58))		// X key
		cube_ptr->rotate(map);
}

//=============================================================================
// check if next move is possible
// return true if chunck moved down
//=============================================================================
bool Tetris::checkMap(float frameTime, int dx, int dy)
{
	for (auto b : cube_ptr->vecPieces){
		int cnk_x = static_cast<int>((b->getX() - MAP_START_X) / MAP_TILE_WIDTH);
		int cnk_y = static_cast<int>((b->getY() - MAP_START_Y) / MAP_TILE_HEIGHT);

		if (dx != 0 || dy != 0){
			if (cnk_x + dx < 0 || cnk_x + dx > 9)
				dx = 0;
			if (cnk_y + dy < 0 || cnk_y + dy > 19)
				return false;

			if (map[cnk_y + dy][cnk_x + dx] != nullptr)
				return false;
		}
		else
			return false;
	}

	for (auto b : cube_ptr->vecPieces){
		switch (dx)
		{
		case -1:
			b->moveLeft(frameTime);
			break;
		case 1:
			b->moveRight(frameTime);
			break;
		default:
			break;
		}
		if (dy == 1)
			b->moveDown(frameTime);
	}

	if (dy == 1)
		return true;
	else
		return false;
}

//=============================================================================
// move chunck bottom every step time
//=============================================================================
void Tetris::tick(float frameTime)
{
	t_step -= frameTime;
	//if (t_step <= 0.0f){
		//checkMap(frameTime, 0, 1);
		//t_step = TIME_STEP;
	//}
}

//=============================================================================
// create piece
//=============================================================================
void Tetris::createPiece()
{
	/*
	for (std::shared_ptr<Block> b : vecBlocks){
		if (b->activate == false){
			b->activate = true;
			pBlock = b;
			break;
		}
	}
	*/
	if (nextblock_buffer == -1){							// if first time play
		int pieceNumber = get_rdm_number(0, 6);				//create new piece
		create_O_Piece(pieceNumber);

		nextblock_buffer = get_rdm_number(0, 6);			//create a new piece for the next block
		nextb.setCurrentFrame(nextblock_buffer);
	}
	else{
		create_O_Piece(nextblock_buffer);					//create new piece created before

		nextblock_buffer = get_rdm_number(0, 6);			//create a new piece for the next block
		nextb.setCurrentFrame(nextblock_buffer);
	}
}

//=============================================================================
// take 4 chuncks and points to the O_Piece
//=============================================================================
void Tetris::create_O_Piece(int n)
{
	int count = 0;

	switch (n)
	{
	case 0:
		cube_ptr = &cubeO;
		break;
	case 1:
		cube_ptr = &cubeI;
		break;
	case 2:
		cube_ptr = &cubeJ;
		break;
	case 3:
		cube_ptr = &cubeL;
		break;
	case 4: 
		cube_ptr = &cubeS;
		break;
	case 5:
		cube_ptr = &cubeT;
		break;
	case 6:
		cube_ptr = &cubeZ;
		break;
	default:
		cube_ptr = &cubeO;
		break;
	}

	for (std::shared_ptr<Block> b : vecBlocks){
		if (b->activate == false){
			b->activate = true;
			cube_ptr->vecPieces[count] = b;
			++count;
			if (genericCubeNS::N_BLOCKS == count)
				break;
		}
	}

	cube_ptr->resetOrient();

	//ptr_entity = &p_type_O;
}


//=============================================================================
// mark block position on map grid
//=============================================================================
std::vector<std::vector<std::shared_ptr<Block>>> Tetris::markMap(std::vector<std::vector<std::shared_ptr<Block>>>& m)
{
	std::vector<std::vector<std::shared_ptr<Block>>> update_map{ m };

	for (auto b : cube_ptr->vecPieces){
		int cnk_x = static_cast<int>((b->getX() - MAP_START_X) / MAP_TILE_WIDTH);
		int cnk_y = static_cast<int>((b->getY() - MAP_START_Y) / MAP_TILE_HEIGHT);

		for (std::shared_ptr<Block> b_mem : vecBlocks){
			if (b_mem == b){
				update_map[cnk_y][cnk_x] = b_mem;
				break;
			}
		}
	}
	return update_map;
}

//=============================================================================
// return true if block downards is occupied 
//=============================================================================
bool Tetris::isBlocked()
{
	for (auto b : cube_ptr->vecPieces){
		int cnk_x = static_cast<int>((b->getX() - MAP_START_X) / MAP_TILE_WIDTH);
		int cnk_y = static_cast<int>((b->getY() - MAP_START_Y) / MAP_TILE_HEIGHT);

		if (cnk_y == 19)
			return true;
		if (map[cnk_y + 1][cnk_x] != nullptr)
			return true;
	}
	return false;
}

//=============================================================================
// check if there is a line to delete
//=============================================================================
int Tetris::checkDeletion(int& l)
{
	int count = 0;
	int n_rowDeleted = 0;

	for (int i = MAP_HEIGTH - 1; i >= 0; --i){
		count = 0;
		for (int j = 0; j < MAP_WIDTH; ++j){
			if (map[i][j] != nullptr)
				++count;
		}
		//if (count == 0)
			//break;
		if (count == MAP_WIDTH){
			deleteRow(i);
			++n_rowDeleted;
			l = i;
			map = moveAllblocksDown(map, 1, l);
			++i;		//check again the line
		}
	}

	return n_rowDeleted;
}

//=============================================================================
// discativate chunck and set map cell to nullptr
//=============================================================================
void Tetris::deleteRow(int row)
{
	for (int col = 0; col < MAP_WIDTH; ++col){
		map[row][col]->activate = false;
		map[row][col] = nullptr;
	}
}

//=============================================================================
// update and move all blocks down from l (where occurs last deletion
//=============================================================================
std::vector<std::vector<std::shared_ptr<Block>>> Tetris::moveAllblocksDown(std::vector<std::vector<std::shared_ptr<Block>>>& m, int rows, int l)
{
	std::vector<std::vector<std::shared_ptr<Block>>> updated_map{ m };

	int row = MAP_HEIGTH - 1;
	int col = 0;
	/*
	while (row < 0 || updated_map[row][col] != nullptr)
		--row;
	if (row >= 0)
		row -= rows;
	*/
	
	for (int i = l; i >= 0; --i){					//start to move down for line "l"
		for (int j = 0; j < MAP_WIDTH; ++j){
			if (updated_map[i][j] != nullptr){
				updated_map[i][j]->setY(updated_map[i][j]->getY() + rows*MAP_TILE_HEIGHT);
				updated_map[i + rows][j] = updated_map[i][j];
				updated_map[i][j] = nullptr;
			}
		}
	}

	return updated_map;
}

//=============================================================================
// choose a number between d1 and d2 randomly
//=============================================================================
int Tetris::get_rdm_number(int d1, int d2)
{
	std::random_device rd;											// choose a seed randomly	
	std::default_random_engine generator(rd());						// Generators: Objects that generate uniformly distributed numbers.
	std::uniform_int_distribution<int> distribution(d1, d2);		// Distributions: Objects that transform sequences of numbers generated by a generator into sequences of numbers that follow a specific random variable distribution, such as uniform, Normal or Binomial.
	return distribution(generator);									// generates number in the range d1..d2
}

//=============================================================================
// if piece controlled by the player at starting point touches 
// a piece on the board, is game over
//=============================================================================
void Tetris::check_ifLose()
{
	for (auto b : cube_ptr->vecPieces){
		int cnk_x = static_cast<int>((b->getX() - MAP_START_X) / MAP_TILE_WIDTH);
		int cnk_y = static_cast<int>((b->getY() - MAP_START_Y) / MAP_TILE_HEIGHT);

		if (map[cnk_y + dy][cnk_x + dx] != nullptr){
			phase = LOSE;
			return;
		}
	}
	phase = MOVE;
}

//=============================================================================
// disabled all blocks, so they are availables for a new game
//=============================================================================
void Tetris::restartNewGame()
{
	for (int row = 0; row < MAP_HEIGTH; ++row){
		for (int col = 0; col < MAP_WIDTH; ++col){
			if (map[row][col] != nullptr){
				map[row][col]->activate = false;
				map[row][col] = nullptr;
			}
		}
	}
	for (auto b : cube_ptr->vecPieces)
		b->activate = false;

	points = 0;
	level = 1;
	t_step = TIME_STEP;
	startingGoal = STARTING_GOAL;
	goal = STARTING_GOAL;
	nextblock_buffer = -1;

	phase = INSERT;
}

//=============================================================================
// next level if
//=============================================================================
void Tetris::checkLevel(int rowDel)
{
	goal -= rowDel;
	if (goal <= 0){
		++level;
		startingGoal += 5;
		goal = startingGoal;
		if (t_step > 0.2f)
			t_step += 0.1f;
	}
}

//=============================================================================
// Loads the texture file(s) from disk.
//=============================================================================
void Tetris::init_textures()
{
	if (!chunck_T.initialize(graphics, BLOCK_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing chunck_T"));
	textures.push_back(&chunck_T);

	if (!background_t.initialize(graphics, BACKGROUND_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background_t"));
	textures.push_back(&background_t);

	if (!back2_t.initialize(graphics, BACK2_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing back2_t"));
	textures.push_back(&back2_t);

	if (!nextb_t.initialize(graphics, NEXTBLOCK_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nextb_t"));
	textures.push_back(&nextb_t);

	if (!gui_t.initialize(graphics, GUI_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing guiTexture"));
	textures.push_back(&gui_t);
}

//=============================================================================
// Initialize an Image,
// has spriteData object: properties required by Graphics::drawSprite to draw a sprite
//=============================================================================
void Tetris::init_images()
{
	if (!background.initialize(graphics, 0, 0, 0, &background_t))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background image"));
	background.setX(MAP_START_X - MAP_TILE_WIDTH);
	background.setY(MAP_START_Y);

	if (!back2.initialize(graphics, 0, 0, 0, &back2_t))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing back2_t image"));

	if (!nextb.initialize(graphics, 160, 80, 7, &nextb_t))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nextb image"));
	nextb.setCurrentFrame(0);
	nextb.setX(1280.0f);
	nextb.setY(200.0f);
}

//=============================================================================
// Initialize an entities with a texture
//=============================================================================
void Tetris::init_entities()
{
	for (int i = 0; i < 205; ++i){
		std::shared_ptr<Block> p(new Block);
		if (!p->initialize(this, 0, 0, 0, &chunck_T))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ptr block"));
		vecBlocks.push_back(std::move(p));
	}

	if (!gui.initialize(this, 0, 0, 0, &gui_t))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing gui object"));
}
