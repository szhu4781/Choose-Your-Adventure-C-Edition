#include "adv.h"

using namespace std;

//constructor
Adventure::Adventure(int playerHP, int playerATK) : 
    player(playerHP, playerATK), current(0), openInv(false), elite(), regular(), boss(){
    Loot stick("Stick", "Common", 100, 10, true);
    player.addLoot(stick);
    player.equipWeapon(stick);
    stick.isWeapon = true;
}

//game initialization
void Adventure::startGame(){
    cout << "You have awaken in the start of the labyrinth." << endl;
    while(playerStatus()){
        //If the inventory is not opened, display the room
        if(!openInv){
            displayRoom();
        }
        char choice;

        //Display options based on the room
        //Since we start at the first room, we only get one choice
        if(current == 0){
            cout << "What would you like to do?" << endl;
            cout << "A. Move forward" << endl;
        }
        //More available choices after exiting starting room
        else {
            cout << "What would you like to do?" << endl;
            cout << "A. Move forward" << endl;
            cout << "B. Go left" << endl;
            cout << "C. Go right" << endl;
            cout << "D. Rest here." << endl;
        }   
        cout << "Open Inventory (E)" << endl; //Opening inventory hot key is E
        cout << "Menu (M)" << endl;
        cin >> choice;
        
        //Inventory display and choice handling
        if(choice == 'E' || choice == 'e'){
            openInv = displayInventory();
        } else if(choice == 'M' || choice == 'm'){
            openMenu = displayMenu();
        }
        else {
            handleChoice(choice);
        }
    }
    cout << "Your journey ends here. Game over." << endl;
}

//function for displaying the current room
void Adventure::displayRoom() const{
    cout << "Room: " << current << endl;
    switch(current){
        //this case is only for the start of the game
        case 0: 
            cout << "You are at the entrance of the labyrinth." << endl;
            cout << "A dark path awaits ahead." << endl;
            break;

        default: 
            //when the current is > 1, randomly prints between 4 unique messages
            if (current > 1){
                int message = rand() % 100;

                if (message < 25){
                    cout << "You walk along the narrow, quiet hallway." << endl;
                    cout << "A fork is up ahead." << endl;
                }
                else if(message < 50){
                    cout << "You walk along the spacious hallway. You can hear faint noises ahead." << endl;
                    cout << "The path splits into two." << endl;
                }
                else if(message < 75){
                    cout << "You walk down the damp, murky path. The air is chilly." << endl;
                }
                else {
                    cout << "You hear faint whispers and noises ahead." << endl;
                    cout << "You get the feeling that you are being watched." << endl;
                }
            }
            else {
                cout << "You walk along the narrow, quiet hallway." << endl;
                cout << "A fork is up ahead." << endl;
            }
            break;
    }
}

//function for displaying the inventory
bool Adventure::displayInventory(){
    //If the inventory isn't open, open it
    if(!openInv){
        openInv = true;
        cout << "Inventory: " << endl;
        player.displayInv();
        cout << "Press E again to close inventory." << endl;

        char choice;

        //If inventory has been opened, display it for the user
        while(openInv){   
            cin >> choice;

            if(choice == 'E' || choice == 'e'){
                openInv = false;
            } 
            else if(choice == 'Q' || choice == 'q'){
                player.weaponSelect();
                player.armorSelect();
                cout << "Inventory: " << endl;
                player.displayInv();
                cout << "Press E again to close inventory." << endl;
            }
            else {
                cout << "Invalid input. Please try again." << endl << endl;
                cout << "Inventory: " << endl;  // Re-display inventory
                player.displayInv();
                cout << "Press E again to close inventory." << endl;
            }
        }
    }

    return openInv;
}

//function to display menu
bool Adventure::displayMenu(){
    if(!openMenu){
        openMenu = true;
        cout << "Menu" << endl;
        cout << "Press Q to quit game." << endl;
        cout << "Press M to go back." << endl;

        char choice;
        cin >> choice;

        //if the user presses q, quit the game
        if(choice == 'Q' || choice == 'q'){
            exit(0);
        }
        else if(choice == 'M' || choice == 'm'){
            openMenu = false;
        }
        else {
            cout << "Invalid input. Please try again." << endl;
        }
    }
    return openMenu;
}

