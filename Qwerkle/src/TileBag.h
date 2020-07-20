#ifndef TILE_BAG
#define TILE_BAG

#include "LinkedList.h"
#include "Tile.h"
#include "TileCodes.h"

#include <random>

#define NUM_OF_EACH_TILE 2

class TileBag
{
public:
    // Creates a randomly ordered list of 72 tiles(2 of each tile)
    TileBag();
    TileBag(LinkedList*& bag);
    ~TileBag();

    void generateTiles();
    int size();
    // Draws a tile from the
    // deletes the drawn tile from the tile bag
    // and returns it
    TilePtr draw();
    // Puts tile at the end of the tile bag
    TilePtr swap(Tile &tileToSwap);

    std::string toString();

private:
    List tileBag;
};
#endif // TILE_BAG
