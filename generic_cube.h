#ifndef _GENERICCUBE_H
#define _GENERICCUBE_H
#define WIN32_LEAN_AND_MEAN

#include <memory>
#include <vector>

#include "block.h"

namespace genericCubeNS
{
	const int N_BLOCKS = 4;
	const float MAP_X = 780.0f;
	const float MAP_Y = 180.0f;
}

class GenericCube
{
protected:
	enum Orientation{
		NORTH,
		EAST,
		SOUTH,
		WEST
	} orient;

public:
	GenericCube();
	std::vector<std::shared_ptr<Block>> vecPieces;
	inline void resetOrient() { orient = NORTH; }
	virtual void setPieces() = 0;
	virtual void rotate(std::vector<std::vector<std::shared_ptr<Block>>>& map) = 0;
	virtual void update(float frameTime) = 0;
	virtual void draw() = 0;
};

#endif
