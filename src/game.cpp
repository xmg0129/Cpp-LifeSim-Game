#include "../include/common.h"
#include "../include/game.h"
#include "../include/player.h"
#include "../include/bank.h"
#include "../include/backpack.h"
#include "../include/random.h"
#include "../include/json.hpp"
#include <curl/curl.h>
#include <fstream>
#include <unistd.h>
#include <cstdio>

int Game::work() {
    int a = random(400,600);
    std::cout << "工作中···" << std::endl;
    sleep(random(1,2));
    std::cout << "工作了一天您赚到了:" << a << "元人民币" << std::endl;
    if(player.getHunger() >= 35)
    {
        std::cout << "饥饿值 - 35"<< std::endl;
        player.spendHunger(35);
    }
    else
    {
        std::cout << "由于饥饿值不足35所以扣除血量15" << std::endl;
        player.spendHp(15);
    }
    if(player.getThirst() >= 35)
    {
        std::cout << "口渴值 - 35"<< std::endl;
        player.spendThirst(35);
    }
    else
    {
        std::cout << "由于口渴值不足35所以扣除血量50" << std::endl;
        player.spendHp(50);
    }
    player.spendMood(7);
    return a;
}

void Game::familyResult(std::string m,int z) {

    std::cout
            << "你出生了" << std::endl
            << "你是个男孩" << std::endl
            << "你的家境" << m << std::endl
            << "很快你成年了家里给了你一笔钱" << std::endl
            << "总共:" << z << "元人民币" << std::endl << std::endl;
    player.earnMoney(z);

}
bool Game::getLotteryCd() {
    return lotteryCd;
}
void Game::randomFamily() {
    int a = random(1,100);
    int n1 = 15;
    int n2 = 50;
    int n3 = 85;
    int z1;
    std::string m1;
    if (a <= n1)
    {
        m1 = "贫穷";
        z1 = random(200,800);
        familyResult(m1,z1);
    }
    else if(a <= n2)
    {
        m1 = "普通";
        z1 = random(800,1500);
        familyResult(m1,z1);
    }
    else if(a <= n3)
    {
        m1 = "小康";
        z1 = random(2000,3000);
        familyResult(m1,z1);
    }
    else
    {
        m1 = "富裕";
        z1 = random(4000,5000);
        familyResult(m1,z1);
    }


}
void Game::nextDay() {
    lotteryCd = false;
    randomEvent();
}
bool Game::sendVersion() {
    CURL* curl = curl_easy_init();
    if (!curl) return false;

    std::string body;
    curl_easy_setopt(curl, CURLOPT_URL, SERVER_API.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,
        +[](void* data, size_t size, size_t nmemb, void* userp) -> size_t {
            auto* out = static_cast<std::string*>(userp);
            out->append(static_cast<char*>(data), size * nmemb);
            return size * nmemb;
        });
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &body);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK) return false;

    while (!body.empty() && (body.back() == '\n' || body.back() == '\r'))
        body.pop_back();

    return body != VERSION_DISPLAY;
}
void Game::randomEvent() {
    int ra = random(1,100);
    if(ra == 1)
    {
        std::cout << "你运气超好在路边免费抽奖抽中了10万元" << std::endl;
        player.earnMoney(100000);
        player.earnMood(7);
    }
    else
    {
        switch(ra)
        {
              case 2:
              case 3:
              case 4:
              case 5:
              case 6:
                  std::cout << "你走在马路上，捡到了100块钱" << std::endl;
                  player.earnMood(1);
                  player.earnMoney(100);
                  break;
              case 7:
              case 8:
              case 9:
              case 10:
                  std::cout << "你一出门就踩到了一坨狗屎，你觉得倒霉透了" << std::endl;
                  player.spendMood(1);
                  break;
              case 11:
              case 12:
              case 13:
              case 14:
              case 15:
              case 16:
                  std::cout << "你走在马路上，突然被一颗石子绊倒了";
                  player.spendMood(1);
                  if(player.getMoney() == 0)
                  {
                      std::cout << "因为你没有钱买创可贴所以减少5的血量" << std::endl;
                      player.spendHp(5);
                  }
                  else
                  {
                      std::cout << "去药店买了个创可贴花费5元" << std::endl;
                      player.spendMoney(5);
                  }
                  break;
              case 17:
              case 18:
              case 19:
              case 20:
                  std::cout << "你刚一回到家，就发现自己的钱包不见了扣除500块" << std::endl;
                  player.spendMood(3);
                  player.spendMoney(500);
                  break;
              default:
                  std::cout << "今天无事发生" << std::endl;
                  break;
        }
    }
}

using json = nlohmann::json;

