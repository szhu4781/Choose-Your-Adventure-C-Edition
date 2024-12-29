#ifndef EVENT_H
#define EVENT_H

#include <iostream>
#include <string>

using namespace std;

class Event{
protected:
    string type;
    int health;
    int attack;
    string reward;
    bool outcome;

public:
    Event(); //constructor

    /*Future reference: We add const after our getters so
    that the results from our setters doesn't get modified
    by our getters. The getters will always return the results
    from the setters.*/

    //setters and getters for mob stats

    //enemy health bar
    virtual void set_health(int hp) ;
    virtual int get_health() const;

    //enemy strength and power
    virtual void set_attack(int atk); 
    virtual int get_attack() const;

    //loot drops
    virtual void set_loot(string loot);
    virtual string get_loot() const;

    //battle outcome
    virtual void set_outcome(bool result);
    virtual bool get_outcome() const;

    //function to check if the monster is an elite
    virtual bool isElite(){return false;}

    virtual ~Event(); //destructor if needed
};

#endif