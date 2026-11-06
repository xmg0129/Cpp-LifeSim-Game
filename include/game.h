#ifndef GAME_H
#define GAME_H
#include "common.h"
#include "player.h"
#include "backpack.h"
#include "bank.h"

class Game {
private:
    bool lotteryCd = false;
    void familyResult(std::string m,int z);
    void randomEvent();
public:
    Bank bank;
    Player player;
    Backpack backpack;
    int work();
    void randomFamily();
    bool getLotteryCd();
    void lottery();
    void nextDay();
    void saveGame();
    void loadGame();
    bool sendVersion();
};

#endif