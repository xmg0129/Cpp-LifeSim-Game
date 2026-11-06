#ifndef BACKPACK_H
#define BACKPACK_H
#include "common.h"
#include <unordered_map>

class Backpack {
private:
    std::unordered_map<std::string, int> packet;
    void buyItem(int price,std::string name,Player& player);
    bool useItem(std::string name,Player& player);
public:
    Backpack();
    void discard();
    void show();
    void buyMenu(Player& player);
    void useMenu(Player& player);
    const std::unordered_map<std::string, int>& getAllItems() const;
    void clear();
    void addItem(const std::string& name, int count);
};

#endif