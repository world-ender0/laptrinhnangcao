#include "object.h"
#include "TextureManager.h"
#include "Game.h"


 Object::   Object()
 {

 }
 Object::   ~Object()
 {

 }


void Object::init(const char* path)
{
    SetTex(path);
    dest = src;

}
void Object::update(){
    //cap nhat xem object nay da duoc
    if(Game::e.type == SDL_MOUSEMOTION)
    {
        int x = Game::e.motion.x;
        int y = Game::e.motion.y;
        if(Collision(dest, {x,y,1,1})  )
        {
            touch = true;
        }
        else touch = false;
    }

    if(Game::e.type == SDL_MOUSEBUTTONDOWN)
    {
        if(touch)
        {
            isChosed = true;
        }
    }

}
void Object::render(){
    TextureManager::DrawImage(tex, src, dest);
}


SDL_Rect Object::GetSrc(){
    return src;
}
SDL_Rect Object::GetDest(){
    return dest;
}
SDL_Texture* Object::GetTex(){
    return tex;
}

void Object::SetSrc(SDL_Rect sr){
    src = sr;
}
void Object::SetDest(SDL_Rect de){
    dest = de;
}
void Object::SetTex(const char* path){

    tex = TextureManager::LoadImage(path,src);

}

void Object:: SetPos(int x,int y)
{
    dest.x = x - dest.w/2;
    dest.y = y - dest.h/2;
}

void Object:: SetChosed(bool x)
{
    isChosed = x;
}

bool Object:: Collision(SDL_Rect A, SDL_Rect B)
{
    return !(
             B.x > A.x + A.w ||
             B.y > A.y + A.h ||
             A.x > B.x + B.w ||
             A.y > B.y + B.h
             );
}

bool Object:: GetChosed()
{
    return isChosed;
}