//function for creating the crafting room
void Adventure::craftingRoom(){
    cout << "You've encountered a forge. Perhaps you can use the tools here..." << endl;

    bool crafting = true;
    while(crafting){
        cout << "What would you like to do?" << endl;
        cout << "A. Craft a weapon" << endl;
        cout << "B. Craft armor" << endl;
        cout << "C. Smelt Ores" << endl;
        cout << "D. Leave" << endl;

        char choice;
        cin >> choice;

        switch(choice){
            //Weapon crafting
            case 'A':
            case 'a': {
                bool weaponCraft = true;
                while(weaponCraft){
                    cout << "What would you like to craft?" << endl;
                    cout << "1. Golden Sword (5 Gold, 3 Iron)" << endl;
                    cout << "2. Diamond Sword (7 Diamonds, 7 Iron)" << endl;
                    cout << "3. Sword of the Labyrinth (1 Sword Hilt, 10 Diamonds, 7 Minotaur Horns)" << endl;
                    cout << "4. Go back" << endl;

                    int weaponChoice;
                    cin >> weaponChoice;

                    if (weaponChoice == 1){
                        if(player.hasMats("Gold", 5) && player.hasMats("Iron", 3)){
                            player.useMats("Gold", 5);
                            player.useMats("Iron", 3);
                            Loot goldSword("Golden Sword", "Rare", 50, 75, true, false);
                            player.addLoot(goldSword);
                            cout << "Golden Sword crafted. Check your inventory." << endl;
                        } else {
                            cout << "Not enough materials." << endl;
                        }
                    }
                    else if(weaponChoice == 2){
                        if(player.hasMats("Diamond", 7) && player.hasMats("Iron", 7)){
                            player.useMats("Diamond", 7);
                            player.useMats("Iron", 7);
                            Loot diamondSword("Diamond Sword", "Legendary", 30, 120, true, false);
                            player.addLoot(diamondSword);
                            cout << "Diamond Sword crafted. Check your inventory." << endl;
                        } 
                        else {
                            cout << "Not enough materials." << endl;
                        }
                    }
                    else if(weaponChoice == 3){
                        if(player.hasItem("Sword Hilt") && player.hasMats("Diamonds", 10) && player.hasMats("Minotaur Horns", 7)){
                            player.removeLoot("Sword Hilt");
                            player.useMats("Diamond", 10);
                            player.useMats("Minotaur's Horn", 7);
                            Loot labSword("Sword of the Labyrinth", "Legendary", 10,  400, true, false);
                            player.addLoot(labSword);
                            cout << "The Sword of the Labyrinth has been forged. You feel a powerful force..." << endl;
                        }
                        else {
                            cout << "Not enough materials." << endl;
                        }
                    }
                    else if(weaponChoice == 4){
                        weaponCraft = false;
                    }
                    //Testing purposes (Checks if crafting weapons works)
                    // else if(weaponChoice == 5){
                    //     if(player.hasMats("Iron", 1)){
                    //         player.useMats("Iron", 1);
                    //         Loot sword("Sword", "Rare", 50, 75, true, false);
                    //         player.addLoot(sword);
                    //         cout << "Sword crafted. Check your inventory." << endl;
                    //     } else {
                    //         cout << "Not enough materials." << endl;
                    //     }
                    // }
                    else if(weaponChoice == 5){
                        if(player.hasItem("Mysterious Cube") && player.hasItem("Marble")){
                            player.removeLoot("Mysterious Cube");
                            player.removeLoot("Marble");
                            Loot uncertain("???", "Error", 0, 0, false, false);
                            player.addLoot(uncertain);
                            cout << "??? crafted. Check your inventory." << endl;
                        } else {
                            cout << "Invalid choice. Try again." << endl;
                        }
                    }
                    else {
                        cout << "Invalid choice. Try again." << endl;
                    }
                }
                break;
            }
            
            //Armor crafting
            case 'B':
            case 'b': {
                bool armorCraft = true;
                while(armorCraft){
                    cout << "What would you like to craft?" << endl;
                    cout << "1. Iron Armor (10 Iron)" << endl;
                    cout << "2. Golden Armor (10 Gold)" << endl;
                    cout << "3. Diamond Armor (10 Diamond)" << endl;
                    cout << "4. Go back" << endl;

                    int armorChoice;
                    cin >> armorChoice;

                    if(armorChoice == 1){
                        //Change value for required materials to 1 for testing
                        //Change value back to 10 when 
                        if(player.hasMats("Iron", 10)){
                            player.useMats("Iron", 10);
                            Loot ironArmor("Iron Armor", "Uncommon", 80, 150, false, false, 0, true);
                            player.addLoot(ironArmor);
                            cout << "Iron Armor has been crafted. Check your inventory." << endl;
                        } else {
                            cout << "Not enough materials." << endl;
                        }
                    }
                    else if (armorChoice == 2){
                        if(player.hasMats("Gold", 10)){
                            player.useMats("Gold", 10);
                            Loot goldArmor("Golden Armor", "Rare", 50, 200, false, false, 0, true);
                            player.addLoot(goldArmor);
                            cout << "Golden Armor has been crafted. Check your inventory." << endl;
                        } else {
                            cout << "Not enough materials." << endl;
                        }
                    }
                    else if(armorChoice == 3){
                        if(player.hasMats("Diamond", 10)){
                            player.useMats("Diamond", 10);
                            Loot diamondArmor("Diamond Armor", "Legendary", 10, 300, false, false, 0, true);
                            player.addLoot(diamondArmor);
                            cout << "Diamond Armor has been crafted. Check your inventory." << endl;
                        } else {
                            cout << "Not enough materials." << endl;
                        }
                    }
                    else if(armorChoice == 4){
                        armorCraft = false;
                    }
                    else if(armorChoice == 5){
                        if(player.hasMats("Diamond", 100) && player.hasItem("Pheonix Feather")){
                            player.useMats("Diamond", 100);
                            player.removeLoot("Pheonix Feather");
                            Loot pheonixArmor("Armor of the Pheonix", "Ancient", 0.5, 2000, false, false, 0, true);
                            player.addLoot(pheonixArmor);
                            cout << "A powerful armor has been forged with the Pheonix feather. Check your inventory." << endl;
                        } else {
                            cout << "Invalid choice. Try again." << endl;
                        }
                    }
                    else {
                         cout << "Invalid choice. Try again." << endl;
                    }   
                }
                break;
            }
            
            //Smelting ores
            case 'C':
            case 'c': {
                bool smeltOre = true;
                while(smeltOre){
                    cout << "What would you like to smelt?" << endl;
                    cout << "1. Iron Ore" << endl;
                    cout << "2. Gold Ore" << endl;
                    cout << "3. Go back" << endl;

                    int smeltChoice;
                    cin >> smeltChoice;
                    int oreCount;

                    if(smeltChoice == 1){
                        // Check if player has Iron Ore and its quantity is > 0
                        oreCount = player.getMatsCount("Iron Ore");
                        if(oreCount > 0){
                            player.useMats("Iron Ore", 1);
                            player.addMats("Iron", 1);
                            cout << "Smelted 1 Iron Ore for 1 Iron. (" << oreCount - 1 << " Iron Ore remaining)" << endl;
                        } else {
                            cout << "Not enough Iron Ores." << endl;
                        }
                    }
                    else if (smeltChoice == 2){
                        // Check if player has Gold Ore and its quantity is > 0
                        oreCount = player.getMatsCount("Gold Ore");
                        if(oreCount > 0){
                            player.useMats("Gold Ore", 1);
                            player.addMats("Gold", 1);
                            cout << "Smelted 1 Gold Ore for 1 Gold. (" << oreCount - 1 << " Iron Ore remaining)" << endl;
                        } else {
                            cout << "Not enough Gold Ores." << endl;
                        }
                    }
                    else if(smeltChoice == 3){
                        smeltOre = false;
                    }
                    else {
                        cout << "Invalid choice. Try again." << endl;
                    }  
                }
                break;
            }

            //Leaving
            case 'D':
            case 'd': {
                cout << "You chose to leave the forge." << endl;
                crafting = false;
                break;
            }
            default:
                cout << "Invalid input. Please try again." << endl;
                break;
        }
    }
}

