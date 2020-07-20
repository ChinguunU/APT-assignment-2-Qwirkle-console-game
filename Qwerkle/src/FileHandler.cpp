#include "FileHandler.h"

void FileHandler::saveGame(GameEngine &gameEngine, std::string fileName)
{
    std::string path = "savedGames//";
    path.append(fileName);
    path.append(".txt");

    std::ofstream outFile;
    outFile.open(path);

    if (outFile.good())
    {
        outFile << gameEngine.toFileString();
    }
    else
    {
        throw "File could not be saved";
    }

    outFile.close();
}

GameEngine *FileHandler::loadGame(std::string fileName)
{
    std::string path = "savedGames//";
    path.append(fileName);
    path.append(".txt");

    std::ifstream inFile;
    inFile.open(path);
    GameEngine *engine = nullptr;
    if (inFile.good())
    {

        engine = new GameEngine();
        Utilities utility = Utilities();

        // Reading the number of players
        std::string line;
        std::getline(inFile, line);
        int numPlayers = std::stoi(line);

        // Reading the players
        for (int loop = 0; loop < numPlayers; ++loop)
        {

            std::getline(inFile, line);
            std::string name = line;

            std::getline(inFile, line);
            int score = std::stoi(line);

            std::getline(inFile, line);
            char regex = ',';
            List deck = utility.getTiles(utility.split(line, regex));

            engine->addPlayer(loop + 1, name, score, *deck);
        }

        for (int loop = 0; loop < 3; ++loop)
        {
            std::getline(inFile, line);
        }

        // Reading the board
        std::regex validTile("[ROYGBP][1-6]");
        Board *board = new Board();
        int rowCoordinate = 0;
        while (line.find("-") == std::string::npos)
        {
            std::size_t startingPos = line.find("|");
            char regex = '|';
            std::string stringToSplit = line.substr(startingPos).substr(1, std::string::npos);
            std::vector<std::string> row = utility.split(stringToSplit, regex);

            for (unsigned int loop = 0; loop < row.size(); ++loop)
            {

                int colCoordinate;
                if (rowCoordinate % 2 == 0)
                {
                    colCoordinate = loop * 2;
                }
                else
                {
                    colCoordinate = (loop * 2) + 1;
                }

                if (std::regex_match(row[loop].substr(1, 2), validTile))
                {
                    std::string tileString = row[loop].substr(1, 2);
                    Tile *tile = utility.getTile(tileString);
                    board->placeTile(rowCoordinate, colCoordinate, *tile);
                }
            }
            rowCoordinate++;
            std::getline(inFile, line);
        }

        engine->setBoard(board);

        // Reading the tileBag
        for (int loop = 0; loop < 2; ++loop)
        {
            std::getline(inFile, line);
        }
        char regex = ',';
        List bag = utility.getTiles(utility.split(line, regex));
        TileBag *tileBag = new TileBag(bag);
        engine->setTileBag(tileBag);
        
        // Reading the current player
        std::getline(inFile, line);
        engine->setCurrentPlayerName(line);

        // Reading the number of AIs
        std::getline(inFile, line);
        engine->setNumberOfAis(std::stoi(line));
    }
    else
    {

        throw "File could not be loaded";
    }

    inFile.close();

    return engine;
}