#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include "loot.h"

using namespace std;

class Player {
private:
    int health;                     //base health
    int maxHP;                      //max health value
    int baseMaxHP;                  //default max health
    int attack;                     //base attack
    Loot equipped;                  //used for tracking equipped weapon    
    Loot armory;                    //used for tracking equipped armor
    vector<Loot> inventory;         //structure of inventory system
    set<string> obtained;           //used for tracking obtained items; mainly to prevent dupes
    map<string, int> counter;       //counts how many item dupes
    map<string, int> materials;     //materials
public:
    Player(int hp, int atk);

    //Getters and setters
    void setHP(int);   
    int getHP() const;

    void setATK(int);
    int getATK() const;

    //Adding loot to inventory
    void addLoot(const Loot& loot);

    //Equipping weapon
    void equipWeapon(const Loot&);

    //Equipping armor
    void equipArmor(const Loot&);

    //Inventory display
    void displayInv();

    //Weapon selection
    void weaponSelect();

    //Armor selection
    void armorSelect();

    //Restoring health
    void restoreHealth(int);

    //Has a specific item in inventory
    bool hasItem(const string&) const;

    void removeLoot(const string&);

    //Methods for intializing crafting
    //------------------------------------------------------------------------------------------------------//
    
    //Has the the right amount of materials
    bool hasMats(const string&, int) const; 
    
    //Checks how much material the player has
    int getMatsCount(const string&) const;

    //Adding materials
    void addMats(const string&, int);

    //Using materials
    bool useMats(const string&, int);

    //Clear materials
    void clearMats();
};
#endif