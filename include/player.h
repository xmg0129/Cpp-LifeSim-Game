#ifndef PLAYER_H
#define PLAYER_H
#include "common.h"

class Player {
private:
    int hp = 100;
    int maxHp = 100;
    int minHp = 0;
    int hunger = 100;
    int maxHunger = 100;
    int minHunger = 0;
    int thirst = 100;
    int maxThirst = 100;
    int minThirst = 0;
    bool dead = false;
    long long Money = 0;  //因为比较特殊整个游戏都是围绕着他进行的所以就给他大写
    long long days = 0;
    long long targetMoney = 100000000;
    int mood = 50;
    int maxMood = 100;
    int minMood = 0;
public:
    long long getMoney();
    long long getDays();
    int getHp();
    int getHunger();
    void earnHunger(long long amount);
    void spendHunger(long long amount);
    int getThirst();
    void earnThirst(long long amount);
    void spendThirst(long long amount);
    bool checkGoal();
    long long getTargetMoney();
    void setMoney(long long amount);
    void setDays(long long amount);
    void setHp(int amount);
    void setHunger(int amount);
    void setThirst(int amount);
    bool getDead();
    
    int getMood();
    void earnMood(long long amount);
    void spendMood(long long amount);
    void setMood(long long amount);
    
    void die(bool easterEgg);
    void earnMoney(long long amount);
    void earnDays();
    void earnHp(int amount);
    bool spendMoney(long long amount);
    void spendHp(int amount,bool easterEgg = false);
};

#endif