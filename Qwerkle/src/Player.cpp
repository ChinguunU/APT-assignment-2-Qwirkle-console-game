#include "Player.h"

Player::Player(int playerNum, std::string name, LinkedList &handDeck)
{
  this->playerNum = playerNum;
  this->name = name;
  this->deck = &handDeck;
}

Player::~Player()
{
  delete deck;
}

void Player::removeTileFromHand(Tile &tile)
{
  deck->remove(tile);
}

std::string Player::getPlayerName()
{
  return this->name;
}

int Player::getNumTiles()
{
  return deck->size();
}

int Player::getPlayerNum()
{
  return this->playerNum;
}

int Player::getScore()
{
  return this->playerScore;
}

bool Player::hasTile(Tile &tile)
{
  bool hasTile = false;
  for (int i = 0; i != deck->size(); ++i)
  {
    TilePtr tileItter = deck->get(i);
    if (tileItter->equals(tile))
    {
      hasTile = true;
    }
    delete tileItter;
  }
  return hasTile;
}

void Player::setScore(int score)
{
  this->playerScore = score;
}

void Player::insertDeck(Tile &tile)
{
  // Insert a tile in players deck
  deck->addBack(tile);
}

std::string Player::getDeckString(bool colourize)
{
  return deck->toString(colourize);
}