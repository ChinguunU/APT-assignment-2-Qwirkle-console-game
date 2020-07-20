#include "Colorize.h"

std::string Colorize::getColorByIndex(int index, std::string toColorize)
{
    std::string coloredString;
    std::stringstream stringStream;
    stringStream << "\u001b[38;5;"
                 << (index % 256)
                 << "m"
                 << toColorize
                 << "\u001b[0m";

    stringStream >> coloredString;
    return coloredString;
}

// Did not use method getColorByIndex because i didnt want a black color
std::string Colorize::getAnyColorNotBlack(std::string toColorize)
{
    int random = ((rand() % 230) + 1);
    return getColorByIndex(random, toColorize);
}