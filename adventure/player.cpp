#include "player.h"
#include "loot.h"

using namespace std;

//constructor
Player::Player(int hp, int atk) : 
    health(hp), 
    maxHP(hp),    // Start with base max HP
    baseMaxHP(hp), // Store the base value
    attack(atk), 
    equipped("None", "None", 0, 0, false),
    armory("None", "None", 0, 0, false, false, 0, false) {}
    //Getter and setter for the player health points

void Player::setHP(int hp) {
    health = hp;
}

int Player::getHP() const {
    return health;
}

//Getter and setter for player attack
void Player::setATK(int atk){
    attack = atk;
}

int Player::getATK() const{
    return attack;
}

//Adding items to inventory
void Player::addLoot(const Loot& loot){
    if(loot.isUnique){
        // Initialize if not exists
        if(materials.find(loot.getName()) == materials.end()) {
            materials[loot.getName()] = 0;
            counter[loot.getName()] = 0;
        }

        // Update quantities
        materials[loot.getName()] += 1;  // Always add 1, not loot.quantity
        counter[loot.getName()] += 1;

        // Update or add to inventory
        auto it = find_if(inventory.begin(), inventory.end(), [&](Loot& exist){
            return exist.getName() == loot.getName();
        });

        if(it != inventory.end()){
            it->quantity = materials[loot.getName()];  // Sync with materials map
        } else {
            Loot newItem = loot;
            newItem.quantity = 1;  // Start with quantity 1
            inventory.push_back(newItem);
        }
        cout << "Obtained: " << loot.name << endl; 
        return;
    }

    // Non-unique items handling remains the same
    if(obtained.find(loot.getName()) != obtained.end()){
        cout << "You've already have a " << loot.getName() << endl;
    } else {
        inventory.push_back(loot);
        obtained.insert(loot.getName());
        cout << "Obtained: " << loot.name << " " << "Tier: " << loot.tier << " " << "Rarity: " << loot.rarity << endl;
    }
}

//Weapon equipping function
void Player::equipWeapon(const Loot& weapon){
    if(weapon.isWeapon){
        equipped = weapon;
        attack = equipped.value;
        cout << "You've equipped " << weapon.name << ". Attack increased to " << weapon.value << endl;
    }
    else {
        cout << "Cannot equip." << endl;
    }  
}

//Armor equipping function
void Player::equipArmor(const Loot& armor){
    if(armor.isArmor){
        armory = armor;

        //Armor increase max health
        maxHP = armor.value;  
        
        // When equipping new armor, set health to new maximum
        health = maxHP;
        
        cout << "You've equipped " << armor.name << "." << endl;
        cout << "Max Health increased to " << maxHP << " (Base: " << baseMaxHP << " + Armor: " << armor.value << ")" << endl;
    }
    else {
        cout << "Cannot equip." << endl;
    }
}

//Inventory display
void Player::displayInv(){
    //Check if the inventory is empty
    if(inventory.empty()){
        cout << "Your inventory is empty." << endl;
    }

    //Check if a weapon is equipped
    if(equipped.isWeapon){
        cout << "Weapon: " << equipped.name << "(Damage: " << equipped.value << ")" << endl;
    } else {
        cout << "No weapon equipped." << endl;
    }

    //Check if an armor is equipped
    if(armory.isArmor){
        cout << "Armor: " << armory.name << "(Health: " << armory.value << ")" << endl;
    } else {
        cout << "No armor equipped." << endl;
    }
    cout << endl;

    cout << "Items" << endl << endl;

    //Logic for ore counter
    if(!counter.empty()){
        for (const auto& pair : materials){
            if(pair.second > 0){
                cout << pair.first << " (x" << pair.second << ")" << endl;
            }
        }
    }

    //We use size_t rather than int because we are
    //store the sizes of objects in this case item drops
    //given that we have variety of unique drops that
    //takes up memory

    //Vectors can take up memory in C++, and our item drops
    //are all initialized using vectors
    for(size_t i = 0; i < inventory.size(); ++i){
        if(counter.find(inventory[i].getName()) != counter.end()){
            continue;
        }
        cout << inventory[i].getName() 
        << " (Tier: " << inventory[i].getTier() 
        << ", Rarity: " << inventory[i].getRarity() << ")" << endl;
    }
    cout << "---------------------------------" << endl;

    cout << "Equipment" << endl << endl;
    bool hasWeapon = false;
    bool hasArmor = false;
    for(size_t i = 0; i < inventory.size(); ++i){
        if(inventory[i].isWeapon){
            hasWeapon = true;
            cout << inventory[i].getName() 
            << " (Tier: " << inventory[i].getTier() 
            << ", Rarity: " << inventory[i].getRarity() 
            << ", Damage: " << inventory[i].getValue() << ")" << endl;
        } 
        else if(inventory[i].isArmor){
            hasArmor = true;
            cout << inventory[i].getName() 
            << " (Tier: " << inventory[i].getTier() 
            << ", Rarity: " << inventory[i].getRarity() 
            << ", Health: " << inventory[i].getValue() << ")" << endl;
        }
    }
    cout << "---------------------------------" << endl;

    if(!hasWeapon){
        cout << "No weapons available." << endl;
    }

    if(!hasArmor){
        cout << "No armor available." << endl;
    }

    cout << "Change Weapon or Armor (Q)" << endl;
}