//Input handling
void Adventure::handleChoice(char choice){
    switch(current){
        case 0:  // Starting room - can only go forward
            if(choice == 'A' || choice == 'a'){
                cout << "You moved forward." << endl;
                current++;
            }
            else {
                cout << "Invalid input. Choose again." << endl;
            }
            break;
            
        default:  // All other rooms - full movement options
            if(choice == 'A' || choice == 'a'){
                cout << "You moved forward." << endl;
                current++;
                handleEvent();
            }
            else if (choice == 'B' || choice == 'b'){
                cout << "You went left." << endl;
                current++;
                handleEvent();
            }
            else if (choice == 'C' || choice == 'c'){
                cout << "You went right." << endl;
                current++;
                handleEvent();
            }
            else if (choice == 'D' || choice == 'd'){
                cout << "You decided to rest." << endl;
                player.restoreHealth(15);
            }
            else {
                cout << "Invalid input. Choose again." << endl;
            }
            break;
    }
}

//seperate function for handling events in specific rooms
void Adventure::handleEvent(){
    if(current % 100 == 0){
        finalRoom();
    } else if(current % 50 == 0){
        mazeCenter();
    } else if(current % 25 == 0){
        bossEncounter(player, boss);
    } 
    else if(current % 15 == 0){
        craftingRoom();
    } 
    else if (rand() % 100 < 50){
        eventEncounter(player, elite, regular);
    }
}

