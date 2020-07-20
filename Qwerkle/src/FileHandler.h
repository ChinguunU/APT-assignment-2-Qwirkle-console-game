#ifndef FILE_HANDLER
#define FILE_HANDLER

#include "GameEngine.h"
#include "Utilities.h"

#include <fstream>
#include <iostream>
#include <regex>

class FileHandler
{
public:
    // Return null if file doesn't exist
    GameEngine *loadGame(std::string fileName);
    void saveGame(GameEngine &gameEngine, std::string fileName);
};
#endif // FILE_HANDLER