#ifndef ASSIGN1_TILE_COLOR_DICTIONARY_H
#define ASSIGN1_TILE_COLOR_DICTIONARY_H

#include "TileCodes.h"
#include "Colorize.h"

#include <map>

class TileColorDictionary
{
public:
    TileColorDictionary();
    std::string getColor(Colour colour, Shape shape);

private:
    std::map<char, int> colorMap;
};

#endif // ASSIGN1_TILE_COLOR_DICTIONARY_H