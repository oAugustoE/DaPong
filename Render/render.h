//
// Created by augusto on 8/27/26.
//
#ifndef RENDER_H
#define RENDER_H

#include "../Canvas/Canvas.h"
#include "../Player/player.h"
#include "../Ball/Ball.h"

void render_canvas(const Canvas *canvas,const Ball *ball, const Player *player, const Player *player2);
void render_winner(int winner);

#endif
