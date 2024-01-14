#include <iostream>
#include <ctime>
#include "SDL_utils.h"
#include "Tosser.h"
using namespace std;

int main(int argc, char* argv[])
{
   srand(time(0));
   SDL_Window* window;
   SDL_Renderer* renderer;
   initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);

   Tosser tosser(renderer);
   tosser.render();
   do
   {
      SDL_Event event;
      while (SDL_PollEvent(&event))
      {
         tosser.listen(event);
      }
      tosser.update();
      tosser.render();
      SDL_Delay(1);
   }
   while (tosser.isRunning());

   quitSDL(window, renderer);
   return 0;
}
