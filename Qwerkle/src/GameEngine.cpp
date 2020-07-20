#include "GameEngine.h"

GameEngine::GameEngine()
{
    this->tileBag = nullptr;
    this->board = nullptr;
}

GameEngine::~GameEngine()
{
    delete tileBag;
    delete board;
    for (unsigned int loop = 0; loop != players.size(); ++loop)
    {

        delete players[loop];
    }
}

void GameEngine::addPlayer(int playerNum, std::string name, int score, LinkedList &handDeck)
{
    if (!nameIsUnique(name))
    {

        throw "Name is not unique";
    }
    else if (!nameIsUpperCase(name))
    {

        throw "Name is not upper case letters";
    }
    else
    {

        PlayerPtr player = new Player(playerNum, name, handDeck);
        player->setScore(score);
        players.push_back(player);
    }
}

void GameEngine::setBoard(Board *&board)
{
    this->board = board;
}

void GameEngine::setTileBag(TileBag *&tileBag)
{
    this->tileBag = tileBag;
}

void GameEngine::setCurrentPlayerName(std::string &name)
{
    this->currentPlayerName = name;
}

void GameEngine::setNumberOfAis(int num)
{
    this->numberOfAis = num;
}

int GameEngine::getNumberOfAis()
{
    return numberOfAis;
}

void GameEngine::startNewGame()
{
    currentPlayerName = players[0]->getPlayerName();
    this->tileBag = new TileBag();
    this->board = new Board();
    dealCards();
}

void GameEngine::placeTile(Tile &tile, int yCoordinate, int xCoordinate)
{
    PlayerPtr player = getCurrentPlayer();

    if (!player->hasTile(tile))
    {

        throw "Sorry you do not have the tile to place";
    }
    else
    {
        try
        {

            board->isPlayableTile(tile, yCoordinate, xCoordinate);
        }
        catch (const char *&exception)
        {

            throw exception;
        }

        // Setting score
        int playerScore = board->totalReceivablePoints(tile, yCoordinate, xCoordinate) + player->getScore();
        player->setScore(playerScore);

        // Placing tile
        board->placeTile(yCoordinate, xCoordinate, tile);
        player->removeTileFromHand(tile);
        if (tileBag->size() != 0)
        {

            player->insertDeck(*tileBag->draw());
        }

        shiftToNextPlayer();

        if (board->isQwirkle(yCoordinate, xCoordinate))
        {
            throw QwirkleException();
        }
    }
}

void GameEngine::replaceTile(Tile &tile)
{
    PlayerPtr player = getCurrentPlayer();

    if (!player->hasTile(tile))
    {

        throw "Sorry you do not have the tile to replace";
    }
    else if (tileBag->size() == 0)
    {

        throw "Sorry tile bag is empty you can not replace a tile";
    }
    else
    {

        player->insertDeck(*tileBag->swap(tile));
        player->removeTileFromHand(tile);
        shiftToNextPlayer();
    }
}

bool GameEngine::gameHasEnded()
{
    bool ended = false;
    for (PlayerPtr player : players)
    {

        if (player->getNumTiles() == 0)
        {

            ended = true;
        }
    }
    return ended;
}

std::string GameEngine::gameResults()
{
    std::string result;
    result.append("Game Over\n");
    for (PlayerPtr player : players)
    {
        std::stringstream stringStream;
        stringStream << "Score for "
                     << player->getPlayerName()
                     << ": "
                     << player->getScore()
                     << "\n";

        result.append(stringStream.str());
    }

    result.append("Player ");
    result.append(winnerName());
    result.append(" won!");

    return result;
}

std::string GameEngine::toString(bool colourize)
{
    std::stringstream stringBuilder;

    stringBuilder << currentPlayerName << ", it's your turn\n";

    for (PlayerPtr player : players)
    {
        stringBuilder << "Score for "
                      << player->getPlayerName()
                      << ": "
                      << player->getScore()
                      << "\n";
    }

    stringBuilder << "\n"
                  << board->toString(colourize)
                  << "\n\n"
                  << "Your hand is\n"
                  << getCurrentPlayer()->getDeckString(colourize);

    return stringBuilder.str();
}

std::string GameEngine::toFileString()
{
    std::stringstream stringBuilder;

    stringBuilder << players.size()
                  << "\n";
    for (PlayerPtr player : players)
    {
        stringBuilder << player->getPlayerName()
                      << "\n"
                      << player->getScore()
                      << "\n"
                      << player->getDeckString(false)
                      << "\n";
    }

    stringBuilder << board->toString(false)
                  << "\n"
                  << tileBag->toString()
                  << "\n"
                  << currentPlayerName
                  << "\n"
                  << numberOfAis;

    return stringBuilder.str();
}

void GameEngine::dealCards()
{

    for (PlayerPtr player : players)
    {

        for (int loop = 0; loop != STARTING_NUM_OF_TILES; ++loop)
        {

            player->insertDeck(*tileBag->draw());
        }
    }
}

PlayerPtr GameEngine::getCurrentPlayer()
{
    PlayerPtr currentPlayer = nullptr;
    for (PlayerPtr player : players)
    {

        if (player->getPlayerName() == currentPlayerName)
        {

            currentPlayer = player;
        }
    }

    return currentPlayer;
}

bool GameEngine::nameIsUnique(std::string &name)
{
    bool unique = true;
    for (PlayerPtr player : players)
    {

        if (player->getPlayerName() == name)
        {

            unique = false;
        }
    }

    return unique;
}

bool GameEngine::nameIsUpperCase(std::string &name)
{
    bool upperCase = false;
    std::regex nameUpperCase("[A-Z]+");

    if (std::regex_match(name, nameUpperCase))
    {
        upperCase = true;
    }

    return upperCase;
}

void GameEngine::shiftToNextPlayer()
{
    bool changePlayer = false;
    unsigned int loop = 0;
    while (!changePlayer)
    {

        if (players[loop]->getPlayerName() == currentPlayerName)
        {

            changePlayer = true;
        }
        loop = (loop + 1) % players.size();
    }
    currentPlayerName = players[loop]->getPlayerName();
}

std::string GameEngine::winnerName()
{
    std::string winner = "";
    int max = 0;
    PlayerPtr playerWinner = nullptr;

    for (PlayerPtr player : players)
    {
        if (player->getScore() > max)
        {
            playerWinner = player;
            max = player->getScore();
        }
    }
    if (playerWinner != nullptr)
    {
        winner.append(playerWinner->getPlayerName());
    }

    return winner;
}