void Game::saveGame() {
    json j;
    json bag = json::object();
    
    j["Money"] = player.getMoney();
    j["days"] = player.getDays();
    j["hp"] = player.getHp();
    j["hunger"] = player.getHunger();
    j["thirst"] = player.getThirst();
    j["lotteryCd"] = lotteryCd;
    j["balance"] = bank.getBalance();
    j["mood"] = player.getMood();
    
    for (const auto& item : backpack.getAllItems()) {
        bag[item.first] = item.second;
    }
    j["backpack"] = bag;
    
    std::ofstream f("saveGame.json");
    f << j.dump(4);
    f.close();
    
/*    std::ofstream file("saveGame.txt");
    if(!file) {
        std::cout << "保存失败" << std::endl;
        return;
    }
    file << player.getMoney() << "\n";
    file << player.getDays() << "\n";
    file << player.getHp() << "\n";
    file << player.getHunger() << "\n";
    file << player.getThirst() << "\n";
    file << lotteryCd << "\n";
    file << bank.getBalance() << "\n";
    file<< player.getMood() << "\n";
    for (const auto& item : backpack.getAllItems()) {
        file << item.first << " " << item.second << "\n";
    }
    file.close();*///让我试试这个库好不好使
    std::cout << "游戏已保存！" << std::endl;
}
void Game::loadGame() {
    json j;
    
    std::ifstream file("saveGame.json");
    
    if(!file) {
        std::cout << "未发现存档" << std::endl;
        return;
    }
    
    try {
        file >> j;
    } catch(...) {
        std::cout << "存档读取失败，该存档无法使用-_-" << std::endl;
        return;
    }
    
    player.setMoney(j.value("Money", 0));
    player.setDays(j.value("days", 0));
    player.setHp(j.value("hp", 100));
    player.setHunger(j.value("hunger", 100));
    player.setThirst(j.value("thirst", 100));
    lotteryCd = j.value("lotteryCd", false);
    bank.setBalance(j.value("balance", 0));
    player.setMood(j.value("mood", 100));
    
    backpack.clear();
    if(j.contains("backpack") && j["backpack"].is_object()) {
        for (auto& [name, count] : j["backpack"].items()) {
            backpack.addItem(name, count.get<int>());
        }
    }
    
    j["version"] = VERSION_DISPLAY;
    
    /*if(!file)
    {
        std::cout << "未发现存档" << std::endl;
        return;
    }
    long long Money, days;
    int hp, hunger, thirst, mood;
    bool lottery;
    double balance;
    file >> Money >> days >> hp >> hunger >> thirst >> lottery >> balance >> mood;
    player.setMoney(Money);
    player.setDays(days);
    player.setHp(hp);
    player.setHunger(hunger);
    player.setThirst(thirst);
    lotteryCd = lottery;
    bank.setBalance(balance);
    player.setMood(mood);
    backpack.clear();
    std::string name;
    int count;
    while (file >> name >> count) {
        backpack.addItem(name, count);
    }*/
    file.close();
    std::cout << "读取存档成功！" << std::endl;
}

void Game::lottery()
{
    int a = random(1,20);
    long long b = 5000000;
    int input;
    std::string input2;
    bool mnl = true;
    bool mnl2 = true;
    std::cout << "彩票奖金为:500万元人民币" << std::endl;
    while (mnl2)
    {
        std::cout << "当前余额:" << player.getMoney() << "元人民币" << std::endl;
        std::cout << "购买彩票需花费500元人民币" << std::endl;
        std::cout << "是否购买(y/n):";
        std::cin >> input2;
        if(input2 == "y")
        {
            if(player.getMoney() >= 500)
            {
                player.spendMoney(500);

                std::cout << "购买成功!" << std::endl;
                player.earnMood(1);
                lotteryCd = true;

                while (mnl)
                {
                    std::cout << "请输入您选择的号码(1-20):";

                    std::cin >> input;
                    if(input >= 1 && input <= 20)
                    {
                        mnl = false;
                        break;
                    }
                    else
                    {
                        std::cout << "错误请重新输入" << std::endl;
                    }

                }

                sleep(1);
                if(input == a)
                {
                    std::cout << "恭喜您!您中奖"<< std::endl;
                    player.earnMoney(b);
                    player.earnMood(20);
                    mnl2 = false;
                    break;
                }
                else
                {
                    std::cout << "很遗憾的告诉您!未中奖" << std::endl;
                    mnl2 = false;
                    break;
                }
            }
            else
            {
                std::cout << "余额不足" << std::endl;
                mnl2 = false;
                break;
            }
        }
        else if(input2 == "n")
        {
            std::cout << "已取消" << std::endl;
            mnl2 = false;
            break;
        }
        else
        {
            std::cout << "错误请重新输入 "<< std::endl;
        }

    }

}
