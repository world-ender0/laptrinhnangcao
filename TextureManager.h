#pragma once
#include<SDL.h>

class TextureManager
{
public:
    static SDL_Texture* LoadImage(const char* path);
    static SDL_Texture* LoadImage(const char* path, SDL_Rect & src);
    static void DrawImage(SDL_Texture* texture,SDL_Rect src,SDL_Rect dest);
};
