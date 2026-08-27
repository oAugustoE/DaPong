#include <stdlib.h>
#include "Ball.h"
#include "../Player/player.h"

#include "../config/config.h"



void gen_ball(Ball *ball) {
    ball->x = CANVAS_WIDTH / 2;
    ball->y = CANVAS_HEIGHT / 2;
    ball->dx = (rand() % 2) ? 1 : -1;
    ball->dy = (rand() % 2) ? 1 : -1;
}

int ball_logic(Ball *ball, const  Player *player, const Player *player2) {
    if (ball->y <= 1 || ball->y >= CANVAS_HEIGHT - 2) {
        ball->dy *= -1;
    }

    if (ball->dx < 0 &&
        ball->x == player->x + 1 &&
        ball->y >= player->y &&
        ball->y < player->y + player->length) {
        ball->dx = 1;
        }

    if (ball->dx > 0 &&
        ball->x == player2->x - 1 &&
        ball->y >= player2->y &&
        ball->y < player2->y + player2->length) {
        ball->dx = -1;
        }

    if (ball->x <= 1) {
        return 2;
    }

    if (ball->x >= CANVAS_WIDTH - 2) {
        return 1;
    }

    ball->x += ball->dx;
    ball->y += ball->dy;

    return 0;
}