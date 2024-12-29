#ifndef LOOT_H
#define LOOT_H

#include <iostream>
#include <string>
#include <variant>
#include <vector>

using namespace std;

struct Loot{
    string name;
    string tier;
    double rarity;
    int value;
    bool isWeapon;
    bool isUnique;
    int quantity;
    bool isArmor;

    static vector <Loot> lootPool;
    static vector <Loot> rarePool;

    //Constructor
    Loot(const string& itemName = "Unknown", const string &itemTier = "Unknown", double itemRarity = 0.0, int val = 0, 
        bool weapon = false, bool unique = false, int q = 0, bool armor = false) :
        name(itemName), tier(itemTier), rarity(itemRarity), value(val), 
        isWeapon(weapon), isUnique(unique), quantity(q), isArmor(armor){}

    //Setters
    void setName(const string& newName){name = newName;};
    void setTier(const string& newTier){tier = newTier;};
    void setRarity(int newRarity){rarity = newRarity;};
    void setValue(int val){value = val;};
    void setQuant(int amount){quantity = amount;};

    //Getters
    string getName() const{return name;};
    string getTier() const{return tier;};
    double getRarity() const{return rarity;};
    int getValue() const{return value;};
    int getQuant() {return quantity;};


    //Data display
    void displayLoot() const{    
        cout << name << endl;
        cout << "Tier: " << tier << endl;

        if(name == "Armor of the Pheonix"){
            cout << "Rarity: " << static_cast<double>(rarity) << endl;
        } else{
            cout << "Rarity: " << rarity << endl;
        }
    };

    //copy constructor
    Loot(const Loot& other){
        name = other.name;
        tier = other.tier;
        rarity = other.rarity;
        value = other.value;
        isWeapon = other.isWeapon;
        isUnique = other.isUnique;
        isArmor = other.isArmor;
    };

    //assigment operator overload
    Loot& operator=(const Loot& other){
        if(this != &other){
            name = other.name;
            tier = other.tier;
            rarity = other.rarity;
            value = other.value;
            isWeapon = other.isWeapon;
            isUnique = other.isUnique;
            quantity = other.quantity;
            isArmor = other.isArmor;
        }
        return *this;
    }

    //equal operator overload (keep this uncommented in case something goes wrong)
    bool operator==(const Loot& other) const{
        return name == other.name &&
        tier == other.tier &&
        rarity == other.rarity &&
        value == other.value &&
        isWeapon == other.isWeapon &&
        isUnique == other.isUnique &&
        quantity == other.quantity &&
        isArmor == other.isArmor;
    }
};

#endif