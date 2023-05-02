#include "text.h"

using namespace std;

void Text::init(SDL_Renderer* renderer)
{
    font = TTF_OpenFont("font\\minecraft.ttf", 30);

    surface = TTF_RenderText_Solid(font, "Play", color);
    play = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_QueryTexture(play, NULL, NULL, &casualRect.w, &casualRect.h);
    casualRect.x = 640;
    casualRect.y = 140;

    /*surface = TTF_RenderText_Solid(font, "Settings", color);
    settings = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_QueryTexture(settings, NULL, NULL, &settingsRect.w, &settingsRect.h);
    settingsRect.x = 640;
    settingsRect.y = 260;
    */

    surface = TTF_RenderText_Solid(font, "Help", color);
    help = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_QueryTexture(help, NULL, NULL, &helpRect.w, &helpRect.h);
    helpRect.x = 640;
    helpRect.y = 180;

    surface = TTF_RenderText_Solid(font, "Quit", color);
    quit = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_QueryTexture(quit, NULL, NULL, &quitRect.w, &quitRect.h);
    quitRect.x = 640;
    quitRect.y = 220;

    surface = TTF_RenderText_Solid(font, "Use your spacebar to get the bird to fly.", color);
    helper1 = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_QueryTexture(helper1, NULL, NULL, &helperRect1.w, &helperRect1.h);
    helperRect1.x = 20;
    helperRect1.y = 500;

    surface = TTF_RenderText_Solid(font, "Go as far as you can without hitting a pipe!", color);
    helper2 = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_QueryTexture(helper2, NULL, NULL, &helperRect2.w, &helperRect2.h);
    helperRect2.x = 20;
    helperRect2.y = 530;

    surface = TTF_RenderText_Solid(font, "Good luck!", color);
    helper3 = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_QueryTexture(helper3, NULL, NULL, &helperRect3.w, &helperRect3.h);
    helperRect3.x = 20;
    helperRect3.y = 560;
}

void Text::display(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, play, NULL, &casualRect);
    SDL_RenderCopy(renderer, help, NULL, &helpRect);
    SDL_RenderCopy(renderer, quit, NULL, &quitRect);
    //SDL_RenderCopy(renderer, settings, NULL, &settingsRect);
}

void Text::helperDisplay(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, helper1, NULL, &helperRect1);  
    SDL_RenderCopy(renderer, helper2, NULL, &helperRect2);
    SDL_RenderCopy(renderer, helper3, NULL, &helperRect3);
    

    //SDL_DestroyTexture(play);
    //SDL_DestroyTexture(help);
    //SDL_DestroyTexture(quit);
}

void Text::destroy()
{
    TTF_CloseFont(font);
    SDL_DestroyTexture(play);
}
