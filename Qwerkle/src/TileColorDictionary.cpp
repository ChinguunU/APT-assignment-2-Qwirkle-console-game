#include "TileColorDictionary.h"

TileColorDictionary::TileColorDictionary()
{
    colorMap.insert({RED, 1});
    colorMap.insert({ORANGE, 9});
    colorMap.insert({YELLOW, 3});
    colorMap.insert({GREEN, 2});
    colorMap.insert({BLUE, 4});
    colorMap.insert({PURPLE, 5});
}

std::string TileColorDictionary::getColor(Colour colour, Shape shape)
{
    std::stringstream stringStream;
    stringStream << colour << shape;
    std::string toColourString;
    stringStream >> toColourString;

    Colorize colorizer;
    return colorizer.getColorByIndex(colorMap[colour], toColourString);
}