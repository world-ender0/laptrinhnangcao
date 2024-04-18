#pragma once
#include <SDL.h>
#include<bits/stdc++.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include "object.h"

using namespace std;

class Game
{
public:

    static SDL_Window* window;
    static SDL_Renderer* renderer;
    static SDL_Event e;
    TTF_Font* font;
    SDL_Color White ;
    bool running = true;

    int head_rotate = 1;

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
        Wall,
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
    int type = 0;
    int maxType = 2;
    int buff[grid_width][grid_height]={};
    vector<SDL_Point>Walls;
    vector<SDL_Point>Foods;

    deque<SDL_Point> body;
    Object* ScoreText = new Object;

    bool alive = true;

    double speed = 0.2;
    int grown = 1;
    int Size = 1;
    int score = 0;

    void newfood();
    void newwall();

    void init();
    void create();
    void input();
    void update();
    void render();
    void close();

};
