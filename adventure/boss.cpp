#include "boss.h"
#include <ctime>
#include <cstdlib>

using namespace std;

Boss::Boss(){
    srand(static_cast<unsigned int>(time(0)));

    set_health(rand() % 800 + 500);
    set_attack(rand() % 50 + 100);
    set_loot("Legendary Item");
    set_outcome(false);
};

void Boss::set_health(int hp){
    this->health = hp;
}

int Boss::get_health() const{
    return this->health;
}

void Boss::set_attack(int atk){
    this->attack = atk;
}

int Boss::get_attack() const{
    return this->attack;
}

void Boss::set_loot(string loot){
    this->reward = loot;
}

string Boss::get_loot() const{
    return this->reward;
}

void Boss::set_outcome(bool result){
    this->outcome = result;
}

bool Boss::get_outcome() const{
    return this->outcome;
}