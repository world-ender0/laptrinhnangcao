#include "Game.h"
#include "Menu.h"
#include "object.h"

///---static---------------------
SDL_Window* Game:: window = nullptr;
SDL_Renderer* Game:: renderer = nullptr;
SDL_Event Game:: e;
bool Game::running = true;
//------------------------------

Object * block;

void Game:: init()
{

//    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
//    {
//        std::cout<<"init\n";
//        window = SDL_CreateWindow("Worlds ended", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 480, 640, 0);
//        if(window != nullptr)
//        {
//            std::cout<<"window\n";
//            renderer = SDL_CreateRenderer(window, -1, 0);
//            if(renderer != nullptr)
//            {
//                std::cout<<"renderer\n";
//                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
//                running = true;
//            }
//        }
//
//    }
    block = new Object;
    block ->init("image/Block.png");
    block->SetPos(200,100);

}
void Game::input()
{
    SDL_PollEvent(&e);
    if(e.type == SDL_QUIT )
    {
        running = false;
    }
}

void Game::update()
{
    block->update();
}

void Game::render()
{
    SDL_RenderClear(renderer);
    block->render();




    SDL_RenderPresent(renderer);
}

void Game:: close()
{

    delete block;
}
