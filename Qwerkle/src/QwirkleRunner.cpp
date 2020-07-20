#include "QwirkleRunner.h"

void QwirkleRunner::runQwirkle()
{
    GameEngine *engine = nullptr;
    try {   
        bool enableColour = enableColourMode();
        std::cout << "\nWelcome to Qwirkle!" << std::endl;
        std::cout << "-------------------\n"
                << std::endl;
        
        main(engine, enableColour);
    } 
    catch (std::runtime_error &quit)
    {
        delete engine;
        std::cout << quit.what() << std::endl;
    }
}

void QwirkleRunner::main(GameEngine*& engine, bool colourize) {
    std::cout << mainMenu()
              << "\n"
              << std::endl;
    try
    {
        int option = askForOption(1, 4);
        if (option == 1)
        {

            newGame(engine, colourize);
        }
        else if (option == 2)
        {

            loadGame(engine, colourize);
        }
        else if (option == 3)
        {
          
            std::cout << "\n" << StudentInfo() << "\n" << std::endl;
            main(engine, colourize);
        }
        else
        {

            throw std::runtime_error("\nGoodbye");
        }
    }
    catch (std::runtime_error &quit)
    {
        delete engine;
        std::cout << quit.what() << std::endl;
    }
}

void QwirkleRunner::newGame(GameEngine *&engine, bool colourize)
{
    engine = new GameEngine();
    std::cout << "\nStarting a New Game" << std::endl;

    std::cout << "\n"
              << playerModeMenu() 
              << "\n"
              << std::endl;

    int playerMode = askForOption(1, 2);

    if (playerMode == 1)
    {
        singlePlayerMode(engine);
    }
    else
    {
        multiPlayerMode(engine);
    }

    std::cout << "\nLet's Play!" << std::endl;

    engine->startNewGame();

    runGamePlay(engine, colourize);
}

void QwirkleRunner::loadGame(GameEngine *&engine, bool colourize)
{
    std::cout << "\nEnter the file name from which to load a game" << std::endl;
    std::string fileName = askForString();
    bool correctFileName = false;
    while (!correctFileName)
    {
        try
        {
            FileHandler fileLoad = FileHandler();
            engine = fileLoad.loadGame(fileName);
            std::cout << "\nQwirkle game successfully loaded" << std::endl;
            correctFileName = true;
        }
        catch (const char *&exception)
        {

            std::cout << exception << std::endl;
            fileName = askForString();
        }
    }

    runGamePlay(engine, colourize);
}

void QwirkleRunner::multiPlayerMode(GameEngine *&engine)
{
    std::cout << "\nEnter number of players you want to play (2 - 4)" << std::endl;
    int players = askForOption(2, 4);

    for (int loop = 0; loop < players; ++loop)
    {
        std::cout << "\nEnter a name for player " << loop + 1 << " (uppercase characters only)" << std::endl;
        std::string names = askForString();

        List deck = new LinkedList();
        try
        {
            engine->addPlayer(loop + 1, names, 0, *deck);
        }
        catch (const char *&exception)
        {

            delete deck;
            std::cout << exception << std::endl;
            loop--;
        }
    }
}

void QwirkleRunner::singlePlayerMode(GameEngine *&engine)
{
    std::cout << "\nEnter number of AI you want to play (1 - 3)" << std::endl;
    int numberOfAis = askForOption(1, 3);

    for (int loop = 0; loop < numberOfAis + 1; ++loop)
    {
        if (loop == 0)
        {
            std::cout << "\nEnter a name for your player (uppercase characters only)" << std::endl;
        }
        else
        {
            std::cout << "\nEnter a name for your AI " << (loop + 1) << " (uppercase characters only)" << std::endl;
        }
        std::string name = askForString();

        List deck = new LinkedList();
        try
        {
            engine->addPlayer(loop + 1, name, 0, *deck);
        }
        catch (const char *&exception)
        {
            delete deck;
            std::cout << exception << std::endl;
            --loop;
        }
    }

    engine->setNumberOfAis(numberOfAis);
}

