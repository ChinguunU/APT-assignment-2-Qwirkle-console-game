#include "Board.h"

Board::Board()
{
    std::vector<TilePtr> empty;
    empty.push_back(nullptr);
    this->board.push_back(empty);
}

Board::~Board()
{
    for (int loop = 0; loop < currRows; ++loop)
    {

        for (int loopIn = 0; loopIn < currCols; ++loopIn)
        {

            if (board[loop][loopIn] != nullptr)
            {

                delete board[loop][loopIn];
            }
        }
    }
}

void Board::placeTile(int row, int col, Tile &tile)
{
    int colToExpandTo = col;
    int rowToExpandTo = row;
    if (row != MAX_ROWS - 1)
    {
        rowToExpandTo++;
    }
    if (col != MAX_COLS - 1)
    {
        colToExpandTo++;
    }

    if (rowToExpandTo < currRows && colToExpandTo < currCols)
    {

        board[row][col] = &tile;
    }
    else
    {

        addCols(colToExpandTo);
        addRows(rowToExpandTo);
        board[row][col] = &tile;
    }
}

void Board::isPlayableTile(Tile &tile, int row, int col)
{
    if ((row + col) % 2 == 0) 
    {
        if (!boardIsEmpty())
        {
            if(row < currRows && col < currCols) 
            {
                if (board[row][col] != nullptr)
                {

                    throw "A tile is already placed in the specified coordinates";
                }
                else
                {

                    std::vector<TilePtr> diagonal;

                    int emptyDiagonals = 0;
                    for (int loop = 0; loop != DIAGONALS; ++loop)
                    {

                        diagonal = getTilesInDiagonal(row, col, loop);
                        if (diagonal.size() == 0)
                        {

                            emptyDiagonals++;
                        }

                        bool compatibleShape = true;
                        bool compatibleColour = true;
                        if (diagonal.size() < MAX_TILES_IN_LINE)
                        {

                            diagonal.push_back(&tile);
                            if (allTilesUnique(diagonal))
                            {

                                for (unsigned int loopIn = 0; loopIn < diagonal.size(); ++loopIn)
                                {

                                    compatibleShape = compatibleShape && tile.compatibleShape(*diagonal[loopIn]);
                                    compatibleColour = compatibleColour && tile.compatibleColour(*diagonal[loopIn]);
                                }

                                if (!compatibleColour && !compatibleShape)
                                {

                                    throw "The tile being played is not compatible with the lines or line";
                                }
                            }
                            else
                            {

                                throw "All tiles in a line must be unique";
                            }
                        }
                        else
                        {

                            throw "Playing the tile in the specified coordinates will cause too many tiles in a line(must be less than 6)";
                        }
                    }

                    if (emptyDiagonals == DIAGONALS)
                    {

                        throw "The tile being played must connect to another tile on the Board";
                    }
                }
            } 
            else 
            {

                throw "The tile being played must connect to another tile on the Board";
            }
        }
    }
    else 
    {

        throw "The specified coordinates don't exist";
    }
}

int Board::totalReceivablePoints(Tile &tile, int row, int col)
{
    std::vector<TilePtr> diagonal;
    int points = 0;
    if (!boardIsEmpty())
    {
        for (int loop = 0; loop != DIAGONALS; ++loop)
        {

            diagonal = getTilesInDiagonal(row, col, loop);
            if (diagonal.size() != 0)
            {

                diagonal.push_back(&tile);
                if (diagonal.size() == MAX_TILES_IN_LINE)
                {
                    points = points + MAX_TILES_IN_LINE;
                }
                points = points + diagonal.size();
            }
        }
    }
    else
    {

        points = 1;
    }
    return points;
}

bool Board::isQwirkle(int row, int col)
{
    std::vector<TilePtr> diagonal;

    bool qwirkle = false;
    for (int loop = 0; loop != DIAGONALS && !qwirkle; ++loop)
    {

        diagonal = getTilesInDiagonal(row, col, loop);
        diagonal.push_back(nullptr);
        if (diagonal.size() == MAX_TILES_IN_LINE)
        {

            qwirkle = true;
        }
    }
    return qwirkle;
}

int Board::getCurrentRows() {
    return currRows;
}

int Board::getCurrentCols() {
    return currCols;
}

std::string Board::toString(bool colourize)
{
    std::string board;
    int loop = 0;

    board.append(rowNumbers(loop, colourize));
    board.append("\n");
    while (loop < 2)
    {

        board.append(dashLine());
        board.append("\n");
        if (loop == 0)
        {

            board.append(generateBoardString(colourize));
        }
        loop++;
    }
    board.append(rowNumbers(loop - 1, colourize));

    return board;
}

/*                                     */
/*          MY PRIVATE METHODS         */
/*                                     */

