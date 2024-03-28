
#pragma once
#include <SDL.h>

class Object
{

public:
    SDL_Rect src,dest,tsrc,tdest;
    SDL_Texture* img = nullptr;
    SDL_Texture* text = nullptr;
    bool isChosed = false;
    bool touch = false;
    int xPos, yPos;

    Object();
    ~Object();
    void init(const char* path, const char* Text = NULL, int sz =12);
    void update();
    void render();


    SDL_Rect GetSrc();
    SDL_Rect GetDest();

    void SetSrc(SDL_Rect sr);
    void SetDest(SDL_Rect de);
    void SetImg(const char* path);
    void SetText(const char* path, int sz);

    void SetPos(int x,int y);
    void SetChosed(bool x);

    bool Collision(SDL_Rect A, SDL_Rect B);
    bool GetChosed();

};
