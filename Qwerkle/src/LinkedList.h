#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"

#include <iostream>

class LinkedList
{
public:
    LinkedList();
    ~LinkedList();
    int size();
    void clear();

    // Returns a copy of the tile at index i
    TilePtr get(int i);
    void remove(int i);

    // For clarificationyou front is the Head an back is the Tail
    void addBack(Tile &tile);
    void deleteFront();
    void deleteBack();

    // Removes the first occurence of the tile
    void remove(Tile &tile);
    std::string toString(bool colourize);

private:
    Node *head;
    Node *tail;
    int length;

    void deleteFromEitherEnd(Node *headOrTail);
};
typedef LinkedList *List;

#endif // ASSIGN2_LINKEDLIST_H
