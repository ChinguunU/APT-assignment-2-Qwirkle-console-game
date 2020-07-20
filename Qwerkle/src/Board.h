#ifndef BOARD
#define BOARD

#include "Tile.h"
#include "Colorize.h"

#include <iostream>
#include <sstream>
#include <vector>

#define MAX_ROWS 26
#define MAX_COLS 26
#define MAX_TILES_IN_LINE 6
#define DIRECTIONS 4
#define DIAGONALS 2

class Board
{
public:
    Board();
    ~Board();
    void placeTile(int row, int col, Tile &tile);
    void isPlayableTile(Tile &tile, int row, int col);
    int totalReceivablePoints(Tile &tile, int row, int col);
    bool isQwirkle(int row, int col);
    int getCurrentRows();
    int getCurrentCols();
    std::string toString(bool colourize);

private:
    int currRows = 1;
    int currCols = 1;
    std::vector<std::vector<TilePtr>> board;

    // Methods to simplify isPlayableTile
    std::vector<TilePtr> getTilesInDiagonal(int row, int col, int positiveDiagonal);
    bool allTilesUnique(std::vector<TilePtr> list);
    bool boardIsEmpty();

    // For resizing the board
    void addRows(int row);
    void addCols(int col);

    // For generating the board string
    std::string generateBoardString(bool colourize);
    std::string rowNumbers(int startingInt, bool colourize);
    std::string alphabetColLetter(int rowNumber, bool colourize);
    std::string dashLine();
};

#endif // BOARD