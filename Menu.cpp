#include "menu.h"
#include "game.h"


bool Menu::running = false;



void Menu::init(){
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout<<"init\n";
        Game::window = SDL_CreateWindow("Worlds ended", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 480, 640, 0);
        if(Game::window != nullptr)
        {
            std::cout<<"window\n";
            Game::renderer = SDL_CreateRenderer(Game::window, -1, 0);
            if(Game::renderer != nullptr)
            {
                std::cout<<"renderer\n";
                SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
                running = true;
            }
        }

    }
    AddTag("image/Block.png");
}

void Menu::input()
{
    SDL_PollEvent(&Game::e);
    if(Game::e.type == SDL_QUIT)
    {
        running = false;
    }

}

int Menu::update()
{
    int i = 0;
    for(auto& t : tags)
    {
        t->update();
        if(t->GetChosed())return i;
        ++i;
    }
    return -1;
}

void Menu::render()
{
    for(auto& t : tags)
    {
        t->SetChosed(false);
        t->render();
    }

}

void Menu::close()
{
    SDL_DestroyRenderer(Game::renderer);
    SDL_DestroyWindow(Game::window);
    SDL_Quit();
}

void Menu:: AddTag(const char* path)
{
    tags.push_back(new Object);
    //tags.back()->init(path);
   // tags.back()->SetPos(_x,_y + (tags.size()-1)*(tags.back()->GetDest().h + 10) );
}
