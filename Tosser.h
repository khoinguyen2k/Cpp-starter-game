#ifndef TOSSER_H
#define TOSSER_H
#include <cmath>
#include "Sprite.h"
enum CoinState {HEAD =0, TAIL};
enum TosserState {QUIT =0, QUEUE, RESET};
class Tosser{
   CoinState coinState;
   TosserState tosserState;
   Sprite coinStateSprite, coinFaceSprite;
   SDL_Renderer* renderer;
public:
   Tosser(SDL_Renderer* ren):
   coinState(HEAD),
   tosserState(QUEUE),
   coinStateSprite(loadTexture("images/coin state.png", ren), 9),
   coinFaceSprite(loadTexture("images/coin face.png", ren), 2),
   renderer(ren)
   {}

   bool isRunning() {return (tosserState !=QUIT);}
   void listen(SDL_Event event)
   {
      if (event.type ==SDL_QUIT) tosserState =QUIT;
      if (event.type ==SDL_KEYDOWN)
         switch (event.key.keysym.sym)
         {
            case SDLK_q: tosserState =QUIT; break;
            case SDLK_r: tosserState =RESET; break;
            default: break;
         }
   }
   void toss()
   {
      int val =rand() %2;
      if (val ==0) coinState =HEAD;
      else coinState =TAIL;
   }
   void update()
   {
      if (tosserState ==RESET)
         toss();
   }
   void render()
   {
      SDL_RenderClear(renderer);
      if (tosserState ==RESET)
      {
         coinStateSprite.drawAnimation(renderer, 1000);
         tosserState =QUEUE;
      }
      else if (tosserState ==QUEUE)
      {
         coinFaceSprite.setClip(coinState);
         coinFaceSprite.drawClip(renderer);
      }
   }
   TosserState getState() {return tosserState;}
};
#endif // TOSSER_H
