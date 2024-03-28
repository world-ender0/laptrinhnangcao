#pragma once
#include<SDL.h>
#include<SDL_ttf.h>

class TextureManager
{
public:
    static TTF_Font* font;
    static SDL_Color color ;
    static SDL_Texture* LoadImage(const char* path);
    static SDL_Texture* LoadImage(const char* path, SDL_Rect & src);
    static SDL_Texture* LoadText(const char* path, SDL_Rect & src, int sz = 15);

    static void DrawImage(SDL_Texture* texture,SDL_Rect src,SDL_Rect dest);
    static void SetFont(int sz);

};
