#include "../include/common.h"
#include "../include/backpack.h"
#include "../include/player.h"

const std::unordered_map<std::string, int>& Backpack::getAllItems() const {
    return packet;
}

void Backpack::clear() {
    packet.clear();
}

void Backpack::addItem(const std::string& name, int count) {
    packet[name] = count;
}
Backpack::Backpack() {
    packet["手机"] = 0;
    packet["面包"] = 2;
    packet["矿泉水"] = 2;
    packet["药品"] = 1;
    packet["饮料"] = 0;
    packet["牛肉干"] = 0;
    packet["水果"] = 5;
}

void Backpack::discard() {
    std::string name;
    int count = 1;
    std::cout << "请输入你要丢弃的物品(格式:名称 数量)" << std::endl;
    std::cin >> name >> count;

    auto it = packet.find(name);

    if (it == packet.end()) {
        std::cout << "背包中没有" << name << std::endl;
    } else if (it->second < count) {
        std::cout << "数量不足！只有 " << it->second << " 个" << std::endl;
    } else if (count < 0) {
        std::cout << "错误！请勿输入负数" << std::endl;
    } else {
        it->second -= count;
        std::cout << "已丢出 " << count << " 个" << name << std::endl;
        if (it->second == 0) packet.erase(it);
    }
}
void Backpack::show() {
    if(!packet.empty())
    {
        std::cout << "你当前背包内的物品:" << std::endl;
        for(auto& sy : packet) {
            std::cout << sy.first << "x" << sy.second << std::endl;
        }
    }
    else
    {
        std::cout << "你的背包是空的" << std::endl;
    }

}

void Backpack::buyMenu(Player& player) {
    std::string input;
    bool a = true;
    do {
        std::cout << "\n当前余额:" << player.getMoney() << "元人民币" << std::endl;
        std::cout << "请选择您要购买的物品:" << std::endl;
        std::cout << "1.手机 1399 元" << std::endl;
        std::cout << "2.面包 6 元" << std::endl;
        std::cout << "3.矿泉水 2 元" << std::endl;
        std::cout << "4.药品 35 元" << std::endl;
        std::cout << "5.饮料 4 元" << std::endl;
        std::cout << "6.牛肉干 40 元" << std::endl;
        std::cout << "7.水果 12 元" << std::endl;
        std::cout << "0.退出\n" << std::endl;
        std::cin >> input;
        if(input == "1")
        {
            buyItem(1399,"手机",player);
        }
        else if(input == "2")
        {
            buyItem(6,"面包",player);
        }
        else if(input == "3")
        {
            buyItem(2,"矿泉水",player);
        }
        else if(input == "4")
        {
            buyItem(35,"药品",player);
        }
        else if(input == "5")
        {
            buyItem(4,"饮料",player);
        }
        else if(input == "6")
        {
            buyItem(40,"牛肉干",player);
        }
        else if(input == "7")
        {
            buyItem(12,"水果",player);
        }
        else if(input == "0")
        {
            std::cout << "已退出" << std::endl;
            a = false;
            break;
        }
        else
        {
            std::cout << "错误!" << std::endl;
        }
    }
    while(a);

}

void Backpack::buyItem(int price,std::string name,Player& player) {
    if(player.getMoney() >= price)
    {

        std::cout << "购买成功!" << std::endl;
        packet[name] += 1;
        player.spendMoney(price);
        if(name == "手机") {
            player.earnMood(2);
        }
    }
    else
    {
        std::cout << "余额不足!" << std::endl;
    }

}


bool Backpack::useItem(std::string name,Player& player) {
    auto it = packet.find(name);
    if (it == packet.end() || it->second <= 0) {
        std::cout << "没有这个物品！" << std::endl;
        return false;
    }
    else
    {
        if(name == "面包")
        {
            std::cout << "美味 饥饿值 + 60 面包 - 1" << std::endl;
            packet[name] -= 1;
            player.earnHunger(60);
        }
        else if(name == "手机")
        {
            std::cout << "你拿起手机打开游戏当打手带着老板千万撤离 hp - 5 Money + 300 心情 - 2" << std::endl;
            player.spendHp(5,true);
            player.earnMoney(200);
            player.spendMood(5);
            if(player.getDead())
            {
                return false;
            }
        }
        else if(name == "药品")
        {
            std::cout << "药很苦但你很快就恢复了健康 hp = 100 药品 - 1" << std::endl;
            packet[name] -= 1;
            player.earnHp(100);
        }
        else if(name == "矿泉水")
        {
            std::cout << "只是普通的水而已 口渴值 + 60" << std::endl;
            packet[name] -= 1;
            player.earnThirst(60);
        }
        else if(name == "饮料")
        {
            std::cout << "非常的好喝 口渴值 + 40 饮料 - 1" << std::endl;
            packet[name] -= 1;
            player.earnThirst(40);
        }
        else if(name == "牛肉干")
        {
            std::cout << "非常的好吃 饥饿值 + 50 牛肉干 - 1" << std::endl;
            packet[name] -= 1;
            player.earnHunger(50);
        }
        else
        {
            std::cout << "非常的好吃 饥饿值 + 25 水果 - 1" << std::endl;
            packet[name] -= 1;
            player.earnHunger(25);
        }
        
    }
    return true;
    
}

void Backpack::useMenu(Player& player) {
    if(packet.empty())
    {
        std::cout << "背包是空的没有物品可用" << std::endl;
        return;
    }
    std::string input;
    bool exitMenu = true;
    do{
        std::cout << "请选择您要使用的物品:" << std::endl;
        std::cout << "1.手机" << std::endl;
        std::cout << "2.面包" << std::endl;
        std::cout << "3.矿泉水" << std::endl;
        std::cout << "4.药品" << std::endl;
        std::cout << "5.饮料" << std::endl;
        std::cout << "6.牛肉干" << std::endl;
        std::cout << "7.水果" << std::endl;
        std::cout << "0.退出\n" << std::endl;
        std::cin >> input;
        if(input == "1")
        {
            exitMenu = useItem("手机",player);
        }
        else if(input == "2")
        {
            useItem("面包",player);
        }
        else if(input == "3")
        {
            useItem("矿泉水",player);
        }
        else if(input == "4")
        {
            useItem("药品",player);
        }
        else if(input == "5")
        {
            useItem("饮料",player);
        }
        else if(input == "6")
        {
            useItem("牛肉干",player);
        }
        else if(input == "7")
        {
            useItem("水果",player);
        }
        else if(input == "0")
        {
            std::cout << "已退出" << std::endl;
            exitMenu = false;
            return;
        }
        else
        {
            std::cout << "错误请重新输入" << std::endl;
        }
        
    }while(exitMenu);
    
}
