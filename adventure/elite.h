#ifndef ELITE_H
#define ELITE_H

#include "event.h"

using namespace std;

//This is deriving from the event
class Elite : public Event{
public:
    Elite(); //constructor
    virtual ~Elite() = default; //destructor if needed

    //setters and getters for elite mob stats

    //enemy health bar
    virtual void set_health(int hp) override;
    virtual int get_health() const;

    //enemy strength and power
    virtual void set_attack(int atk) override;
    virtual int get_attack() const;

    //loot drops
    virtual void set_loot(string loot) override;
    virtual string get_loot() const;

    //battle outcome
    virtual void set_outcome(bool result) override;
    virtual bool get_outcome() const;

    bool isElite() override {return true;}

};

#endif