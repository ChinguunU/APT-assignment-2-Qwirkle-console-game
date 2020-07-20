#ifndef COLORIZE
#define COLORIZE

#include <sstream>
#include <string>
#include <cstdlib>

class Colorize
{
public:
    std::string getColorByIndex(int index, std::string toColorize);
    std::string getAnyColorNotBlack(std::string toColorize);
};

#endif // COLORIZE