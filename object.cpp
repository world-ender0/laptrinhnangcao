//#include "object.h"
//#include "TextureManager.h"
//#include "Game.h"
//
//
//Object::   Object()
//{
//
//}
//Object::   ~Object()
//{
//
//}
//
//
//void Object::init(const char* path, const char* Text, int sz)
//{
//    if(path != NULL)SetImg(path);
//    if(Text != NULL)SetText(Text,sz);
//
//}
//void Object::update(){
//    if(img!= nullptr)
//    {
//        dest.x = xPos - dest.w/2;
//        dest.y = yPos - dest.h/2;
//    }
//    if(text!=nullptr)
//    {
//        tdest.x = xPos - tdest.w/2;
//        tdest.y = yPos - tdest.h/2;
//    }
//    if(img == nullptr)return;
//    //cap nhat xem object nay da duoc
//    if(Game::e.type == SDL_MOUSEMOTION)
//    {
//        int x = Game::e.motion.x;
//        int y = Game::e.motion.y;
//        if(Collision(dest, {x,y,1,1})  )
//        {
//            touch = true;
//        }
//        else touch = false;
//    }
//
//    if(Game::e.type == SDL_MOUSEBUTTONDOWN)
//    {
//        if(touch)
//        {
//            isChosed = true;
//        }
//    }
//
//}
//
//void Object::render(){
//    if(img!=nullptr)TextureManager::DrawImage(img, src, dest);
//    if(text!=nullptr)
//    {
//       // std::cout<<tdest.x<<' '<<tdest.y<<' '<<tdest.w<<' '<<tdest.h<<'\n';
//        TextureManager::DrawImage(text, tsrc, tdest);
//    }
//}
//
//SDL_Rect Object::GetSrc(){
//    return src;
//}
//
//SDL_Rect Object::GetDest(){
//    return dest;
//}
//
//
//
//void Object::SetSrc(SDL_Rect sr){
//    src = sr;
//}
//
//void Object::SetDest(SDL_Rect de){
//    dest = de;
//}
//
//void Object::SetImg(const char* path){
//    if(path == NULL)
//    {
//        img = nullptr;
//        return;
//    }
//    img = TextureManager::LoadImage(path,src);
//    dest = src;
//
//}
//
//void Object::SetText(const char* path, int sz)
//{
//    if(path == NULL)
//    {
//        text = nullptr;
//        return;
//    }
//    text = TextureManager::LoadText(path,tsrc,sz);
//    tdest = tsrc;
//
//}
//
//void Object:: SetPos(int x,int y)
//{
//    xPos = x;
//    yPos = y;
//}
//
//void Object:: SetChosed(bool x)
//{
//    isChosed = x;
//}
//
//bool Object:: Collision(SDL_Rect A, SDL_Rect B)
//{
//    return !(
//             B.x > A.x + A.w ||
//             B.y > A.y + A.h ||
//             A.x > B.x + B.w ||
//             A.y > B.y + B.h
//             );
//}
//
//bool Object:: GetChosed()
//{
//    return isChosed;
//}
