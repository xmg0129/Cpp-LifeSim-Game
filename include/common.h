#ifndef COMMON_H
#define COMMON_H

/* ====== 头文件区 ====== */
#include <iostream>
#include <string>
/* ====== 函数/类声明区 ======*/
class Game;
class Backpack;
class Bank;
class Player;
bool menu(Game& game);

/* ====== 版本常量 ====== */
const std::string VERSION_PREFIX = "Alpha";
const std::string VERSION_NUM = "22";
const std::string VERSION_DISPLAY = "Alpha 0.22";
const std::string SERVER_API = "https://github.com/xmg0129/Cpp-LifeSim-Game/version.txt";
const std::string SERVER = "https://github.com/xmg0129/Cpp-LifeSim-Game";

#endif