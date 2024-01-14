#ifndef SPRITE_H
#define SPRITE_H

const int FRAME_DELAY =70;
class Sprite{
   SDL_Texture* texture;
   int width, height;
   int numOfFrame;
   int clipNum;
public:
   Sprite(SDL_Texture* tex, int _frame =1):
   texture(tex),
   numOfFrame(_frame)
   {
      clipNum =0;
      SDL_QueryTexture(texture, NULL, NULL, &width, &height);
   }
   void drawAtCenter(SDL_Renderer* renderer, SDL_Rect src)
   {
      int xoffset =(SCREEN_WIDTH -src.w) /2;
      int yoffset =(SCREEN_HEIGHT -src.h) /2;
      SDL_Rect dst ={xoffset, yoffset, src.w, src.h};
      SDL_RenderCopy(renderer, texture, &src, &dst);
      SDL_RenderPresent(renderer);
   }
   void drawAnimation(SDL_Renderer* renderer, int timer)
   {
      while (timer >0)
      for (int i =0; i <numOfFrame; i++)
      {
         int size =width /numOfFrame;
         SDL_Rect src ={size *i, 0, size, height};
         drawAtCenter(renderer, src);
         SDL_Delay(FRAME_DELAY);
         timer -=FRAME_DELAY;
      }
   }
   void setClip(int clip) { clipNum =clip; }
   void drawClip(SDL_Renderer* renderer, int x =0, int y =0)
   {
      int size =width /numOfFrame;
      SDL_Rect src ={size *clipNum, 0, size, height};
      drawAtCenter(renderer, src);
   }
};

#endif // SPRITE_H
