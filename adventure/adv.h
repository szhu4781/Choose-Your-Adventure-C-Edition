#ifndef ADV_H
#define ADV_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "boss.h"
#include "event.h"
#include "elite.h"
#include "player.h"
#include "loot.h"

class Adventure {
private:
    Player player;  //The player
    int current;    //The current event
    bool openInv;   //Opened inventory
    bool openMenu;
    Elite elite;    
    Event regular;
    Boss boss;
public:
    //Constructor
    Adventure(int playerHP, int playerATK);

    void startGame();
    void displayRoom() const;
    bool displayInventory();
    bool displayMenu();
    void craftingRoom();
    void handleChoice(char choice);
    void handleEvent();
    bool playerStatus() const;
    void monsterBattle(Player&, Event&);
    void eventEncounter(Player&, Elite&, Event&);
    void bossEncounter(Player&, Event&); 
    void mazeCenter();
    void finalRoom();
};

#endif