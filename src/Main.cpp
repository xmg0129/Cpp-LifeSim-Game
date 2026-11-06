#include "../include/common.h"
#include "../include/game.h"

int main() {
    Game game;
    game.randomFamily();
    while(menu(game)) {
        if(game.player.getDead()) return 0;
    }
}
