#include "menu.h"
#include "game.h"


bool Menu::running = false;



void Menu::init(){

    TTF_Init();
    running = true;
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
}//return nut nao dc bam

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

void Menu:: AddTag(const char* path, const char* text,int sz)
{
    tags.push_back(new Object);
    tags.back()->init(path, text,sz);
    tags.back()->SetPos(_x,_y + (tags.size()-1)*(tags.back()->GetDest().h + 10) );
}
