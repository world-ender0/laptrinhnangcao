#include "Game.h"
#include "Menu.h"
#include "object.h"


void Game:: init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "failed" << '\n';
        return;
    }
    if (!SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl")) {
        std::cerr << "Warning: Could not set render driver hint!" << std::endl;
    }
    window = SDL_CreateWindow("SnakeGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_width, screen_height, SDL_WINDOW_SHOWN);
    if (window==nullptr) cout<<"-1";
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    srand(time(0));
//    cout<<1;
    for (int i=0; i< grid_width; i++){
        for(int j=0; j< grid_height; j++){
            grid[i][j] = Block::Empty;
        }
    }
    grid[head.x][head.y] = Block::Head;
    newfood();
    input();

}
void Game::input()
{
    while(running){
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT) running = false;
            if(e.type == SDL_KEYDOWN){
                switch(e.key.keysym.sym){
                    case SDLK_UP:
                      if(last_dir != Move::down || Size == 1) dir = Move::up;
                      break;
                    case SDLK_DOWN:
                      if(last_dir != Move::up || Size == 1) dir = Move::down;
                      break;
                    case SDLK_LEFT:
                      if(last_dir != Move::right || Size == 1) dir = Move::left;
                      break;
                    case SDLK_RIGHT:
                      if(last_dir != Move::left || Size == 1) dir = Move::right;
                      break;
                }
            }
        }
        update();
        render();
    }
}

void Game::update()
{
    if(alive==false) return;
//    SDL_Delay(1000);
//    cout << head.x << " " << head.y << '\n';
    switch(dir){
        case Move::up:
          pos.y -= speed;
          break;
        case Move::down:
          pos.y += speed;
          break;
        case Move::left:
          pos.x -= speed;
          break;
        case Move::right:
          pos.x += speed;
          break;
    }
    int new_x = pos.x;
    int new_y = pos.y;
    if(new_x < 0) pos.x = grid_width - 1;
    else if(new_x > grid_width - 1) pos.x = 0;

    if(new_y < 0) pos.y = grid_height - 1;
    else if(new_y > grid_height - 1) pos.y = 0;
    new_x = pos.x;
    new_y = pos.y;
    if(new_x != head.x || new_y != head.y){
        last_dir = dir;
        if(grown > 0){
          Size++;
          body.push_front(head);
          grown--;
          grid[head.x][head.y] = Block::Body;
        }
        else{
          body.push_front(head);
          grid[body.back().x][body.back().y] = Block::Empty;
          body.pop_back();
          for(int i = 0; i < (int)body.size(); ++i){
            SDL_Point free = body[i];
            grid[free.x][free.y] = Block::Body;
            free = body[i];
          }
        }
    }
    head.x = new_x;
    head.y = new_y;
    Block &next = grid[head.x][head.y];
    if(next == Block::Food){
        grown ++;
        newfood();
    }
    else if(next == Block::Body){
        alive = false;
        running = false;
        return;
    }
    next = Block::Head;
}


void Game::newfood(){
    int x, y;
    while(1){
        x = rand() % (grid_width);
        y = rand() % (grid_height);
        if(y < 5) continue;

        if(grid[x][y] == Block::Empty){
          grid[x][y] = Block::Food;
          food.x = x;
          food.y = y;
          break;
        }
    }
}

void Game::render()
{

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    for (int i=0; i<grid_width; i++){
        for (int j=0; j<grid_height; j++){
            if ((i+j)%2==0){
                SDL_SetRenderDrawColor(renderer, 162, 209, 73, 255);
                SDL_Rect y = {i*20, j*20, 20, 20};
                SDL_RenderFillRect(renderer, &y);
            }
            else{
                SDL_SetRenderDrawColor(renderer, 170, 215, 81, 255);
                SDL_Rect y = {i*20, j*20, 20, 20};
                SDL_RenderFillRect(renderer, &y);
            }
        }
    }

    SDL_Surface* surface = IMG_Load("image/goldenapple.png");
    SDL_Texture* apple = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_Rect block = {food.x*20, food.y*20, 20, 20};
    SDL_RenderCopy(renderer, apple, NULL, &block);

    SDL_SetRenderDrawColor(renderer, 0, 191, 255, 255);
    block = {head.x*20, head.y*20, 20, 20};
    SDL_RenderFillRect(renderer, &block);

    for (auto t : body){
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        block = {t.x*20, t.y*20, 20, 20};
        SDL_RenderFillRect(renderer, &block);
    }
    SDL_RenderPresent(renderer);
}
