//
// Created by augusto on 8/26/26.
//

#ifndef DAPONG_BALL_LOGIC_H
#define DAPONG_BALL_LOGIC_H

#include "../Player/player.h"

typedef struct {
    int x;
    int y;
    int dx;
    int dy;
} Ball;

void gen_ball(Ball *ball);
int ball_logic(Ball *ball, const  Player *player, const Player *player2);

#endif //DAPONG_BALL_LOGIC_H
