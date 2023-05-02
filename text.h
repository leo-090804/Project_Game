#ifndef TEXT_H
#define TEXT_H

#include "sdl_engine.h"

using namespace std;

class Text
{
public:
    void init(SDL_Renderer* renderer);
    void display(SDL_Renderer* renderer);
    void helperDisplay(SDL_Renderer* renderer);
    void destroy();

    SDL_Rect casualRect, settingsRect, helpRect, quitRect, helperRect1, helperRect2, helperRect3;
private:
    TTF_Font* font = NULL;

    SDL_Color color = { 255,255,255 };
    
    SDL_Surface *surface = NULL;
    SDL_Texture *play = NULL;
    //SDL_Texture *settings = NULL;
    SDL_Texture *help = NULL;
    SDL_Texture *quit = NULL;
    SDL_Texture *helper1 = NULL;
    SDL_Texture *helper2 = NULL;
    SDL_Texture *helper3 = NULL;
};

#endif // TEXT_H

