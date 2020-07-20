#include "PlayerAi.h"

void PlayerAi::playAiMove(GameEngine *&engine)
{
    Board *board = engine->board;
    PlayerPtr player = engine->getCurrentPlayer();
    TilePtr tileToPlay = nullptr;
    int coordinatesToPlay[2] = {0,0};
    int maxScore = 0;

    for (int tileIndex = 0; tileIndex < player->deck->size(); ++tileIndex)
    {

        TilePtr tile = player->deck->get(tileIndex);
        for (int row = 0; row < board->getCurrentRows(); ++row)
        {

            for (int col = 0; col < board->getCurrentCols(); ++col)
            {

                try
                {
                    board->isPlayableTile(*tile, row, col);
                    if (maxScore < board->totalReceivablePoints(*tile, row, col))
                    {
                        delete tileToPlay;
                        tileToPlay = new Tile(*tile);
                        coordinatesToPlay[0] = row;
                        coordinatesToPlay[1] = col;
                        maxScore = board->totalReceivablePoints(*tile, row, col);
                    }
                }
                catch (const char *&exception)
                {
                }
            }
        }
        delete tile;
    }

    if (tileToPlay == nullptr)
    {
        TilePtr tileToReplace = player->deck->get(0);
        try
        {

            engine->replaceTile(*tileToReplace);
            std::cout << "\n" << player->getPlayerName() << " replaced a tile" << std::endl;
        }
        catch (const char *&exception)
        {

            delete tileToReplace;
            engine->shiftToNextPlayer();
            std::cout << "\n" << player->getPlayerName() << " had no possible moves" << std::endl;
        }
    }
    else
    {
        int playerScore = board->totalReceivablePoints(*tileToPlay, coordinatesToPlay[0], coordinatesToPlay[1]) + player->getScore();
        player->setScore(playerScore);

        // Placing tile
        board->placeTile(coordinatesToPlay[0], coordinatesToPlay[1], *tileToPlay);
        player->removeTileFromHand(*tileToPlay);
        if (engine->tileBag->size() != 0)
        {

            player->insertDeck(*engine->tileBag->draw());
        }

        engine->shiftToNextPlayer();

        char row = 'A' + coordinatesToPlay[0];
        std::cout << "\n" << player->getPlayerName() << " placed tile " << tileToPlay->toString(false) << " at " << row << coordinatesToPlay[1] << std::endl;
    }
}