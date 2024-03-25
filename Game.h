#pragma once
#include <SDL.h>
#include <iostream>
#include "TextureManager.h"


class Game
{
public:

    static SDL_Window* window;
    static SDL_Renderer* renderer;
    static SDL_Event e;
    static bool running;

    void init();
    void input();
    void update();
    void render();
    void close();

};
