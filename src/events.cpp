#include "../include/common.h"
#include "../include/game.h"
#include "../include/random.h"
#include <unistd.h>

bool menu(Game& game) {
    bool running = true;
    std::string input;
    std::cout << "当前版本为:" << VERSION_DISPLAY << std::endl;
    do {
        running = game.player.checkGoal();
        if(!running)
        {
            return false;
        }
        
        std::cout
                << "当前余额:" << game.player.getMoney() << "元人民币" << std::endl
                << "当前血量:" << game.player.getHp() << "/100" << std::endl
                << "当前饥饿值:" << game.player.getHunger() << "/100 当前口渴值:" << game.player.getThirst() << "/100" << std::endl
                << "当前心情:" << game.player.getMood() << "/100" << std::endl
                << "当前天数第:" << game.player.getDays() << "天" << std::endl
                << "1.打工(日结)" << std::endl
                << "2.查看背包内物品" << std::endl
                << "3.丢掉背包内物品" << std::endl
                << "4.购买物品" << std::endl
                << "5.使用物品" << std::endl
                << "6.结束一天" << std::endl
                << "7.购买彩票" << std::endl
                << "8.保存存档" << std::endl
                << "9.加载存档" << std::endl
                << "10.检查更新" << std::endl
                << "11.存款" << std::endl
                << "12.取款" << std::endl
                << "13.查询余额" << std::endl
                << "14.去酒吧喝两杯" << std::endl
                << "0.退出" << std::endl;
        std::cin >> input;
        if(input == "1")
        {
            game.player.earnMoney(game.work());
        }
        else if(input == "2")
        {
            game.backpack.show();
        }
        else if(input == "3")
        {
            game.backpack.show();
            game.backpack.discard();
        }
        else if(input == "4")
        {
            game.backpack.buyMenu(game.player);
        }
        else if(input == "5")
        {
            game.backpack.useMenu(game.player);
        }
        else if(input == "6")
        {
            std::cout << "第" << game.player.getDays() << "天结束了" << std::endl;
            if(game.player.getMood() == 0 && randomBool()) {
                std::cout << "你心情极差，由于在过马路的时候没注意到有车经过，导致被撞伤了由于你在过马路的时候闯了红灯导致你全责，";
                if(game.player.getMoney() >= 15000) {
                    std::cout << "扣除15000元人民币" << std::endl;
                    game.player.spendMoney(15000);
                } else {
                    std::cout << "因为你承担不起15000元人民币的手术费，所以扣除血量70" << std::endl;
                    game.player.spendHp(70);
                }
            } else if(game.player.getMood() <= 15 && randomBool()) {
                std::cout << "因为你心情很不好，没注意看路，所以不小心摔了一跤，导致血量减少25" << std::endl;
                game.player.spendHp(25);
            } else if(game.player.getMood() <= 30 && randomBool()) {
                std::cout << "你心情烦躁，不小心把钱包落在了公交车上损失500元" << std::endl;
                game.player.spendMoney(500);
            }
            if(game.player.getHunger() >= 30)
            {
                std::cout << "饥饿值 - 30"<< std::endl;
                game.player.spendHunger(30);
            }
            else
            {
                std::cout << "由于饥饿值不足30所以扣除血量15" << std::endl;
                game.player.spendHp(15);
            }
            if(game.player.getThirst() >= 30)
            {
                std::cout << "口渴值 - 30"<< std::endl;
                game.player.spendThirst(30);
            }
            else
            {
                std::cout << "由于口渴值不足30所以扣除血量50" << std::endl;
                game.player.spendHp(50);
            }
            game.bank.dailyInterest();
            game.player.earnDays();
            game.player.earnMood(3);
            game.nextDay();
            sleep(1);
        }
        else if(input == "7")
        {
            if(!game.getLotteryCd())
            {
                game.lottery();
            }
            else
            {
                std::cout << "今日已经买过一次了，请明日再来" << std::endl;

            }

        }
        else if(input == "8")
        {
            game.saveGame();
        }
        else if(input == "9")
        {
            game.loadGame();
        }
        else if(input == "10")
        {
            if(game.sendVersion() == true) {
                std::cout << "发现新版本请前往:" << SERVER << "下载" << std::endl;
            }
            else
            {
                std::cout << "未发现新版本" << std::endl;
            }
        }
        else if(input == "11")
        {
            long amount = 0;
            std::cout << "请输入存款金额" << std::endl;
            std::cin >> amount;
            game.bank.deposit(amount,game.player);
        }
        else if(input == "12")
        {
            long amount = 0;
            std::cout << "请输入取款金额" << std::endl;
            std::cin >> amount;
            game.bank.withdraw(amount,game.player);
        }
        else if(input == "13")
        {
            game.bank.checkBalance();
        }
        else if(input == "14") {
            if(game.player.getMoney() >= 200) {
                game.player.spendMoney(200);
                std::cout << "你在酒吧喝了两杯，心情好多了，花费200心情加5" << std::endl;
                game.player.earnMood(5);
            } else {
                std::cout << "余额不足，连酒都喝不起了..." << std::endl;
                game.player.spendMood(2);
            }
        }
        else if(input == "0")
        {
            std::cout << "已退出" << std::endl;
            return false;
        }
        else
        {
            std::cout << "错误!" << std::endl;
        }
        if(game.player.getDead())
        {
            return false;
        }

    }
    while(running);
    return false;
}