#include "block.h"
using namespace blockNS;

Block::Block() : Entity(), color{ CYAN }, speed{ SPEED }, activate{ false }
{
	spriteData.x = X;
	spriteData.y = Y;

	spriteData.width =	WIDTH;           
	spriteData.height = HEIGHT;
	spriteData.rect.bottom = HEIGHT;   
	spriteData.rect.right = WIDTH;

	collisionType = entityNS::BOX;
	edge.top = EDGE_TOP;              
	edge.bottom = EDGE_BOTTOM;
	edge.left = EDGE_LEFT;
	edge.right = EDGE_RIGHT;
}

//=============================================================================
// Initialize Block with texture
//=============================================================================
bool Block::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM)
{


	return(Entity::initialize(gamePtr, WIDTH, HEIGHT, NUM_COLS, textureM));
}

//=============================================================================
// update entity logic
//=============================================================================
void Block::update(float frameTime)
{
	if (activate == true)
		Entity::update(frameTime);

}

//=============================================================================
// move Player with keyboard
//=============================================================================
void Block::keyboardMovement(float frameTime)
{
	if (input->wasKeyPressed(VK_LEFT))
		spriteData.x -= speed;

	if (spriteData.x <= 0.0f)
		spriteData.x = 0.0f;

	if (input->wasKeyPressed(VK_RIGHT))
		spriteData.x += speed;

	if (spriteData.x >= GAME_WIDTH - WIDTH)
		spriteData.x = GAME_WIDTH - WIDTH;

	if (input->wasKeyPressed(VK_UP))
		spriteData.y -= speed;

	if (spriteData.y <= 0.0f)
		spriteData.y = 0.0f;

	if (input->wasKeyPressed(VK_DOWN))
		spriteData.y += speed;

	if (spriteData.y >= GAME_HEIGHT - HEIGHT)
		spriteData.y = GAME_HEIGHT - HEIGHT;
}

//=============================================================================
// draw the Block
//=============================================================================
void Block::draw()
{
	if (activate == true){
		switch (color)
		{
		case Block::CYAN:
			Image::draw(graphicsNS::CYAN);
			break;
		case Block::BLUE:
			Image::draw(graphicsNS::BLUE);
			break;
		case Block::ORANGE:
			Image::draw(graphicsNS::ORANGE);
			break;
		case Block::YELLOW:
			Image::draw(graphicsNS::YELLOW);
			break;
		case Block::GREEN:
			Image::draw(graphicsNS::GREEN);
			break;
		case Block::PURPLE:
			Image::draw(graphicsNS::PURPLE);
			break;
		case Block::RED:
			Image::draw(graphicsNS::RED);
			break;
		default:
			Image::draw();
			break;
		}
	}
}
