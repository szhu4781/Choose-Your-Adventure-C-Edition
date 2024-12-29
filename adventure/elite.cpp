#include "elite.h"
#include <ctime>
#include <cstdlib>

using namespace std;

//constructor
Elite::Elite(){
    srand(static_cast<unsigned int>(time(0)));

    //Elite enemies are tougher and strong
    set_health(rand() % 300 + 100);
    set_attack(rand() % 11 + 20);
    set_loot("Rare Item"); //Change parameter if needed
    set_outcome(false); //Default state: Assume that the player always loses
};


void Elite::set_health(int hp){
    this->health = hp;
}

int Elite::get_health() const{
    return this->health;
}

void Elite::set_attack(int atk){
    this->attack = atk;
}

int Elite::get_attack() const{
    return this->attack;
}

void Elite::set_loot(string loot){
    this->reward = loot;
}

string Elite::get_loot() const{
    return this->reward;
}

void Elite::set_outcome(bool result){
    this->outcome = result;
}

bool Elite::get_outcome() const{
    return this->outcome;
}