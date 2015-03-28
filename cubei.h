#ifndef _CUBEI_H
#define _CUBEI_H
#define WIN32_LEAN_AND_MEAN

#include <memory>

#include "block.h"
#include "generic_cube.h"

namespace cubeiNS
{
	const float N1_CELL_X = 3.0f;
	const float N1_CELL_Y = 0.0f;

	const float N2_CELL_X = 4.0f;
	const float N2_CELL_Y = 0.0f;

	const float N3_CELL_X = 5.0f;
	const float N3_CELL_Y = 0.0f;

	const float N4_CELL_X = 6.0f;
	const float N4_CELL_Y = 0.0f;
}

class CubeI : public GenericCube
{
public:
	CubeI();
	void setPieces();
	void rotate(std::vector<std::vector<std::shared_ptr<Block>>>& map);
	void update(float frameTime);
	void draw();
};

#endif
