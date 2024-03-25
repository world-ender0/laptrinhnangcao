
#pragma once
#include <SDL.h>

class Object
{

public:
        SDL_Rect src,dest;
    SDL_Texture* tex;
    bool isChosed = false;
    bool touch = false;

    Object();
    ~Object();
    void init(const char* path);
    void update();
    void render();


    SDL_Rect GetSrc();
    SDL_Rect GetDest();
    SDL_Texture* GetTex();

    void SetSrc(SDL_Rect sr);
    void SetDest(SDL_Rect de);
    void SetTex(const char* path);
    void SetPos(int x,int y);
    void SetChosed(bool x);

    bool Collision(SDL_Rect A, SDL_Rect B);
    bool GetChosed();

};
