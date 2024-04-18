#include "Game.h"
#include "Menu.h"

SDL_Window* Game::window;
SDL_Renderer* Game::renderer;
SDL_Event Game::e;

void Game::create()
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
//    ScoreText->init(NULL,"SCORE : ", 25);
//    ScoreText->SetPos(50,50);
}
void Game:: init()
{
    Walls.clear();
    Foods.clear();
    body.clear();
    for (int i=0; i< grid_width; i++){
        for(int j=0; j< grid_height; j++){
            grid[i][j] = Block::Empty;
        }
    }
    grid[head.x][head.y] = Block::Head;
    TTF_Init();
    font = TTF_OpenFont("fonts/font.ttf", 24);
    running = true;
    alive = true;
    grown = 1;
    Size = 1;
    speed = 0.2;
    score = 0;
    White = {255, 255, 255};
    newfood();
    newfood();
    newfood();
    input();


}
void Game::input()
{
    int FPS = 60;
    int start_frame = 0;
    int delay_time = 0;
    while(running){
        start_frame = SDL_GetTicks();
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT) running = false;
            if(e.type == SDL_KEYDOWN){
                switch(e.key.keysym.sym){
                    case SDLK_w:
                      if(last_dir != Move::down || Size == 1) dir = Move::up;
                      break;
                    case SDLK_s:
                      if(last_dir != Move::up || Size == 1) dir = Move::down;
                      break;
                    case SDLK_a:
                      if(last_dir != Move::right || Size == 1) dir = Move::left;
                      break;
                    case SDLK_d:
                      if(last_dir != Move::left || Size == 1) dir = Move::right;
                      break;
                }
            }
        }

        update();
        render();
        delay_time = 1000/FPS - (SDL_GetTicks() - start_frame);
        if(delay_time > 0)SDL_Delay(delay_time);
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
          score++;
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

    if(head.y%grid_height == (new_y - 1)%grid_height)head_rotate = 1;//down
    if(head.y%grid_height == (new_y + 1)%grid_height)head_rotate = 4;//up

    if(head.x%grid_width == (new_x - 1)%grid_width)head_rotate = 2;//right
    if(head.x%grid_width == (new_x + 1)%grid_width)head_rotate = 3;//left
    head.x = new_x;
    head.y = new_y;

{/** an ta'o--------------------------------------------------------------------**/


    Block &next = grid[head.x][head.y];
    if(next == Block::Food){
        type = buff[head.x][head.y];
        switch(type)
        {
        case 1:
            {
                //score += 10;
                grown ++;
            }
            break;
        case 2:
            {
                //score += 5;
                if(body.size() > 2)
                {
                    grid[body.back().x][body.back().y] = Block::Empty;
                    body.pop_back();
                }
            }
            break;
        default:
            break;
        }

        buff[head.x][head.y] = -1;
        newfood();
        //if(rand()%5 == 0)
            newwall();
    }
    else if(next == Block::Body || next == Block::Wall){
        alive = false;
        running = false;
        SDL_Delay(3000);
        return;
    }
    next = Block::Head;
}
   // ScoreText->SetText(("SCORE : "+std::to_string(score)).c_str(),25);
}

void Game::newwall(){
    int x, y;
    while(1){
        x = rand() % (grid_width);
        y = rand() % (grid_height);
        if(y < 5) continue;

        if(grid[x][y] == Block::Empty){
          grid[x][y] = Block::Wall;
          Game::Walls.push_back({x,y});
          break;
        }
    }
}

