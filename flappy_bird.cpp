#include "flappy_bird.h"

using namespace std;

void FlappyBird::init()
{
    initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    bird.loadPNG(renderer);
    background.init(renderer);
    base.init(renderer);
    message.init(renderer);
    flash.init(renderer);
    sfx.init();
    scoreboard.init(renderer);
    text.init(renderer);
    selection.init(renderer);
}

void FlappyBird::quit()
{
    bird.destroy();
    background.destroy();
    base.destroy();
    resDestroy();
    flash.destroy();
    message.destroy();
    sfx.close();
    text.destroy();
    selection.destroy();
    scoreboard.destroy();
    quitSDL(window, renderer);
}

void FlappyBird::reset()
{
    multiplier = 1;
    score = 0;
    gameLose = false;
    gameReset = false;
    menuLoop = true;
    readyLoop = true;
    level2 = false;
    casual = false;
    help = false;

    bird.destroy();
    background.destroy();
    base.destroy();
    resDestroy();
    flash.destroy();
    message.destroy();
    text.destroy();
    scoreboard.destroy();

    bird.loadPNG(renderer);
    background.init(renderer);
    base.init(renderer);
    message.init(renderer);
    flash.init(renderer);
    scoreboard.init(renderer);
    text.init(renderer);

    menu();
}

void FlappyBird::menu()
{
    sfx.playSwoosh();
    sfx.playBGM();
    while(menuLoop==true && casual == false )
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_QUIT:
                menuLoop = false;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.scancode)
                {
                case SDL_SCANCODE_W:
                case SDL_SCANCODE_UP:
                    sfx.playSelect();
                    selection.select(true);
                    break;
                case SDL_SCANCODE_S:
                case SDL_SCANCODE_DOWN:
                    sfx.playSelect();
                    selection.select(false);
                    break;
                case SDL_SCANCODE_RETURN:
                    switch(selection.selected)
                    {
                    case 1:
                        casual = true;
                        menuLoop = false;
                        sfx.playSelected();
                        break;
                    case 2:
                        if(help==false)
                            help = true;
                        else help = false;
                        sfx.playSelected();
                        break;
                    case 3:
                        menuLoop = false;
                        break;
                    case 4:

                        sfx.playSelected();
                    }
                    break;
                default:
                    break;
                }
            default:
                break;
            }
        }
        SDL_RenderClear(renderer);

        background.display(renderer, multiplier);
        base.display(renderer, multiplier);
        message.displayMenu(renderer);
        text.display(renderer);
        selection.display(renderer);
        if(help == true)
            text.helperDisplay(renderer);

        framerateControl(frameNum);
        SDL_RenderPresent(renderer);
    }
    sfx.stopBGM();
    resInit();
    if(casual==true)
        getReady();
}

void FlappyBird::getReady()
{
    sfx.playSwoosh();
    bird.initCasual();
    while(readyLoop == true)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_QUIT:
                gameLose = true;
                readyLoop = false;
                gameReset = true;
                gameQuit = true;
                break;

            case SDL_KEYDOWN:
                switch(event.key.keysym.scancode)
                {
                case SDL_SCANCODE_SPACE:
                    bird.update();
                    bird.keyUpdate();
                    readyLoop = false;
                    break;
                default:
                    break;
                }
            }
        }
        background.display(renderer, multiplier);
        base.display(renderer, multiplier);
        bird.display(renderer);
        bird.aniUpdate();
        message.display(renderer, false);
        SDL_RenderPresent(renderer);
        framerateControl(frameNum);
    }
    gameLoop();
}

void FlappyBird::gameLoop()
{
    while(!gameLose)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_QUIT:
                gameLose = true;
                gameReset = true;
                gameQuit = true;
                break;
            
            case SDL_KEYDOWN:
                switch(event.key.keysym.scancode)
                {            
                case SDL_SCANCODE_SPACE:
                    bird.keyUpdate();
                    sfx.playWing();
                    break;
                default:
                    break;
                }
            }
        }
        bird.update();
        bird.statusUpdate(gameLose);
        nextLevel();
        bird.collideBase(base.rect1, base.rect2, gameLose);
        framerateControl(frameNum);
        display();
    }
    if(gameQuit == false)
        gameOver();
}

