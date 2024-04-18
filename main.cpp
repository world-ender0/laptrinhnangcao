#include "Game.h"
#include "menu.h"

Game* game;
Menu* menu;

int main(int argc, char*argv[])
{
    game = new Game;
    menu = new Menu;
    game->create();

    menu->init();
    menu->AddTag("image/Block.png","Start",15);
    menu->tags.back()->SetPos(game->screen_width/2, game->screen_height/2);
    menu->AddTag("image/Block.png","Exit",15);
    menu->tags.back()->SetPos(game->screen_width/2, game->screen_height/2+100);

    while(menu->running)
    {
        menu->input();
        switch(menu->update())
        {
        case 0:
            game->init();
            break;
        case 1:
            menu->running = false;
            break;
        default:
            break;
        }
        SDL_SetRenderDrawColor(Game::renderer,255,255,255,255);
        SDL_RenderClear(Game::renderer);
        menu->render();
        SDL_RenderPresent(Game::renderer);

    }
    menu->close();

    return 0;
}

