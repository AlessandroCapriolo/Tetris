#include "cubeo.h"
using namespace cubeoNS;

CubeO::CubeO() : GenericCube()
{
	
}

//=============================================================================
// place chuncks in vecPieces in the right coordinate
//=============================================================================
void CubeO::setPieces()
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
		b->color = Block::YELLOW;
}

void CubeO::rotate(std::vector<std::vector<std::shared_ptr<Block>>>& map)
{

}

//=============================================================================
// update each chunck
//=============================================================================
void CubeO::update(float frameTime)
{
	for (auto b : vecPieces)
		b->update(frameTime);
}

//=============================================================================
// draw all chunks in vecPieces
//=============================================================================
void CubeO::draw()
{
	for (auto b : vecPieces)
		b->draw();
}
