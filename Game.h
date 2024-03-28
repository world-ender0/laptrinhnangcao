#pragma once
#include <SDL.h>
#include<bits/stdc++.h>
#include<SDL_image.h>

using namespace std;

class Game
{
public:

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event e;
    bool running = true;

    static const int screen_width = 500;
    static const int screen_height = 500;
    static const int grid_width = 25;
    static const int grid_height = 25;

    struct {
     double x = (grid_width/2);
     double y = (grid_height/2);
    }pos;

    enum class Block{
        Head,
        Body,
        Food,
        Empty
    };
    Block grid[grid_width][grid_height];

    enum class Move{
        up,
        down,
        left,
        right
    };
    Move dir = Move::up;
    Move last_dir = Move::up;
    SDL_Point head = {pos.x, pos.y};
    SDL_Point food;

    deque<SDL_Point> body;

    bool alive = true;

    double speed = 0.2;
    int grown = 0;
    int Size = 1;

    void newfood();

    void init();
    void input();
    void update();
    void render();
    void close();

};
