#include "Utilities.h"

TilePtr Utilities::getTile(std::string &tile)
{
    Colour colour = tile.c_str()[TILE_COLOUR_INDEX];
    Shape shape;

    std::string sShape(&tile[TILE_SHAPE_INDEX]);
    shape = std::stoi(sShape);

    return new Tile(colour, shape);
}

std::vector<int> Utilities::getCoordinates(std::string &coordinates)
{
    char cRow = coordinates[COORDINATES_ROW_INDEX];
    int row = cRow - 'A';
    int col;

    std::string sCol(&coordinates[COORDINATES_COL_INDEX]);
    col = std::stoi(sCol);

    std::vector<int> coordinatesCont{row, col};

    return coordinatesCont;
}

std::vector<std::string> Utilities::split(std::string &stringToSplit, char regex)
{

    std::stringstream stringStream(stringToSplit);
    std::string token;
    std::vector<std::string> container;
    while (std::getline(stringStream, token, regex))
    {
        container.push_back(token);
    }

    return container;
}

List Utilities::getTiles(std::vector<std::string> tiles)
{

    List tileList = new LinkedList();

    for (unsigned int loop = 0; loop < tiles.size(); ++loop)
    {

        tileList->addBack(*getTile(tiles[loop]));
    }

    return tileList;
}