//Weapon selecting function
void Player::weaponSelect(){
    vector<size_t> index;
    size_t selection;
    
    //Displays all available weapons the player can equip
    for(size_t i = 0; i < inventory.size(); ++i){
        if(inventory[i].isWeapon){
            index.push_back(i);
            cout << index.size() << ". " << inventory[i].getName() 
            << " (Damage: " << inventory[i].getValue() << ")" 
            << (inventory[i].getName() == equipped.getName() ? " [Equipped]" : "") << endl;
        }
    }
    cout << "Select a weapon (enter the number of the weapon you want to equip): " << endl;
    cin >> selection;

    //Validation
    if (selection < 1 || selection > index.size()){
        cout << "Invalid selection. Please try again." << endl;
    } 
    else {
        size_t selectedIdx = index[selection - 1];
        // Check if weapon is already equipped
        if(inventory[selectedIdx].getName() == equipped.getName()){
            cout << "This weapon is already equipped." << endl;
        } else {
            equipped = inventory[selectedIdx];
            setATK(equipped.getValue());
            cout << "Successfully equipped " << equipped.getName() << "." << endl;
        }
    }    
}

//Armor selecting function
void Player::armorSelect(){
    vector<size_t> index;
    
    // First check if there are any armors available
    bool hasArmor = false;
    for(size_t i = 0; i < inventory.size(); ++i){
        if(inventory[i].isArmor){
            hasArmor = true;
            break;
        }
    }

    // If no armor is available, return early
    if(!hasArmor){
        cout << "No armor available to equip." << endl;
        return;
    }

    // Continue with armor selection if armors are available
    size_t selection;
    
    //Displays all available armor the player can equip
    for(size_t i = 0; i < inventory.size(); ++i){
        if(inventory[i].isArmor){
            index.push_back(i);
            cout << index.size() << ". " << inventory[i].getName() 
            << " (Health: " << inventory[i].getValue() << ")" 
            << (inventory[i].getName() == armory.getName() ? " [Equipped]" : "") << endl;
        }
    }
    cout << "Select armor (enter the number of the armor you want to equip): " << endl;
    cin >> selection;

    //Validation
    if (selection < 1 || selection > index.size()){
        cout << "Invalid selection. Please try again." << endl;
    } 
    else {
        size_t selectedIdx = index[selection - 1];
        if(inventory[selectedIdx].getName() == armory.getName()){
            cout << "This armor is already equipped." << endl;
        } else {
            equipArmor(inventory[selectedIdx]);
        }
    }    
}

//Health restore function
void Player::restoreHealth(int amount){
    if (health >= maxHP){
        cout << "Your health is already full." << endl;
        return;
    }

    int oldHealth = health;
    health += amount;

    //Ensures that the health doesn't exceed the max health
    if (health > maxHP){
        health = maxHP;
    }

    cout << "Health restored from " << oldHealth << " to " << health << "/" << maxHP << endl;
}

//Searches the player's inventory for an item
bool Player::hasItem(const string& itemName) const{
    auto it = find_if(inventory.begin(), inventory.end(), [&](const Loot& item){
        return item.name == itemName;
    });
    return it != inventory.end();
}

//Removes an item from the player's inventory
void Player::removeLoot(const string& itemName){
    auto it = find_if(inventory.begin(), inventory.end(), [&](const Loot& item){
        return item.name == itemName;
    });
    
    if(it != inventory.end()){
        inventory.erase(it);
        cout << itemName << " has been used." << endl;
    }
}

//Checks if player has materials
bool Player::hasMats(const string& material, int count) const {
    // First check if material exists in the materials map
    auto matIt = materials.find(material);
    if(matIt == materials.end() || matIt->second <= 0) {
        return false;  // Material doesn't exist or quantity is 0/negative
    }

    // Then check if we have enough
    if(matIt->second >= count) {
        return true;
    }

    return false;
}

//Gets the quantity of materials
int Player::getMatsCount(const string& material) const{
    auto it = materials.find(material);
    return (it != materials.end()) ? it->second : 0;
}

//Adds the materials when crafting or smelting something
void Player::addMats(const string& material, int count){
    // Add the material to the map
    materials[material] += count;
    counter[material] += count;  // Update counter too

    // Try and find the material in inventory
    auto it = find_if(inventory.begin(), inventory.end(), [&](Loot& item){
        return item.name == material;
    });

    if(it != inventory.end()){
        // Update the quantity of existing material
        it->quantity += count;
    } else {
        // Create new material with specified count
        Loot newMat(material, "Uncommon", 60, 0, false, true, count);
        inventory.push_back(newMat);
    }
}

//Materials are used
bool Player::useMats(const string& material, int count){
    // First check if we have the material and enough quantity
    auto matIt = materials.find(material);
    if(matIt == materials.end() || matIt->second < count) {
        return false;  // Not enough materials
    }

    // Update quantities
    materials[material] -= count;
    counter[material] -= count;

    // Update inventory quantity
    auto it = find_if(inventory.begin(), inventory.end(), 
        [&](Loot& item) {
            return item.name == material;
        });
    
    if(it != inventory.end()){
        it->quantity = materials[material];  // Sync with materials map
    }

    // Remove if quantity is 0
    if(materials[material] <= 0){
        materials.erase(material);
        counter.erase(material);
        if(it != inventory.end()){
            inventory.erase(it);
        }
    }

    return true;
}

//Clean up any excess memory
void Player::clearMats(){
    materials.clear();
}

