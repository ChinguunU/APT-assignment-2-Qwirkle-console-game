
#ifndef ASSIGN2_NODE_H
#define ASSIGN2_NODE_H

#include "Tile.h"

/*                             */
/* DO NOT CHANGE ANY CODE HERE */
/*                             */

class Node
{
public:
   Node(TilePtr tile, Node *next, Node *prev);
   Node(Node &other);
   ~Node();

   TilePtr tile;
   Node *next;
   Node *prev;
};

#endif // ASSIGN2_NODE_H
