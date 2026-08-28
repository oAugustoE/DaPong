#include "../Ball/Ball.h"
#include "../config/config.h"
#include "../Player/player.h"

void Ai(Ball *ball, Player *ai) {
    int target = (int)ball->y;

    if (ai->y < target) {
        ai->y += PLAYER_SPEED;
    }
    else if (ai->y > target) {
        ai->y -= PLAYER_SPEED;
    }
    if (ai->y < 1) {
        ai->y = 1;
    }
    if (ai->y + ai->length > CANVAS_HEIGHT - 1) {
        ai->y = CANVAS_HEIGHT - 1 - ai->length;
    }
}