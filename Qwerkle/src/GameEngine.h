#ifndef GAME_ENGINE
#define GAME_ENGINE

#include "Player.h"
#include "TileBag.h"
#include "Board.h"
#include "QwirkleException.h"

#include <regex>

#define STARTING_NUM_OF_TILES 6
#define MAX_NUMBER_OF_TILES 72

class GameEngine
{

    friend class PlayerAi;
public:
    GameEngine();
    ~GameEngine();

    void addPlayer(int playerNum, std::string name, int score, LinkedList &handDeck);

    void setBoard(Board *&board);
    void setTileBag(TileBag *&tileBag);
    void setCurrentPlayerName(std::string &name);
    void setNumberOfAis(int num);
    int getNumberOfAis();

    void startNewGame();

    void placeTile(Tile &tile, int yCoordinate, int xCoordinate);
    void replaceTile(Tile &tile);

    bool gameHasEnded();

    std::string gameResults();
    std::string toString(bool colourize);
    std::string toFileString();

private:
    std::vector<PlayerPtr> players;
    TileBag *tileBag;
    Board *board;
    std::string currentPlayerName;
    int numberOfAis = 0;

    PlayerPtr getCurrentPlayer();
    bool nameIsUnique(std::string &name);
    bool nameIsUpperCase(std::string &name);
    void dealCards();
    void shiftToNextPlayer();
    std::string winnerName();
};
#endif // GAME_ENGINE
