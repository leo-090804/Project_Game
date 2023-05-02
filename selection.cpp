#include "selection.h"

using namespace std;

void Selection::init(SDL_Renderer* renderer)
{
    loadSprites(surface, texture, renderer, path);
    srcrect = { 0,25,34,24 };
    dstrect = { 600, 140, 34 / 2, 24 / 2 };
    selected = 1;
    delay = 0;
    flapStatus = 2;
    flapReversed = false;
}

void Selection::display(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, texture, &srcrect, &dstrect);
    aniUpdate();
}

void Selection::select(bool up)
{
    if (up == true && selected > 1)
    {
        selected--;
    }
    else if (up == false && selected < 3)
    {
        selected++;
    }

    switch(selected)
    {
    case 1:
        setPosPlay();
        break;
    case 2:
        setPosHelp();
        break;
    case 3:
        setPosQuit();
        break;
    //case 4:
    //    setPosSettings();
    //    break;
    }
}

void Selection::aniUpdate()
{
    delay++;
    if(delay == 15)
    {
        if(flapStatus==1)
        {
            srcrect = { 0,25,34,24 };
            flapStatus = 2;
        }
        else if(flapStatus == 2 && flapReversed == true)
        {
            srcrect = { 35,0,34,24 };
            flapStatus = 1;
            flapReversed = false;
        }
        else if(flapStatus == 2 && flapReversed == false)
        {
            srcrect = { 0,0,34,24 };
            flapStatus = 3;
            flapReversed = true;
        }
        else if (flapStatus == 3)
        {
            srcrect = { 0,0,34,24 };
            flapStatus = 2;
        }
        /*else if (flapStatus == 3 && flapReversed == true)
        {
            srcrect = { 0,25,34,24 };
            flapStatus = 2;
            flapReversed = false;
        }
        else if (flapStatus == 3 && flapReversed == false)
        {
            srcrect = { 0,0,34,24 };
            flapStatus = 4;
            flapReversed = true;
        }
        else if (flapStatus == 4)
        {
            srcrect = { 0,0,34,24 };
            flapStatus = 3;
        }
        */
        delay = 0;
    }
}


void Selection::setPosPlay()
{
    dstrect = { 600, 140, 34 / 2, 24 / 2 };
    selected = 1;
}

void Selection::setPosHelp()
{
    dstrect = { 600, 180, 34 / 2, 24 / 2 };
    selected = 2;
}

void Selection::setPosQuit()
{
    dstrect = { 600, 220, 34 / 2, 24 / 2 };
    selected = 3;
}

void Selection::setPosSettings()
{
    dstrect = { 600, 260, 34 / 2, 24 / 2 };
    selected = 4;
}

void Selection::destroy()
{
    SDL_DestroyTexture(texture);
}
