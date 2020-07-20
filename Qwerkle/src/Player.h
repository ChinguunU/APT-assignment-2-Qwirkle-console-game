#ifndef PLAYER
#define PLAYER

#include "LinkedList.h"
#include "Tile.h"

#include <string>

class Player
{

    friend class PlayerAi;
public:
    // Creates an empty deck and initialize atttributes
    Player(int playerNum, std::string name, LinkedList &handDeck);

    // Deletes the deck
    ~Player();

    // Return playerName
    std::string getPlayerName();

    // Return playerNum
    int getPlayerNum();

    // Checks wether or not player has tile in deck
    bool hasTile(Tile &tile);

    // Draw/insert deck puts a tile in players deck
    void insertDeck(Tile &tile);

    // Finds the tile and deletes the first occurence from players hand
    void removeTileFromHand(Tile &tile);

    // Player deck size
    int getNumTiles();

    // Set playerScore to score
    void setScore(int score);

    // Return playerScore
    int getScore();

    std::string getDeckString(bool colourize);

private:
    int playerScore = 0;
    int playerNum;
    std::string name;
    List deck;
};

typedef Player *PlayerPtr;
#endif // PLAYER