void QwirkleRunner::runGamePlay(GameEngine *&engine, bool colourize)
{
    bool gameEnded = engine->gameHasEnded();
    while (!gameEnded)
    {

        playPlayerMoves(engine, colourize);
        gameEnded = playAiMoves(engine);
    }

    if (gameEnded)
    {
        std::cout << "\n"
                  << engine->gameResults() << std::endl;
        throw std::runtime_error("\nGoodbye");
    }
}

bool QwirkleRunner::playAiMoves(GameEngine *&engine)
{
    PlayerAi Ai = PlayerAi();
    bool gameEnded = false;
    for (int loop = 0; loop < engine->getNumberOfAis() && !gameEnded; ++loop)
    {
        if (!engine->gameHasEnded())
        {
            Ai.playAiMove(engine);
        }
        else
        {
            gameEnded = true;
        }
    }

    return gameEnded;
}

void QwirkleRunner::playPlayerMoves(GameEngine *&engine, bool colourize)
{
    bool moveMade = false;
    while (!moveMade)
    {
        Tile *tile = nullptr;
        try
        {
            std::cout << "\n"
                      << engine->toString(colourize) << "\n"
                      << std::endl;

            std::regex placeMoveCommand("place [ROYGBP][1-6] at [A-Z]([0-9]|1[0-9]|2[0-5])");
            std::regex replaceMoveCommand("replace [ROYGBP][1-6]");
            std::regex saveCommand("save [A-Za-z0-9]+");

            std::string command = askForString();

            Utilities utility = Utilities();
            std::vector<std::string> splitCommand = utility.split(command, ' ');
            if (std::regex_match(command, placeMoveCommand))
            {

                std::vector<int> coordinates = utility.getCoordinates(splitCommand[COORDINATES_INDEX]);
                tile = utility.getTile(splitCommand[TILE_INDEX]);

                engine->placeTile(*tile, coordinates[ROW_INDEX], coordinates[COL_INDEX]);
                moveMade = true;
            }
            else if (std::regex_match(command, replaceMoveCommand))
            {

                tile = utility.getTile(splitCommand[TILE_INDEX]);

                engine->replaceTile(*tile);
                moveMade = true;
            }
            else if (std::regex_match(command, saveCommand))
            {

                std::string fileName = splitCommand[FILE_NAME_INDEX];
                FileHandler fileSave = FileHandler();

                fileSave.saveGame(*engine, fileName);
                std::cout << "Game successfully saved" << std::endl;
            }
            else if (command == "help")
            {

                std::cout << "\n" << helpMsg() << "\n" << std::endl;
            }
            else if (command == "quit")
            {

                throw std::runtime_error("\nGoodbye");
            }
            else
            {

                std::cout << "Command not recognized, for help type command 'help'" << std::endl;
            }
        }
        catch (const char *&exception)
        {

            delete tile;
            std::cout << exception << std::endl;
        }
        catch (QwirkleException &qwirkle)
        {
            moveMade = true;
            std::cout << "\n"
                      << qwirkle.what() << std::endl;
        }
    }
}

bool QwirkleRunner::enableColourMode()
{
    std::cout << "\nDo you want to enable colour mode for the game?[y or n]" << std::endl;
    bool enable = false;
    bool inputAccepted = false;
    while (!inputAccepted)
    {
        std::string enableColour = askForString();
        
        
        if (enableColour.compare("y") == 0)
        {
            inputAccepted = true;
            enable = true;
        }
        else if(enableColour == "n")
        {
            inputAccepted = true;
            enable = false;
        }   
        else
        {
            std::cout << "please enter y for enable or n for disable, thank you" << std::endl;
        }
    }

    return enable;
}

int QwirkleRunner::askForOption(int lowerBound, int numberOfOptions)
{
    int option = lowerBound - 1;
    std::string command;

    while (option < lowerBound || option > numberOfOptions)
    {

        command = askForString();
        option = atoi(command.c_str());

        if (option < lowerBound || option > numberOfOptions)
        {

            std::cout << "Invalid option please enter a valid option" << std::endl;
        } 
    }
    return option;
}

