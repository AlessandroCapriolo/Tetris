#ifndef _CUBET_H
#define _CUBET_H
#define WIN32_LEAN_AND_MEAN

#include <memory>

#include "block.h"
#include "generic_cube.h"

namespace cubetNS
{
	const float N1_CELL_X = 4.0f;
	const float N1_CELL_Y = 0.0f;

	const float N2_CELL_X = 5.0f;
	const float N2_CELL_Y = 0.0f;

	const float N3_CELL_X = 6.0f;
	const float N3_CELL_Y = 0.0f;

	const float N4_CELL_X = 5.0f;
	const float N4_CELL_Y = 1.0f;
}

class CubeT : public GenericCube
{
public:
	CubeT();
	void setPieces();
	void rotate(std::vector<std::vector<std::shared_ptr<Block>>>& map);
	void update(float frameTime);
	void draw();
};

#endif
