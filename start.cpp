/*#include <SDL.h>
#include <bits/stdc++.h>

using namespace std;

//screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main( int argc, char* args[] ){
    //the window i'll be rendering to
    SDL_Window* window = NULL;

    //the surface cotained by the window
    SDL_Surface* screenSurface = NULL;

    //initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO )<0){
        cout<<"SDL could not initialize"<<SDL_GetError();
    }
    else{
        //create window
        window = SDL_CreateWindow( "SDL Tutorial ", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL){
            cout<<"Window could not be created! SDL_Error"<<SDL_GetError();
        }
        else{
            //Get window surface
            screenSurface = SDL_GetWindowSurface( window );

            //Fill the surface white
            SDL_FillRect(screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF));

            //Update the surface
            SDL_UpdateWindowSurface( window );

            //Hack to get window to stay up
            SDL_Event e; bool quit = false; while( quit == false){ while(SDL_PollEvent( &e)){if(e.type == SDL_QUIT) quit = true;}}
        }
    }
    //destroy window
    SDL_DestroyWindow( window );

    //Quit SDL subsystems
    SDL_Quit();

    return 0;
}*/
