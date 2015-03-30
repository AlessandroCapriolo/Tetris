#include "generic_cube.h"
using namespace genericCubeNS;

GenericCube::GenericCube() : orient{ NORTH }
{
	vecPieces.resize(N_BLOCKS);
}