//Check the player's current health and status
bool Adventure::playerStatus() const{
    //If the player have health points, they are alive
    if(player.getHP() > 0){
        cout << "Health: " << player.getHP() << endl << endl;
        return true;
    }
    //Otherwise, they died
    else {
        return false;
    }
}

//function for getting lootpool data
Loot getRandomLoot(){
    int idx = rand() % Loot::lootPool.size(); //Generate a random index
    return Loot::lootPool[idx];               //Return loot in the index
}

//function for getting rare loot from lootpool
Loot getRareLoot(){
    int r_idx = rand() % Loot::rarePool.size();
    return Loot::rarePool[r_idx];
}

//function for setting up the battle between a monster in encounter
void Adventure::monsterBattle(Player& player, Event& monster){
    cout << "You've entered a battle with a " << (monster.isElite() ? "minotaur!" : "creature.") <<  endl;
    cout << "Monster HP:" << monster.get_health() << endl << endl;
    cout << "Player HP:" << player.getHP() << endl;

    int initialHealth = monster.get_health();

    char choice;

    //a choice can be made if the player and monster are still alive
    while (player.getHP() > 0 && monster.get_health() > 0){
        //Player goes first
        cout << "It is your turn. What will you do?" << endl;
        cout << "A. Attack" << endl;
        cout << "B. Rest" << endl;
        cout << "C. Flee" << endl;
        cin >> choice;

        //If the player attacks, reduce the monster's health based
        // on the player's attack
        if(choice == 'A' || choice == 'a'){
            int damage = player.getATK();
            cout << "You dealt " << damage << " damage to it." << endl << endl;
            monster.set_health(monster.get_health() - damage);
        }
        //if the player decides to rest, they restore health
        else if(choice == 'B' || choice == 'b'){
            cout << "You've decided to rest a little..." << endl << endl;
            player.restoreHealth(25);
            cout << "You've restored health." << endl << endl;
        }
        //if the player decides to run away...
        else if(choice == 'C' || choice == 'c'){
            if(rand() % 100 + 1 <= 50){
                cout << "You've successfully ran away." << endl << endl;
                return;
            }
            else {
                cout << "You couldn't escape!" << endl << endl;
            }
        }
        else {
            cout << "Invaild input. Try again." << endl << endl;
            continue; //Skip the monster's turn.
        }

        //check if the monster has been defeated
        if (monster.get_health() <= 0){
            cout << "You slayed the " << (monster.isElite() ? "Minotaur" : "creature") << " and aquired loot." << endl << endl;

            //If the monster is an elite, drop rarer loot
            if(monster.isElite()){
                player.addLoot(getRareLoot());
            }
            else {
                player.addLoot(getRandomLoot());
            }
            return;
        }

        //Monster's turn
        cout << "The " << (monster.isElite() ? "Minotaur" : "creature") << " takes its turn and attacks." << endl;
        int monsterDmg = monster.get_attack();

        player.setHP(player.getHP() - monsterDmg);
        cout << "The " << (monster.isElite() ? "Minotaur" : "creature") << " dealt " << monsterDmg << " damage to you." << endl << endl;

        //Check if the player is alive or not
        if(player.getHP() <= 0){
            cout << "You've been killed by the " << (monster.isElite() ? "guardian" : "creature") << " of the labyrinth." << endl;
            return;
        }

        //Display the updated stats
        cout << "Monster HP:" << monster.get_health() << endl << endl;
        cout << "Player HP:" << player.getHP() << endl;
    }

    monster.set_health(initialHealth);
}

