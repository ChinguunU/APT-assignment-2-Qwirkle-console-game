#include "TileBag.h"

TileBag::TileBag()
{
  //initialising new temporary list
  List tempList = new LinkedList();

  char colourList[6] = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE};
  int shapeList[6] = {CIRCLE, STAR_4, DIAMOND, SQUARE, STAR_6, CLOVER};
  //Creating a list of 72 Tiles

  for (int x = 0; x < NUM_OF_EACH_TILE; ++x)
  {

    for (unsigned int i = 0; i < 6; ++i)
    {

      char colours = colourList[i];

      for (unsigned int j = 0; j < 6; ++j)
      {

        int shapes = shapeList[j];
        //Creating new tile
        TilePtr newTile = new Tile(colours, shapes);
        //appending tile to list

        tempList->addBack(*newTile);
      }
    }
  }

  std::random_device randomGen;
  tileBag = new LinkedList();
  while (tempList->size() != 0)
  {

    //Randomising tiles in list
    std::uniform_int_distribution<int> uniform_dist(0, tempList->size() - 1);
    int randInt = uniform_dist(randomGen);

    TilePtr curTile = tempList->get(randInt);
    //Adding the current tile to the tile bag
    tileBag->addBack(*curTile);
    //removing the current tile from temporary list
    tempList->remove(*curTile);
  }

  delete tempList;
}

TileBag::TileBag(LinkedList*& bag) {
  tileBag = bag;
}

TileBag::~TileBag()
{

  delete tileBag;
}

int TileBag::size()
{
  return tileBag->size();
}

TilePtr TileBag::swap(Tile &tileToSwap)
{
  TilePtr tileToReturn = nullptr;
  if (tileBag->size() != 0)
  {
    tileToReturn = tileBag->get(0);
    tileBag->deleteFront();
    tileBag->addBack(tileToSwap);
  }
  return tileToReturn;
}

TilePtr TileBag::draw()
{
  TilePtr tileToDraw = nullptr;
  if (tileBag->size() != 0)
  {
    tileToDraw = tileBag->get(0);
    tileBag->deleteFront();
  }
  return tileToDraw;
}

std::string TileBag::toString()
{
  return tileBag->toString(false);
}
