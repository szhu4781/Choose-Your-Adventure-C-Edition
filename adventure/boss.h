#ifndef BOSS_H
#define BOSS_H

#include "event.h"

using namespace std;

class Boss : public Event{
public:
    Boss(); //constuctor if needed
    virtual ~Boss() = default; // destructor if needed

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
};

#endif