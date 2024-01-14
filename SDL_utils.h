#ifndef SDL_UTILS_H
#define SDL_UTILS_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
using namespace std;
const int SCREEN_WIDTH =640;
const int SCREEN_HEIGHT =480;
const string WINDOW_TITLE ="Flip Coin!";

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer,
             const int &SCREEN_WIDTH, const int &SCREEN_HEIGHT, const string &WINDOW_TITLE);
void logSDLError(ostream& os, const string &msg, bool fatal =false);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void waitUntilKeyPressed();
//SDL_image
SDL_Texture* loadTexture(string path, SDL_Renderer* renderer);

void logSDLError(ostream& os, const string &msg, bool fatal)
{
    os <<msg <<" Error: " <<SDL_GetError() <<endl;
    if (fatal)
    {
        SDL_Quit();
        exit(1);
    }
}
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer,
             const int &SCREEN_WIDTH, const int &SCREEN_HEIGHT, const string &WINDOW_TITLE)
{
    if (SDL_Init(SDL_INIT_EVERYTHING !=0))
        logSDLError(std::cout, "SDL_Init", true);
    window =SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
                             SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    //test at home
    if (window ==nullptr) logSDLError(std::cout, "CreateWindow", true);
    renderer =SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                 SDL_RENDERER_PRESENTVSYNC);
}
void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true)
    {
        if (SDL_WaitEvent(&e) !=0 &&
                (e.type ==SDL_KEYDOWN || e.type ==SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}

// SDL_image
SDL_Texture* loadTexture(string path, SDL_Renderer* renderer)
{
    SDL_Texture* newTexture =nullptr;
    SDL_Surface* loadedSurface =IMG_Load(path.c_str() );
    if (loadedSurface ==nullptr)
        cout <<"Unable to load image " <<path <<" SDL_image Error: "
             <<IMG_GetError() <<endl;
    else
    {
        newTexture =SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture ==nullptr)
            cout <<"Unable to create texture from " <<path <<" SDL Error: "
                 <<SDL_GetError() <<endl;
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}

//modifed
SDL_Rect IntRect(int a, int b, int c, int d)
{
   SDL_Rect ans ={a, b, c, d};
   return ans;
}
#endif // SDL_utils.h
