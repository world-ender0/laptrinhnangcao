#include "Game.h"
#include "Menu.h"


Game* game;
Menu* menu;


int main(int argc, char*argv[])
{
    menu= new Menu;
    menu->init();
    int FPS = 10;
    int timer = 1000/FPS;
    int last, recent;
    while(Menu::running)
    {
        menu->input();
        menu->update();
        switch(menu->update())
        {
        case 0:
        {
            game->init();
            while(game->running)
            {
                last = SDL_GetTicks();
                game->input();
                game->update();
                game->render();
                recent = SDL_GetTicks();


                if(timer > (last - recent))
                {
                    SDL_Delay( timer - (last - recent) );
                }
            }
            game->close();
        }

            break;
        default:
            break;
        }
        menu->render();


    }
    menu->close();

    return 0;
}

