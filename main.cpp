#include "Game.h"


Game* game;


int main(int argc, char*argv[])
{
    game = new Game;
    game->init();

    return 0;
}

