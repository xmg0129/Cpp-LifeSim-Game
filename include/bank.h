#ifndef BANK_H
#define BANK_H
#include "common.h"

class Bank {
private:
    double balance = 0.0;
public:
    const double interestRate = 0.00025;
    void deposit(double amount,Player& player);
    void withdraw(double amount,Player& player);
    void checkBalance();
    void dailyInterest();
    double getBalance();
    void setBalance(double amount);
};

#endif