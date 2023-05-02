#ifndef SELECTION_H
#define SELECTION_H

#include "sdl_engine.h"

using namespace std;

class Selection
{
public:
    void init(SDL_Renderer* renderer);
    void display(SDL_Renderer* renderer);
    void select(bool up);
    void aniUpdate();
    void setPosPlay();
    void setPosHelp();
    void setPosQuit();
    void setPosSettings();
    void destroy();

    int selected = 1;
private:
    SDL_Surface *surface = NULL;
    SDL_Texture *texture = NULL;
    SDL_Rect srcrect;
    SDL_Rect dstrect;
    int delay = 0;
    int flapStatus = 2;
    bool flapReversed = false;
    const char* path = "sprites\\bird\\yellowbird.png";
};

#endif // SELECTION_H
