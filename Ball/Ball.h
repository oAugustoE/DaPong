//
// Created by augusto on 8/26/26.
//

#ifndef DAPONG_BALL_LOGIC_H
#define DAPONG_BALL_LOGIC_H

#include "../Player/player.h"

typedef struct {
    double x;
    double y;
    double dx;
    double dy;
} Ball;

void gen_ball(Ball *ball);
int ball_logic(Ball *ball, const  Player *player, const Player *player2);

#endif //DAPONG_BALL_LOGIC_H
