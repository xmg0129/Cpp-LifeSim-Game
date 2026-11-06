#include "../include/common.h"
#include "../include/player.h"

void Player::spendHp(int amount,bool easterEgg) {
    if(hp - amount <= minHp)
    {
        die(easterEgg);
    }
    else
    {
        hp -= amount;
    }
}
void Player::die(bool easterEgg) {
    if(easterEgg)
    {
        std::cout << "您死了!原因:你在打游戏结束后猝死了...游戏结束!" << std::endl;
    }
    else
    {
        std::cout << "您死了!...游戏结束!" << std::endl;
    }
    hp = minHp;
    dead = true;
}
bool Player::getDead() {
    return dead;
}
void Player::earnHp(int amount) {
    if(hp + amount >= maxHp)
    {
        hp = maxHp;
    }
    else
    {
        hp += amount;
    }
}
void Player::setMoney(long long amount) {
    Money = amount;
}
void Player::setDays(long long amount) {
    days = amount;
}
void Player::setHp(int amount) {
    hp = amount;
}
void Player::setHunger(int amount) {
    hunger = amount;
}
void Player::setThirst(int amount) {
    thirst = amount;
}
    
void Player::spendThirst(long long amount) {
    if(thirst - amount >= minThirst)
    {
        thirst -= amount;
    }
    else
    {
        thirst = minThirst;
    }
}
long long Player::getMoney() {
    return Money;
}
long long Player::getDays() {
    return days;
}
long long Player::getTargetMoney() {
    return targetMoney;
}
void Player::earnMoney(long long amount) {
    Money += amount;
}
void Player::earnDays() {
    days += 1;
}
bool Player::spendMoney(long long amount) {
    if (Money >= amount) {
        Money -= amount;
        return true;
    }
    else
    {
        return false;
    }
}
bool Player::checkGoal() {
    if(Money >= targetMoney)
    {
        std::cout << "\n恭喜你!你达成目标"<< std::endl;
        return false;
    }
    else
    {
        return true;
    }

}
int Player::getHp() {
    return hp;
}
int Player::getHunger() {
    return hunger;
}
void Player::earnHunger(long long amount) {
    if(hunger + amount <= maxHunger)
    {
        hunger += amount;
    }
    else
    {
        hunger = maxHunger;
    }
}
void Player::spendHunger(long long amount) {
    if(hunger - amount >= minHunger)
    {
        hunger -= amount;
    }
    else
    {
        hunger = minHunger;
    }
}
int Player::getThirst() {
    return thirst;
}
void Player::earnThirst(long long amount) {
    if(thirst + amount <= maxThirst)
    {
        thirst += amount;
    }
    else
    {
        thirst = maxThirst;
    }
}
int Player::getMood() {
    return mood;
}
void Player::earnMood(long long amount) {
    if(mood + amount <= maxMood)
    {
        mood += amount;
    }
    else
    {
        mood = maxMood;
    }
}
void Player::spendMood(long long amount) {
    if(mood - amount >= minMood)
    {
        mood -= amount;
    }
    else
    {
        mood = minMood;
    }
}
void Player::setMood(long long amount) {
    mood = amount;
}