std::vector<TilePtr> Board::getTilesInDiagonal(int row, int col, int positiveDiagonal)
{
    std::vector<TilePtr> tilesInDiagonalLine;

    int posOrNegDiagonal;
    if (positiveDiagonal == 0)
    {
        posOrNegDiagonal = -1;
    }
    else
    {
        posOrNegDiagonal = 1;
    }

    for (int loop = 0; loop != DIAGONALS; ++loop)
    {

        int xAxis[DIRECTIONS] = {-1, 1};
        int yAxis[DIRECTIONS] = {-1, 1};

        bool endOfLine = false;
        for (int loopIn = 1; loopIn <= MAX_TILES_IN_LINE && !endOfLine; ++loopIn)
        {

            int y = row + yAxis[loop] * loopIn;
            int x = col + xAxis[loop] * posOrNegDiagonal * loopIn;
            if (y >= 0 && y < currRows && x >= 0 && x < currCols)
            {

                if (board[y][x] != nullptr)
                {
                    tilesInDiagonalLine.push_back(board[y][x]);
                }
                else
                {
                    endOfLine = true;
                }
            }
            else
            {
                endOfLine = true;
            }
        }
    }
    return tilesInDiagonalLine;
}

bool Board::allTilesUnique(std::vector<TilePtr> list)
{
    bool allUnique = true;
    for (unsigned int loop = 0; loop != list.size() && allUnique; ++loop)
    {

        for (unsigned int loopIn = loop + 1; loopIn != list.size() && allUnique; ++loopIn)
        {

            if (list[loop]->equals(*list[loopIn]))
            {

                allUnique = false;
            }
        }
    }
    return allUnique;
}

bool Board::boardIsEmpty()
{
    bool empty = true;
    for (int loop = 0; loop != currRows && empty; ++loop)
    {

        for (int loopIn = 0; loopIn != currCols && empty; ++loopIn)
        {

            if (board[loop][loopIn] != nullptr)
            {

                empty = false;
            }
        }
    }

    return empty;
}

/*                                                   */
/*          MY PRIVATE METHODS FOR RESIZING          */
/*                                                   */

void Board::addRows(int row)
{
    if (row >= currRows)
    {
        while (row >= currRows)
        {

            std::vector<TilePtr> newRow;
            for (int loop = 0; loop != currCols; ++loop)
            {

                newRow.push_back(nullptr);
            }
            board.push_back(newRow);
            currRows++;
        }
    }
}

void Board::addCols(int col)
{
    if (col >= currCols)
    {

        for (int loop = 0; loop != currRows; ++loop)
        {

            int columnsToAdd = currCols;
            while (col >= columnsToAdd)
            {

                board[loop].push_back(nullptr);
                columnsToAdd++;
            }
        }
        currCols = col + 1;
    }
}

/*                                                               */
/*          MY PRIVATE METHODS FOR GENERATING BOARD STRING       */
/*                                                               */

std::string Board::generateBoardString(bool colourize)
{
    std::string boardString;

    for (int loop = 0; loop < currRows; ++loop)
    {

        boardString.append(alphabetColLetter(loop, colourize));
        boardString.append("  ");
        if (loop % 2 != 0)
        {

            boardString.append("   |");
        }
        else if (loop % 2 == 0)
        {

            boardString.append("|");
        }
        for (int loopIn = 0; loopIn < currCols; ++loopIn)
        {

            if ((loop + loopIn) % 2 == 0)
            {

                if (board[loop][loopIn] != nullptr)
                {
                    boardString.append(" ");
                    boardString.append(board[loop][loopIn]->toString(colourize));
                    boardString.append(" |");
                }
                else
                {
                    boardString.append("    |");
                }
            }
        }
        boardString.append("\n");
    }

    return boardString;
}

std::string Board::rowNumbers(int startingInt, bool colourize)
{
    std::string rowNumberLine;

    rowNumberLine.append("     ");
    if (startingInt != 0)
    {

        rowNumberLine.append("   ");
    }
    while (startingInt < currCols)
    {

        if (colourize)
        {
            Colorize colorizer;
            std::string coloredNum = colorizer.getAnyColorNotBlack(std::to_string(startingInt));
            rowNumberLine.append(coloredNum);
        }
        else
        {
            std::stringstream stringStream;
            stringStream << startingInt;
            rowNumberLine.append(stringStream.str());
        }
        if (startingInt < 10)
        {

            rowNumberLine.append("    ");
        }
        else
        {

            rowNumberLine.append("   ");
        }

        startingInt = startingInt + 2;
    }
    return rowNumberLine;
}

std::string Board::alphabetColLetter(int rowNumber, bool colourize)
{
    char character = 'A' + rowNumber;
    std::string stringCharacter(1, character);
    std::string letter;

    if (colourize)
    {
        Colorize colorizer;
        letter = colorizer.getAnyColorNotBlack(stringCharacter);
    }
    else
    {
        letter.append(stringCharacter);
    }
    return letter;
}

std::string Board::dashLine()
{
    std::string dashLine;

    dashLine.append("   ");
    if (currCols % 2 == 0)
    {

        dashLine.append("----");
        for (int loop = 0; loop != (currCols / 2); ++loop)
        {

            dashLine.append("-----");
        }
    }
    else
    {

        dashLine.append("-");
        for (int loop = 0; loop != ((currCols - 1) / 2) + 1; ++loop)
        {

            dashLine.append("-----");
        }
    }
    return dashLine;
}
