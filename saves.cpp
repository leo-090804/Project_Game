#include "saves.h"

using namespace std;

void Saves::read()
{
    savefile.open("saves\\casual.txt");
    if(savefile.is_open())
    {
        savefile >> highscoreCasual;
    }
    savefile.close();

}

bool Saves::compareCasual(int score)
{
    if (highscoreCasual < score)
    {
        highscoreCasual = score;
        return true;
    }
    return false;
}



void Saves::write()
{
    savefile.open("saves\\casual.txt", ios::out | ios::trunc);
    savefile << highscoreCasual;
    savefile.close();

}
