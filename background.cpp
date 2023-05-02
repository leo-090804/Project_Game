#include "background.h"

using namespace std;

void Background::select(){
    srand(time(NULL));
    int selection = rand() % 7;
    if (selection == 1)
        path = "sprites\\background\\dayBackground.png";
    else if (selection == 2)
        path = "sprites\\background\\cloudyBackground.png";
    else if (selection == 3)
        path = "sprites\\background\\nightBackground.jpg";
    else if (selection == 4)
        path = "sprites\\background\\noonBackground.jpg";
    else if (selection == 5)
        path = "sprites\\background\\beachBackground.jpg";
    else if (selection == 6)
        path = "sprites\\background\\cityBackground.jpg";
}

void Background::init(SDL_Renderer* renderer){
    select();
    loadSprites(surface, texture, renderer, path);
    rect1 = {0,-120,1280,720};
    rect2 = {1280, -120, 1280, 720};
}

void Background::display(SDL_Renderer* renderer, int multiplier){
    SDL_RenderCopy(renderer, texture, NULL, &rect1);
    SDL_RenderCopy(renderer, texture, NULL, &rect2);
    rect1.x -= 4 * multiplier;
    rect2.x -= 4 * multiplier;
    if(rect1.x<-1280 + 6) rect1.x = 1280 - 4 * multiplier;
    if(rect2.x<-1280 + 6) rect2.x = 1280 - 4 * multiplier;
}

void Background::destroy(){
    SDL_DestroyTexture(texture);
}
