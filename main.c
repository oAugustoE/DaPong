#include "Render/render.h"
#include "Game/Game.h"
#include <stdio.h>


int main(void) {

    render_menu();
    int winner = Game();
    render_winner(winner);

    return 0;
}
