#include <stdlib.h>
#include "Ball.h"

#include "../Player/player.h"
#include "../config/config.h"

double max_ball_speed = 1.0;

void gen_ball(Ball *ball) {
    ball->x = CANVAS_WIDTH / 2;
    ball->y = CANVAS_HEIGHT / 2;
    ball->dx = (rand() % 2 == 0) ? -max_ball_speed : max_ball_speed;
    ball->dy = (rand() % 3) - 1;
}

int ball_logic(Ball *ball, const Player *player, const Player *player2) {
    if (ball->y <= 1) {
        ball->y = 1;
        ball->dy = -ball->dy;
    }

    if (ball->y >= CANVAS_HEIGHT - 2) {
        ball->y = CANVAS_HEIGHT - 2;
        ball->dy = -ball->dy;
    }
    if (ball->dx < 0 && ball->x <= player->x + 1 &&
        ball->x >= player->x && ball->y >= player->y &&
        ball->y < player->y + player->length) {
        ball->x = player->x + 1;
        ball->dx = max_ball_speed;
        ball->dy = (rand() % 3) - 1;
        }

    if (ball->dx > 0 && ball->x >= player2->x - 1 &&
        ball->x <= player2->x && ball->y >= player2->y &&
        ball->y < player2->y + player2->length) {

        ball->x = player2->x - 1;
        ball->dx = -max_ball_speed;

        ball->dy = (rand() % 3) - 1;
        }
    if (ball->x <= 0) {
        return 2;
    }
    if (ball->x >= CANVAS_WIDTH - 1) {
        return 1;
    }
    ball->x += ball->dx;
    ball->y += ball->dy;

    return 0;
}