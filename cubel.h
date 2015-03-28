#ifndef _CUBEL_H
#define _CUBEL_H
#define WIN32_LEAN_AND_MEAN

#include <memory>

#include "block.h"
#include "generic_cube.h"

namespace cubelNS
{
	const float N1_CELL_X = 3.0f;
	const float N1_CELL_Y = 0.0f;

	const float N2_CELL_X = 4.0f;
	const float N2_CELL_Y = 0.0f;

	const float N3_CELL_X = 5.0f;
	const float N3_CELL_Y = 0.0f;

	const float N4_CELL_X = 3.0f;
	const float N4_CELL_Y = 1.0f;
}

class CubeL : public GenericCube
{
public:
	CubeL();
	void setPieces();
	void rotate(std::vector<std::vector<std::shared_ptr<Block>>>& map);
	void update(float frameTime);
	void draw();
};

#endif
