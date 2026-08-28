#include <stdlib.h>
#include <unistd.h>

#include "../config/config.h"
#include "../Ai/Ai.h"
#include "player.h"

void player_logic(Player *player, Player *Player2, int p_type) {
    unsigned char ch;

    while (read(STDIN_FILENO, &ch, 1) > 0) {
        if (ch == 'w') {
            if (player->y > 1) {
                player->y -= player->speed;
            }
        }
        else if (ch == 's') {
            if (player->y + player->length < CANVAS_HEIGHT - 1) {
                player->y += player->speed;
            }
        }
        if (p_type == 1) {
            if (ch == 'i') {
                if (Player2->y > 1) {
                    Player2->y -= Player2->speed;
                }
            }
            else if (ch == 'k') {
                if (Player2->y + Player2->length < CANVAS_HEIGHT - 1) {
                    Player2->y += Player2->speed;
                }
            }
            else if (ch == 'q') {
                exit(0);
            }
        }
    }
}

void gen_player(Player *Player, char type) {
    Player->length = PLAYER_LENGTH;
    Player->speed = PLAYER_SPEED;
    Player->y = (CANVAS_HEIGHT - Player->length) / 2;
    Player->type = type;

    if (type == '1') {
        Player->x = 5;
    }
    else if (type == '2') {
        Player->x = CANVAS_WIDTH - 5;
    }
}