std::string QwirkleRunner::askForString()
{
    bool valid = false;
    std::string string;

    std::cout << "> ";
    std::getline(std::cin, string);
    while (!valid)
    {

        if (std::cin.eof())
        {

            throw std::runtime_error("\n\nGoodbye");
        }
        else if (std::cin.fail() || string == "")
        {

            std::cout << "Invalid command please choose a valid command"
                      << "\n"
                      << "> ";

            std::getline(std::cin, string);
        }
        else
        {

            valid = true;
        }
    }

    // This has caused me a lot of trouble
    // however when you create a file in windows 
    // it stores a new line character as "\r\n"
    // whereas a linux OS stores it as "\n". 
    // The problem was caused when i used getline to get an input string
    // as it didn't ignore "\r" hence causing unknown errors to the gameoutput
    
    std::size_t carriageReturn = string.find("\r");
    if(carriageReturn != std::string::npos) {
        string = string.substr(0, string.size() - 1);
    }
    
    return string;
}

std::string QwirkleRunner::mainMenu()
{
    std::string menu;
    menu.append("menu\n");
    menu.append("----\n");
    menu.append("1. New Game\n");
    menu.append("2. Load Game\n");
    menu.append("3. Show Student Information\n");
    menu.append("4. Quit");

    return menu;
}

std::string QwirkleRunner::playerModeMenu()
{
    std::string menu;
    menu.append("PlayerMode\n");
    menu.append("----------\n");
    menu.append("1. Singleplayer\n");
    menu.append("2. Multiplayer");

    return menu;
}

std::string QwirkleRunner::StudentInfo() {
    std::string stud;
    stud.append("---------------------------------\n");
    stud.append("Name: Chinguun Undrakh\n");
    stud.append("Student ID: s3774562\n");
    stud.append("Email: s3774562@student.rmit.edu.au\n");
    stud.append("\n");
    stud.append("Name: Alejandro Tchung\n");
    stud.append("Student ID: s3722126\n");
    stud.append("Email: s3722126@student.rmit.edu.au\n");
    stud.append("\n");
    stud.append("Name: Jiajun Zhu\n");
    stud.append("Student ID: s3556752\n");
    stud.append("Email: s3556752@student.rmit.edu.au\n");
    stud.append("\n");
    stud.append("Name: Jonathan Haddad\n");
    stud.append("Student ID: s3722092\n");
    stud.append("Email: s3722092@student.rmit.edu.au\n");
    stud.append("---------------------------------");

    return stud;

}

std::string QwirkleRunner::helpMsg() {
    std::string help;
    help.append("----------------------\n");
    help.append("Hello, need some help?\n");
    help.append("----------------------\n");
    help.append("\n");
    help.append("---------------\n");
    help.append("Placing a tile:\n");
    help.append("---------------\n");
    help.append("\n");
    help.append("Each line can only contain one of each color and one of each shape.\n");
    help.append("The tile being placed must connect to another tile on the board\n");
    help.append("\n");
    help.append("To place a tile, type: 'place <Tile> at <Coordinates>'\n");
    help.append("For example: 'place G5 at A2'\n");
    help.append("A tile can only be consisted of R,B,P,O,Y,G with shape numbers 1-6\n");
    help.append("The coordinate position rows extend from A to Z and colums extend from 0 to 25\n");
    help.append("\n");
    help.append("To replace a tile, type: 'replace <Tile>'\n");
    help.append("For example: 'replace G5'\n");
    help.append("You will then get a new tile in its place.\n");
    help.append("This will skip your turn.\n");
    help.append("\n");
    help.append("-------------------\n");
    help.append("Saving and Quitting\n");
    help.append("-------------------\n");
    help.append("\n");
    help.append("You can type 'save <savename>' to save your current game progress.\n");
    help.append("\n");
    help.append("You can type 'quit' to exit the game, make sure you save first if you want to keep your progress.\n");
    help.append("-------------------------------------------------------------------------------------------------");
 
    return help;

}