//function for handling event encounters and occurrences
void Adventure::eventEncounter(Player& player, Elite& elite, Event& regular){
    int occurrence = rand() % 3 + 1;
    int eliteChance = rand() % 100 + 1;
    
    // Initialize variables before use
    char choice;
    Loot treasure;  // Used for case 2
    
    switch(occurrence){
        //monster occurrence
        case 1: 
            //20% chance for regular monster occurrence
            //to be elite monster
            if (eliteChance <= 20){
                cout << "You've encountered a minotaur." << endl;
                cout << "It's stronger than a regular monster."<< endl;

                bool validInput = false;

                //Check if the input is valid or not (this is to keep the message 
                //reprompted after invalid inputs)
                while (!validInput) {
                    cout << "Fight(F) or run(R)?" << endl;
                    cin >> choice;

                    if (choice == 'F' || choice == 'f'){
                        validInput = true;
                        Elite newElite;
                        monsterBattle(player, newElite);
                    }
                    else if(choice == 'R' || choice == 'r') {
                        validInput = true;
                        cout << "You ran away successfully." << endl;
                    }
                    else {
                        cout << "Invalid choice. Please enter F to fight or R to run." << endl;
                    }
                }
            } 
            //Regular monster encounter
            else {
                cout << "You've encounted a creature of the labyrinth." << endl;

                //Same logic as elite monster encounter
                bool validInput = false;
                while (!validInput) {
                    cout << "Fight(F) or run(R)?" << endl;
                    cin >> choice;

                    if (choice == 'F' || choice == 'f'){
                        validInput = true;
                        Event newMonster;
                        monsterBattle(player, newMonster);
                    }
                    else if (choice == 'R' || choice == 'r'){
                        validInput = true;
                        cout << "You ran away." << endl;        
                    }
                    else {
                        cout << "Invalid choice. Please enter F to fight or R to run." << endl;
                    }
                }
            }   
            break;  

        //Treasure chest occurrence (gives one random item)
        case 2: 
            cout << "You've encountered a treasure chest." << endl;
            treasure = getRandomLoot();  
            treasure.displayLoot();
            player.addLoot(treasure);
            break;

        //Oasis occurrence (heals the player)
        case 3: 
            cout << "You've encounter an oasis." << endl;
            player.restoreHealth(20);
            break;
    }
}

// Boss encounter logic
void Adventure::bossEncounter(Player& player, Event& boss) {
    cout << "A powerful boss appears!" << endl;
    cout << "You've entered a battle with the Labyrinth Keeper." <<  endl;
    cout << "Boss HP:" << boss.get_health() << endl << endl;
    cout << "Player HP:" << player.getHP() << endl;

    int initialHealth = boss.get_health();

    char choice;

    //a choice can be made if the player and boss are still alive
    while (player.getHP() > 0 && boss.get_health() > 0){
        //Player goes first
        cout << "It is your turn. What will you do?" << endl;
        cout << "A. Attack" << endl;
        cout << "B. Rest" << endl;
        cout << "C. Flee" << endl;
        cin >> choice;

        //If the player attacks, reduce the boss's health based
        // on the player's attack
        if(choice == 'A' || choice == 'a'){
            int damage = player.getATK();
            cout << "You dealt " << damage << " damage to it." << endl << endl;
            boss.set_health(boss.get_health() - damage);
        }
        //if the player decides to rest, they restore health
        else if(choice == 'B' || choice == 'b'){
            cout << "You've decided to rest a little..." << endl << endl;
            player.restoreHealth(50);
            cout << "You've restored health." << endl << endl;
        }
        //if the player decides to run away...
        else if(choice == 'C' || choice == 'c'){
            cout << "You've successfully ran away." << endl << endl;
            return;
        }
        else {
            cout << "Invaild input. Try again." << endl << endl;
            continue; //Skip the boss's turn.
        }

        //check if the boss has been defeated
        if (boss.get_health() <= 0){
            cout << "You slayed the Labyrinth Keeper and aquired loot." << endl << endl;
            player.addLoot(getRareLoot());
            return;
        }

        //Boss's turn
        cout << "The Labyrinth Keeper takes its turn and attacks." << endl;
        int bossDmg = boss.get_attack();

        player.setHP(player.getHP() - bossDmg);
        cout << "The Labyrinth Keeper dealt " << bossDmg << " damage to you." << endl << endl;

        //Check if the player is alive or not
        if(player.getHP() <= 0){
            cout << "You've been killed by the Labyrinth Keeper." << endl;
            return;
        }

        //Display the updated stats
        cout << "Boss HP:" << boss.get_health() << endl << endl;
        cout << "Player HP:" << player.getHP() << endl;
    }

    boss.set_health(initialHealth);
}

