#include "LinkedList.h"

LinkedList::LinkedList()
{
   head = nullptr;
   tail = nullptr;
   length = 0;
}

LinkedList::~LinkedList()
{
   clear();
}

int LinkedList::size()
{
   return length;
}

void LinkedList::clear()
{
   Node *tmp;
   while (head != nullptr)
   {
      tmp = head;
      head = head->next;
      delete tmp;
   }
}

TilePtr LinkedList::get(int i)
{
   TilePtr tile = nullptr;
   if (i >= 0 && i < length)
   {

      Node *currentNode = head;
      int count = 0;
      while (count != i)
      {

         currentNode = currentNode->next;
         count++;
      }

      tile = new Tile(*currentNode->tile);
   }
   else
   {

      throw std::runtime_error("Invalid index: Beyond boundaries");
   }

   return tile;
}

void LinkedList::remove(int i)
{
   if (i >= 0 && i < length)
   {

      Node *currentNode = head;
      int count = 0;
      while (count != i)
      {

         currentNode = currentNode->next;
         count++;
      }

      if (currentNode == tail)
      {

         deleteBack();
      }
      else if (currentNode == head)
      {

         deleteFront();
      }
      else
      {

         currentNode->prev->next = currentNode->next;
         currentNode->next->prev = currentNode->prev;
         delete currentNode;
         length--;
      }
   }
   else
   {

      throw std::runtime_error("Invalid index: Beyond boundaries");
   }
}

void LinkedList::addBack(Tile &tile)
{
   Node *newNode = new Node(&tile, nullptr, tail);
   if (tail == nullptr)
   {

      head = newNode;
   }
   else
   {

      tail->next = newNode;
   }
   tail = newNode;
   length++;
}

void LinkedList::deleteFront()
{
   deleteFromEitherEnd(head);
}

void LinkedList::deleteBack()
{
   deleteFromEitherEnd(tail);
}

void LinkedList::remove(Tile &tile)
{
   Node *currentNode = head;
   bool removed = false;
   int count = 0;
   while (currentNode != nullptr && !removed)
   {

      if (tile.equals(*currentNode->tile))
      {

         remove(count);
         removed = true;
      }
      currentNode = currentNode->next;
      count++;
   }
}

void LinkedList::deleteFromEitherEnd(Node *headOrTail)
{
   if (headOrTail != nullptr && length != 0)
   {

      if (head == tail && length == 1)
      {

         delete tail;
         head = nullptr;
         tail = nullptr;
      }
      else
      {

         Node *tmp = headOrTail;
         if (headOrTail == tail)
         {

            tail = tail->prev;
            tail->next = nullptr;
         }
         else if (headOrTail == head)
         {

            head = head->next;
            head->prev = nullptr;
         }
         delete tmp;
      }
      length--;
   }
}

std::string LinkedList::toString(bool colourize)
{
   std::string listString = "";
   Node *currentNode = head;
   while (currentNode != nullptr)
   {
      listString.append(currentNode->tile->toString(colourize));
      if (currentNode != tail)
      {
         listString.append(",");
      }
      currentNode = currentNode->next;
   }

   return listString;
}