void Game::newfood(){
    int x, y;
    while(1){
        x = rand() % (grid_width);
        y = rand() % (grid_height);
        if(y < 5) continue;

        if(grid[x][y] == Block::Empty){
          grid[x][y] = Block::Food;
          if(rand()%100 <= 30)buff[x][y] = 2;
          else buff[x][y] = 1;
          Game::Foods.push_back({x,y});
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

    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, ("score : " + std::to_string(score)).c_str(), White);
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    SDL_Rect Message_rect; //create a rect
    Message_rect.x = 10;  //controls the rect's x coordinate
    Message_rect.y = 10; // controls the rect's y coordinte
    Message_rect.w = surfaceMessage->w; // controls the width of the rect
    Message_rect.h = surfaceMessage->h; // controls the height of the rect


    SDL_Surface* surface = IMG_Load("image/goldenapple.png");
    SDL_Texture* apple = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    surface = IMG_Load("image/redapple.png");
    SDL_Texture* apple1 = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_Rect block;
    for(auto& f : Game::Foods)
    {
        block = {f.x*20, f.y*20, 20, 20};
        if(buff[f.x][f.y] == 1)SDL_RenderCopy(renderer, apple, NULL, &block);
        else if(buff[f.x][f.y] == 2)SDL_RenderCopy(renderer, apple1, NULL, &block);
    }


    surface = IMG_Load("image/wall.png");
    SDL_Texture* wall = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    for(auto& w : Game::Walls)
    {
        block = {w.x*20, w.y*20, 20, 20};
        SDL_SetTextureColorMod(wall,200,150,150);
        SDL_RenderCopy(renderer, wall, NULL, &block);
    }

    SDL_SetRenderDrawColor(renderer, 0, 191, 255, 255);
    block = {head.x*20, head.y*20, 20, 20};

    SDL_Surface* surface1 = IMG_Load("image/body1.png");
    SDL_Surface* surface2 = IMG_Load("image/body2.png");
    SDL_Texture* texture1 = SDL_CreateTextureFromSurface(renderer, surface1);
    SDL_Texture* texture2 = SDL_CreateTextureFromSurface(renderer, surface2);
    SDL_FreeSurface(surface1);
    SDL_FreeSurface(surface2);
    SDL_Surface* surface3 = IMG_Load("image/body3.png");
    SDL_Surface* surface4 = IMG_Load("image/head.png");
    SDL_Texture* texture3 = SDL_CreateTextureFromSurface(renderer, surface3);
    SDL_Texture* texture4 = SDL_CreateTextureFromSurface(renderer, surface4);
    SDL_FreeSurface(surface3);
    SDL_FreeSurface(surface4);
    if(head_rotate == 4)SDL_RenderCopyEx(renderer,texture4, NULL,&block ,NULL,NULL,SDL_FLIP_NONE);
    if(head_rotate == 1)SDL_RenderCopyEx(renderer,texture4, NULL,&block ,NULL,NULL,SDL_FLIP_VERTICAL);
    if(head_rotate == 3)SDL_RenderCopyEx(renderer,texture4, NULL,&block ,-90,NULL,SDL_FLIP_NONE);
    if(head_rotate == 2)SDL_RenderCopyEx(renderer,texture4, NULL,&block ,90,NULL,SDL_FLIP_NONE);

    for (int i=0; i< body.size(); i++){
        double ang = 0;
        SDL_RendererFlip flip1 = SDL_FLIP_HORIZONTAL;
        SDL_RendererFlip flip2 = SDL_FLIP_NONE;
        SDL_Texture* Tex = texture1;
        SDL_Point prev;
        SDL_Point suf;
        if(i == 0) prev = head;
        else prev = body[i-1];

        if(prev.y%grid_height == (body[i].y + 1)%grid_height )ang = 0;
        if(prev.y%grid_height == (body[i].y - 1 + grid_height)%grid_height )ang = 180;
        if(prev.x%grid_width == (body[i].x + 1)%grid_width)ang = -90;
        if(prev.x%grid_width == (body[i].x - 1 + grid_width)%grid_width)ang = 90;


        if(i+1 < body.size())
        {
            suf = body[i+1];

            if( prev.y%grid_height == (body[i].y + 1)%grid_height && suf.x == (body[i].x + 1)%grid_width){Tex = texture2; ang = -90;flip1 = flip2= SDL_FLIP_NONE;}
            else if( suf.y == (body[i].y + 1)%grid_height && prev.x == (body[i].x + 1)%grid_width){Tex = texture2; ang = -90;flip1 = flip2= SDL_FLIP_NONE;}
            else if( prev.y == (body[i].y - 1 + grid_height)%grid_height && suf.x == (body[i].x + 1)%grid_width){Tex = texture2;ang = 180; flip1 = flip2 = SDL_FLIP_NONE;}
            else if( suf.y == (body[i].y - 1 + grid_height)%grid_height && prev.x == (body[i].x + 1)%grid_width){Tex = texture2;ang = 180; flip1 = flip2 = SDL_FLIP_NONE;}
            else if( prev.y == (body[i].y + 1) %grid_height && suf.x == (body[i].x - 1 +grid_width)%grid_width){Tex = texture2;ang = 0; flip1 = flip2 = SDL_FLIP_NONE;}
            else if( suf.y == (body[i].y + 1) %grid_height && prev.x == (body[i].x - 1+grid_width)%grid_width){Tex = texture2;ang = 0; flip1 = flip2 = SDL_FLIP_NONE;}
            else if( prev.y == (body[i].y - 1 + grid_height)%grid_height && suf.x == (body[i].x - 1+grid_width)%grid_width){Tex = texture2; ang = 90;flip1 = flip2= SDL_FLIP_NONE;}
            else if( suf.y == (body[i].y - 1 + grid_height)%grid_height && prev.x == (body[i].x - 1+grid_width)%grid_width){Tex = texture2; ang = 90;flip1 = flip2= SDL_FLIP_NONE;}

        }
        else Tex = texture3;

        block = {body[i].x*20, body[i].y*20, 20, 20};

        if ((block.x/20 + block.y/20)%2==0) SDL_RenderCopyEx(renderer, Tex, NULL, &block,ang,NULL,flip1);
        else SDL_RenderCopyEx(renderer, Tex, NULL, &block,ang,NULL,flip2);
//        SDL_RenderFillRect(renderer, &block);
    }
    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);
    SDL_RenderPresent(renderer);
}
