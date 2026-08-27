#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


#include "Ball/Ball.h"
#include "Canvas/Canvas.h"
#include "Player/player.h"
#include "Input/Input.h"
#include "Render/render.h"


#define PLAYER_SPEED 1
#define CANVAS_WIDTH 200
#define CANVAS_HEIGHT 15
#define PLAYER_LENGTH 3
#define TICK_SPEED 100000
#define WINNING_TEXT_SIZE 14

int main(void) {
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
        player_logic(&player, &player2);

        printf("\033[H");
        render_canvas(&canvas, &ball, &player, &player2);

        switch (ball_logic(&ball, &player, &player2)) {
            case 1:
                GameRunning = 0;
                render_winner(1);
                break;
            case 2:
                GameRunning = 0;
                render_winner(2);
                break;
            default:
                break;
        }

        usleep(TICK_SPEED);
    }

    return 0;
}