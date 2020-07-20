#include "QwirkleRunner.h"

#define EXIT_SUCCESS 0

int main(void)
{

   QwirkleRunner *game = new QwirkleRunner();
   game->runQwirkle();
   delete game;

   return EXIT_SUCCESS;
}
