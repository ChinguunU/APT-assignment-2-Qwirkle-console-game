#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H

#include "TileColorDictionary.h"

#include <string>
#include <sstream>

class Tile
{
public:
   Colour colour;
   Shape shape;
   Tile(Colour colour, Shape shape);
   Tile(Tile &tile);
   bool equals(Tile &tile);
   bool compatibleShape(Tile &tile);
   bool compatibleColour(Tile &tile);
   std::string toString(bool colourize);
};

typedef Tile *TilePtr;
#endif // ASSIGN2_TILE_H
