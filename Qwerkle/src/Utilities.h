#ifndef UTILITIES
#define UTILITIES

#include "Tile.h"
#include "LinkedList.h"

#include <string>
#include <vector>

#define TILE_COLOUR_INDEX 0
#define TILE_SHAPE_INDEX 1
#define COORDINATES_ROW_INDEX 0
#define COORDINATES_COL_INDEX 1

class Utilities {
public:
    TilePtr getTile(std::string& tile);
    std::vector<int> getCoordinates(std::string& coordinates);
    std::vector<std::string> split(std::string& stringToSplit, char regex);
    List getTiles(std::vector<std::string> tiles);
};

#endif // UTILITIES