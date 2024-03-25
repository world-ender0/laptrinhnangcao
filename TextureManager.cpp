#include "TextureManager.h"
#include<SDL_image.h>
#include "Game.h"

SDL_Texture* TextureManager:: LoadImage(const char* path)
{
    SDL_Surface* surface = IMG_Load(path);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
    SDL_FreeSurface(surface);
    return texture;

}


SDL_Texture* TextureManager:: LoadImage(const char* path, SDL_Rect& src)
{
    SDL_Surface* surface = IMG_Load(path);
    src.w = surface->w;
    src.h = surface->h;
    src.x = src.y =0;
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
    SDL_FreeSurface(surface);
    return texture;

}

void TextureManager:: DrawImage(SDL_Texture* texture,SDL_Rect src,SDL_Rect dest){
    SDL_RenderCopy(Game::renderer, texture, &src, &dest);
}
