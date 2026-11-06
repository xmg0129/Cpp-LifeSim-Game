#include "../include/common.h"
#include "../include/bank.h"
#include "../include/player.h"

void Bank::deposit(double amount,Player& player) {
    if(amount <= 0) {
        std::cout << "金额错误存款失败" << std::endl;
        return;
    }
    if(player.getMoney() < amount) {
        std::cout << "余额不足存款失败" << std::endl;
        return;
    }
    player.spendMoney(amount);
    balance += amount;
    std::cout << "存款成功" << std::endl;
}
void Bank::withdraw(double amount,Player& player) {
    if(amount <= 0) {
        std::cout << "金额错误取款失败" << std::endl;
        return;
    }
    if(balance < amount) {
        std::cout << "余额不足取款失败" << std::endl;
        return;
    }
    player.earnMoney(amount);
    balance -= amount;
    std::cout << "取款成功" << std::endl;
}
void Bank::checkBalance() {
    std::cout << "当前余额为:" << balance << std::endl;
}
void Bank::dailyInterest() {
    balance += balance * interestRate;
}
double Bank::getBalance() {
    return balance;
}
void Bank::setBalance(double amount) {
    balance = amount;
}
