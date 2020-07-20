#include "Tile.h"

Tile::Tile(Colour colour, Shape shape)
{
    this->colour = colour;
    this->shape = shape;
}

Tile::Tile(Tile &tile)
{
    this->colour = tile.colour;
    this->shape = tile.shape;
}

bool Tile::equals(Tile &tile)
{
    return tile.colour == this->colour && tile.shape == this->shape;
}

bool Tile::compatibleShape(Tile &tile)
{
    return tile.shape == this->shape;
}

bool Tile::compatibleColour(Tile &tile)
{
    return tile.colour == this->colour;
}

std::string Tile::toString(bool colourize)
{
    std::string string;

    if (colourize)
    {
        TileColorDictionary color = TileColorDictionary();
        string.append(color.getColor(colour, shape));
    }
    else
    {
        std::stringstream stringStream;
        stringStream << colour << shape;
        string = stringStream.str();
    }

    return string;
}
