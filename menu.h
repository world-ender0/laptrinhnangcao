#pragma once
#include "object.h"
#include <vector>


class Menu
{
public:

    std::vector<Object* >tags;
    static bool running;
    int _x = 240,_y=320;

    void init();
    void input();
    int update();
    void render();
    void close();

    void AddTag(const char* path);

};
