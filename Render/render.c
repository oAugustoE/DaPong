#include <stdio.h>
#include "../Canvas/Canvas.h"
#include "../Player/player.h"
#include "../Ball/Ball.h"
#include "../config/config.h"

void render_canvas(const Canvas *Window,const Ball *Ball, const Player *player, const Player *player2) {
    for (int y = 0; y < Window->height; y++) {
        for (int x = 0; x < Window->width; x++) {
            if (Ball->x == x && Ball->y == y) {
                printf("*");
            }
            else if (y == 0 || y == Window->height - 1) {
                printf("-");
            }
            else if (x == 0 || x == Window->width - 1) {
                printf("|");
            }
            else if ((x == player->x && y >= player->y && y < player->y + player->length)
                || x == player2->x && y >= player2->y && y < player2->y + player2->length) {
                printf("#");
                }
            else {
                printf(" ");
            }
        }

        printf("\n");
    }
}

void render_winner(const int winner) {
    printf("\033[H");
    for (int y = 0; y < CANVAS_HEIGHT; y++) {
        for (int x = 0; x < CANVAS_WIDTH-WINNING_TEXT_SIZE; x++) {
            if (y == 0 || y == CANVAS_HEIGHT - 1) {
                printf("-");
            }
            else if (x == 0 || x == CANVAS_WIDTH - WINNING_TEXT_SIZE-2) {
                printf("|");
            }
            else if (x == CANVAS_WIDTH / 2 - 1) {
                printf("Player %i ganhou!", winner);
            }
            else {
                printf(" ");
            }
        }

        printf("\n");
    }
}