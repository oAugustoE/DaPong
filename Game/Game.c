//
// Created by augusto on 8/27/26.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "../Ai/Ai.h"
#include "../Ball/Ball.h"
#include "../Canvas/Canvas.h"
#include "../Player/player.h"
#include "../Input/Input.h"
#include "../Render/render.h"
#include "../config//config.h"

int Game(int type) {
    int GameRunning = 1;

    srand(time(NULL));

    Canvas canvas;
    Ball ball;
    Player player;
    Player player2;

    gen_ball(&ball);
    gen_player(&player, '1');
    gen_player(&player2, '2');
    gen_canvas(&canvas);
    set_conio_mode();
    printf("\033[2J");

    while (GameRunning) {
        player_logic(&player, &player2, type);
        if (type == 0) {
            Ai(&ball, &player2);
        }
        printf("\033[H");
        render_canvas(&canvas, &ball, &player, &player2);

        int resultado = ball_logic(&ball, &player, &player2);

        if (resultado != 0) {
            return resultado;
        }



        usleep(TICK_SPEED);
    }

    return 0;
}