void FlappyBird::gameOver()
{
    //Gameover Scene
    multiplier = 0;
    sfx.playHit();
    flash.display(renderer);
    sfx.playDie();
    while(bird.dstrect.y<1000)
    {
        SDL_RenderClear(renderer);

        background.display(renderer, multiplier);
        base.display(renderer, multiplier);
        resGen();
        bird.update();
        bird.statusUpdate(gameLose);
        bird.display(renderer);
        flash.displayNoAlpha(renderer);

        framerateControl(frameNum);
        SDL_RenderPresent(renderer);
    }
    sfx.playSwoosh();

    //High-score(saves) R/W
    saves.read();
    if(casual == true)
    {
        if(saves.compareCasual(score))
        {
            scoreboard.newHighScore = true;
        }
        scoreboard.getHighScore(saves.highscoreCasual);
    }
    saves.write();

    while(gameReset==false)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_QUIT:
                gameReset = true;
                gameQuit = true;
            case SDL_KEYDOWN:
                switch(event.key.keysym.scancode)
                {
                case SDL_SCANCODE_RETURN:
                    gameReset = true;
                default:
                    break;
                }
            }
        }
        SDL_RenderClear(renderer);

        background.display(renderer, multiplier);
        base.display(renderer, multiplier);
        for(int i=0; i<6; i++)
        {
            if(coinStatus[i]==true && coinRandom[i]==1)
            {
                coin[i].display(renderer);
            }
            if(casual == true)
            {
                pipe[i].display(renderer);
            }
        }
        message.displayGameOver(renderer);
        scoreboard.displayGameOver(renderer);

        framerateControl(frameNum);
        SDL_RenderPresent(renderer);
    }
    if(gameQuit == false)
    {
        reset();
    }
}

void FlappyBird::display()
{
    SDL_RenderClear(renderer);

    background.display(renderer, multiplier);
    base.display(renderer, multiplier);
    resGen();
    if(casual == true)
        bird.display(renderer);
    scoreboard.display(renderer, bird.dstrect.y);

    SDL_RenderPresent(renderer);
}

void FlappyBird::resInit()
{
    //Get a random choice
    randNum = rand() % 2;

    for(int i=0; i<6; i++)
    {
        //Load a random pipe sprite based on randNum
        if(randNum == 0)
            pipe[i].loadGreen(renderer);
        else
            pipe[i].loadRed(renderer);

        //Initialize pipe(s) based on game mode
        if(casual == true)
            pipe[i].init(i*250);
        scoreStatus[i]=false;

        //Initialize coin(s)
        coin[i].loadPNG(renderer);
        coin[i].init(i*250);
        coinStatus[i] = true;
        coinRandom[i] = rand() % 2;
}
}

        void FlappyBird::resGen(){
            if(delay>0)
            {
                delay--;
            }
            if(delay==0)
            {
                for(int i=0; i<6; i++)
                {
                    //Pipe Generators & Score Updater
                    if(pipe[i].dstrectDown.x<-60)
                    {
                        if(casual == true)
                            pipe[i].init(150);
                        scoreStatus[i] = false;
                    }
                    if(collisionCheck(bird.dstrect, pipe[i].dstrectDown))
                    {
                        gameLose = true;
                    }
                    if(collisionCheck(bird.dstrect, pipe[i].dstrectUp) && casual == true)
                    {
                        gameLose = true;
                    }
                    if(bird.dstrect.x > pipe[i].dstrectDown.x && scoreStatus[i]==false && gameLose == false)
                    {
                        sfx.playPoint();
                        score+=multiplier;
                        scoreStatus[i] = true;
                        scoreboard.update(score);
                    }
                    //Display Pipe(s)
                    if(casual == true)
                    {
                        pipe[i].display(renderer);
                        pipe[i].update(multiplier);
                    }

                    //Coin Generators && Score Updater
                    if(coin[i].dstrect.x<-60)
                    {
                        coin[i].init(10);
                        coinStatus[i] = true;
                        coinRandom[i] = rand() % 2;
                    }
                    if(collisionCheck(bird.dstrect, coin[i].dstrect) && coinStatus[i]==true && coinRandom[i]==1)
                    {
                        sfx.playCoin();
                        score+=2;
                        scoreboard.update(score);
                        coinStatus[i]=false;
                    }
                    //Display Coin(s)
                    coin[i].updatePos(multiplier);
                    if(coinStatus[i]==true && coinRandom[i]==1)
                        coin[i].display(renderer);

                    //Pacman

                }
            }
        }

        void FlappyBird::resDestroy()
        {
            for(int i=0; i<6; i++)
            {
                pipe[i].destroy();
                coin[i].destroy();
            }
        }

        void FlappyBird::nextLevel()
        {
            if(score>=20 && level2==false)
            {
                multiplier = 2;
                level2 = true;
                sfx.playLevelUp();
            }
        }
