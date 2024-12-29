#include <iostream>
#include "adv.h"

using namespace std;

int main(){
    //Seed RNG with static casting
    srand(static_cast<unsigned int>(time(0)));

    //Initialize the stats of the player
    int startHealth = 100;
    int startAttack = 10;
    Adventure game(startHealth, startAttack);

    game.startGame();

    return 0;
}