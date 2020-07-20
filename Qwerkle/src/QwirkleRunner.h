#ifndef QWIRKLE_RUNNER
#define QWIRKLE_RUNNER

#include "LinkedList.h"
#include "Board.h"
#include "TileCodes.h"
#include "GameEngine.h"
#include "QwirkleException.h"
#include "Utilities.h"
#include "FileHandler.h"
#include "PlayerAi.h"

#include <sstream>
#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>
#include <regex>

#define COMMAND_INDEX 0
#define TILE_INDEX 1
#define COORDINATES_INDEX 3
#define ROW_INDEX 0
#define COL_INDEX 1
#define FILE_NAME_INDEX 1

class QwirkleRunner
{
public:
    void runQwirkle();

private:
    void main(GameEngine*& engine, bool colourize);
    void loadGame(GameEngine*& engine, bool colourize);
    void newGame(GameEngine*& engine, bool colourize);
    void multiPlayerMode(GameEngine*& engine);
    void singlePlayerMode(GameEngine*& engine);
    void runGamePlay(GameEngine*& engine, bool colourize);
    bool playAiMoves(GameEngine*& engine);
    void playPlayerMoves(GameEngine*& engine, bool colourize);
    bool enableColourMode();

    std::string mainMenu();
    std::string playerModeMenu();
    std::string askForString();
    std::string helpMsg(); 
    std::string StudentInfo(); 
    int askForOption(int lowerBound, int numberOfOptions);
};

#endif // QWIRKLE_RUNNER