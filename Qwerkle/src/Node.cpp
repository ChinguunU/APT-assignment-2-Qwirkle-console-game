/*                             */
/* DO NOT CHANGE ANY CODE HERE */
/*                             */

#include "Node.h"

Node::Node(TilePtr tile, Node *next, Node *prev)
{
   this->tile = tile;
   this->next = next;
   this->prev = prev;
}

Node::Node(Node &other)
{
   this->tile = new Tile(*other.tile);
   this->next = other.next;
   this->prev = other.prev;
}

Node::~Node()
{
   delete tile;
}
