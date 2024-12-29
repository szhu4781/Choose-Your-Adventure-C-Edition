#include "event.h"
#include <ctime>
#include <cstdlib>

using namespace std;

//constructor
Event::Event(){
    /*We generate a random seed and we convert its the seed type
    into an unsigned integer of the current time measured in seconds.
    */
    srand(static_cast<unsigned int>(time(0)));

    // We randomize the stats of enemy health and attack
    health = rand() % 50 + 10;
    attack = rand() % 10 + 1;
};

//Destructor if needed
Event::~Event(){

};

//Defined setters and getters

void Event::set_health(int hp){
    health = hp;
}

int Event::get_health() const{
    return health;
}

void Event::set_attack(int atk){
    attack = atk;
}

int Event::get_attack() const{
    return attack;
}

void Event::set_loot(string loot){
    reward = loot;
}

string Event::get_loot() const{
    return reward;
}

void Event::set_outcome(bool result){
    outcome = result;
}

bool Event::get_outcome() const{
    return outcome;
}