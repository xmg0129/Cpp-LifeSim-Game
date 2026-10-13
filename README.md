[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

# Cpp-LifeSim-Game

- 一个简单的C++人生模拟游戏

## 特别提醒

- 目前仅支持Linux、Android(Termux)、MacOS等环境，暂未适配Windows

## 当前版本

- Alpha 0.22

## 游戏功能

- 打工赚钱
- 背包系统
- 彩票系统
- 天数系统
- 目标系统
- 每日随机事件
- 联网检测版本
- 银行系统

## 快速开始

### 如未安装g++ curl git make请先安装:

#### Android(Termux)环境安装命令:

```bash
pkg install g++ curl git make
```

#### Linux环境安装命令(apt包管理为例):

```bash
sudo apt install g++ curl git make
```

#### MacOS环境安装命令:

```bash
brew install curl git make
xcode-select --install
```
### 克隆仓库

```bash
git clone https://github.com/xmg0129/Cpp-LifeSim-Game.git
cd Cpp-LifeSim-Game
```

### 编译命令：

#### Linux、Android(Termux)环境编译命令:

```bash
make run CXX=g++ CFLAGS=-std=c++17 -j$(nproc)
```

#### MacOS环境编译命令:

```bash
make run CXX=clang++ CFLAGS=-std=c++17 -j$(sysctl -n hw.ncpu)
```

## 运行命令：

- 需要在“Cpp-LifeSim-Game”目录下执行

```bash
make run
```

##

注：本项目开发过程中使用了AI辅助部分代码编写。