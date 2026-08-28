#include "Render/render.h"
#include "Game/Game.h"


int main(void) {

    int winner = Game(render_menu());
    render_winner(winner);

    return 0;
}
