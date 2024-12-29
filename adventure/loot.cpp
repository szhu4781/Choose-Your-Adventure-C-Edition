#include "loot.h"

using namespace std;

//Item drops
vector<Loot> Loot::lootPool = {
    //Sequence: name, tier, rarity, damage, item classification (weapon or item), ore type
    Loot("Iron Ore", "Common", 100, 0, false, true),
    Loot("Iron Sword", "Uncommon", 80, 50, true, false),
    Loot("Gold Ore", "Rare", 50, 0, false, true),
    Loot("Sword Hilt", "Legendary", 10, 0, false, false),
    //Loot("Rusted Key", "Mythic", 1, 0, false, false),
    Loot("Mysterious Cube", "Legendary", 5, 0 , false, false),
    Loot("Pheonix Feather", "Mythic", 1, 0, false, false)
};

//obtained from elite bosses
vector <Loot> Loot::rarePool{
    Loot("Minotaur's Horn", "Rare", 50, 0, false, false),
    Loot("Guardian's Axe", "Epic", 25, 250, true, false),
    Loot("Diamond", "Epic", 20, 0, false, true),
    Loot("Rusted Key", "Mythic", 1, 0, false, false),
    Loot("Pheonix Feather", "Mythic", 1, 0, false, false)
};