//Center of labyrinth
void Adventure::mazeCenter(){
    cout << "You've reached the center of the labyrinth." << endl;
    cout << "A statue stands before you. It gazes upon you." << endl;
    cout << "You walk closer to it. As you walk, you stumble upon a rusted treasure chest." << endl;
    cout << "You feel a dark presence emitting from the chest." << endl;
    cout << "Would you like to open it? Yes(Y) or No(N)?" << endl;

    char choice;
    cin >> choice;

    if(choice == 'Y' || choice == 'y'){
        bool hasKey = player.hasItem("Rusted Key");

        //If the player has a Rusted Key, open the chest
        //otherwise do not open it
        if(hasKey){
            cout << "You unlocked the chest and obtained a..." << endl;
            cout << "marble?" << endl;

            Loot marble("Marble", "Unknown", 0, 0, false, false);
            player.addLoot(marble);
            player.removeLoot("Rusted Key");

            cout << "After opening the chest, you've decided to continue your journey in the labyrinth." << endl;
        }
        else {
            cout << "You don't have a key to open it..." << endl;
        }
    }
    else if (choice == 'N' || choice == 'n'){
        cout << "You've refused to open the chest." << endl;
        cout << "You decided to continue your journey through the labyrinth." << endl;
    }
    else {
        cout << "Invalid input. Try again." << endl;
    }
}

//The final room
void Adventure::finalRoom(){
    cout << "You stumble upon a crack of light from one of the walls." << endl;
    cout << "Upon interacting with it, you realize it's a portal." << endl;
    cout << "Would you like to leave and end your journey? Yes(Y) or No(N)?" << endl;

    char choice;
    cin >> choice;

    if(choice == 'Y' || choice == 'y'){
        //Ending 2
        if(player.hasItem("???")){
            cout << "You manage to fit through the crack and went through the portal." << endl;
            cout << "Upon going through the portal, you've been teleported to an unusual place." << endl;
            cout << "Looking around you find yourself in a barren wasteland." << endl;
            cout << "The trees are dead, the sky is grim, and bones are scattered everywhere." << endl;
            cout << "You felt despair and felt lost. You felt that after all the struggle, you wounded up in a place with nothing left." << endl;
            cout << "\n Ending 2: Despair" << endl;
            exit(0);
        } 
        //Ending 1
        else {
            cout << "You manage to fit through the crack and went through the portal." << endl;
            cout << "Upon going through the portal, you've been teleported to an empty grass field." << endl;
            cout << "After the countless challenges you've faced, you finally felt free." << endl;
            cout << "No more, shall you fight in that dark, endless labyrinth." << endl;
            cout << "You lay on the grass and let the sun shine on your skin." << endl;
            cout << "You think to yourself, \"It's finally over. I am free. \" " << endl;
            cout << "Or are you?" << endl << endl;

            cout << "Ending 1: Labyrinth Conqueror" << endl;
            exit(0);
        } 
    }
    else if(choice == 'N' || choice == 'n'){
        cout << "You refused to leave and continued to wander the endless labyrinth." << endl;

    }
    else {
        cout << "Invalid choice. Try again." << endl;
    }
}