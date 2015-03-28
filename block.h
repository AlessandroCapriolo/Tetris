#ifndef _BLOCK_H
#define _BLOCK_H
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace blockNS
{
	// image info
	const float X = GAME_WIDTH / 2;
	const float Y = GAME_HEIGHT/ 2;
	const int NUM_COLS = 0;
	const int WIDTH = 36;							// 1280x720, virtual resoultion of 400x240, scale 3x3, NES sprite 16x16
	const int HEIGHT = 36;							// 1920x1080, virtual resoultion of 400x240, scale 4.5x4.5, NES sprite 16x16

	// collision box
	const int   EDGE_TOP = -18;             // For BOX and ROTATE_BOX collison.
	const int   EDGE_BOTTOM = 18;           // "   relative to center
	const int   EDGE_LEFT = -18;            // "
	const int   EDGE_RIGHT = 18;            // "

	// Block state and behaviour modifier
	const float SPEED = 36;
}

class Block : public Entity
{
private:
	// update logic
	void keyboardMovement(float frameTime);

	// built-in 
	float speed;

public:
	enum colorType{
		CYAN,
		BLUE,
		ORANGE,
		YELLOW,
		GREEN,
		PURPLE,
		RED
	} color;

	Block();
	bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);
	void update(float frameTime);
	void draw();

	inline void moveLeft(float frameTime){ spriteData.x -= speed; }
	inline void moveRight(float frameTime){ spriteData.x += speed; }
	inline void moveDown(float frameTime){ spriteData.y += speed; }

	bool activate;
};
#endif
