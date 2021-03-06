#include "cubes.h"
using namespace cubesNS;

CubeS::CubeS() : GenericCube()
{

}

//=============================================================================
// place chuncks in vecPieces in the right coordinate
//=============================================================================
void CubeS::setPieces()
{
	vecPieces[0]->setX(genericCubeNS::MAP_X + N1_CELL_X * blockNS::WIDTH);			//180
	vecPieces[0]->setY(genericCubeNS::MAP_Y + N1_CELL_Y * blockNS::WIDTH);

	vecPieces[1]->setX(genericCubeNS::MAP_X + N2_CELL_X * blockNS::WIDTH);
	vecPieces[1]->setY(genericCubeNS::MAP_Y + N2_CELL_Y * blockNS::WIDTH);

	vecPieces[2]->setX(genericCubeNS::MAP_X + N3_CELL_X * blockNS::WIDTH);
	vecPieces[2]->setY(genericCubeNS::MAP_Y + N3_CELL_Y * blockNS::WIDTH);

	vecPieces[3]->setX(genericCubeNS::MAP_X + N4_CELL_X * blockNS::WIDTH);
	vecPieces[3]->setY(genericCubeNS::MAP_Y + N4_CELL_Y * blockNS::WIDTH);

	for (auto b : vecPieces)
		b->color = Block::GREEN;
}

void CubeS::rotate(std::vector<std::vector<std::shared_ptr<Block>>>& map)
{
	int cnk_x = 0;
	int cnk_y = 0;
	
	switch (orient)
	{
	case GenericCube::NORTH:
	case GenericCube::SOUTH:
		cnk_x = static_cast<int>((vecPieces[2]->getX() - genericCubeNS::MAP_X) / blockNS::WIDTH);
		cnk_y = static_cast<int>((vecPieces[2]->getY() - genericCubeNS::MAP_Y) / blockNS::HEIGHT);
		if (cnk_y == 0)
			return;
		if (map[cnk_y - 1][cnk_x - 1] != nullptr || map[cnk_y][cnk_x - 1] != nullptr || map[cnk_y + 1][cnk_x] != nullptr)
			return;

		vecPieces[0]->setX(vecPieces[0]->getX() + 0 * blockNS::WIDTH);
		vecPieces[0]->setY(vecPieces[0]->getY() - 2 * blockNS::WIDTH);

		vecPieces[1]->setX(vecPieces[1]->getX() - 1 * blockNS::WIDTH);
		vecPieces[1]->setY(vecPieces[1]->getY() - 1 * blockNS::WIDTH);

		vecPieces[3]->setX(vecPieces[3]->getX() - 1 * blockNS::WIDTH);
		vecPieces[3]->setY(vecPieces[3]->getY() + 1 * blockNS::WIDTH);

		orient = EAST;
		break;
	case GenericCube::EAST:
	case GenericCube::WEST:
		cnk_x = static_cast<int>((vecPieces[2]->getX() - genericCubeNS::MAP_X) / blockNS::WIDTH);
		cnk_y = static_cast<int>((vecPieces[2]->getY() - genericCubeNS::MAP_Y) / blockNS::HEIGHT);
		if (cnk_x == 9)
			return;
		if (map[cnk_y + 1][cnk_x - 1] != nullptr || map[cnk_y + 1][cnk_x] != nullptr || map[cnk_y][cnk_x + 1] != nullptr)
			return;

		vecPieces[0]->setX(vecPieces[0]->getX() + 0 * blockNS::WIDTH);
		vecPieces[0]->setY(vecPieces[0]->getY() + 2 * blockNS::WIDTH);

		vecPieces[1]->setX(vecPieces[1]->getX() + 1 * blockNS::WIDTH);
		vecPieces[1]->setY(vecPieces[1]->getY() + 1 * blockNS::WIDTH);

		vecPieces[3]->setX(vecPieces[3]->getX() + 1 * blockNS::WIDTH);
		vecPieces[3]->setY(vecPieces[3]->getY() - 1 * blockNS::WIDTH);

		orient = NORTH;
		break;
	}
}

//=============================================================================
// update each chunck
//=============================================================================
void CubeS::update(float frameTime)
{
	for (auto b : vecPieces)
		b->update(frameTime);
}

//=============================================================================
// draw all chunks in vecPieces
//=============================================================================
void CubeS::draw()
{
	for (auto b : vecPieces)
		b->draw();
}
