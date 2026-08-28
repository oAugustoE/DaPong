#include <stdio.h>

#define TITLE "DaPong!"
#define OPTION_BUTTON_1 "vsAi"
#define OPTION_BUTTON_2 "vsPlayer"
#include <unistd.h>

#include "../Canvas/Canvas.h"
#include "../Player/player.h"
#include "../Ball/Ball.h"
#include "../config/config.h"
#include "../Input/Input.h"




int render_menu() {

    set_conio_mode();

    int in_menu = 1;
    int button_selected = 0;

    int button1_size = sizeof(OPTION_BUTTON_1) - 1;
    int button2_size = sizeof(OPTION_BUTTON_2) - 1;
    int header_size = sizeof(TITLE) - 1;

    int total_button_size = button1_size + button2_size + 9;

    printf("\033[?1049h");
    printf("\033[2J\033[H");
    printf("\033[?25l");

    while (in_menu) {

        int header_x = (CANVAS_WIDTH - header_size) / 2;
        int button_x = (CANVAS_WIDTH - total_button_size) / 2;

        for (int y = 0; y < CANVAS_HEIGHT; y++) {
            for (int x = 0; x < CANVAS_WIDTH; x++) {

                if (y == 0 || y == CANVAS_HEIGHT - 1) {
                    printf("-");
                }
                else if (x == 0 || x == CANVAS_WIDTH - 1) {
                    printf("|");
                }
                else if (y == CANVAS_HEIGHT / 2 - 2 &&
                         x == header_x) {

                    printf("%s", TITLE);
                    x += header_size - 1;
                }
                else if (y == CANVAS_HEIGHT / 2 &&
                         x == button_x) {

                    if (button_selected == 0) {
                        printf(">>%s<<     %s", OPTION_BUTTON_1, OPTION_BUTTON_2);
                    }
                    else {
                        printf("%s     >>%s<<", OPTION_BUTTON_1, OPTION_BUTTON_2);
                    }

                    x += total_button_size - 1;
                }
                else {
                    printf(" ");
                }
            }

            printf("\n");
        }

        fflush(stdout);
        printf("\033[%dA", CANVAS_HEIGHT);

        char input;

        if (read(STDIN_FILENO, &input, 1) > 0) {

            if (input == 'a' || input == 'A') {
                if (button_selected == 0) {
                    button_selected = 1;
                }
                else {
                    button_selected = 0;
                }
            }

            else if (input == 'd' || input == 'D') {
                if (button_selected == 0) {
                    button_selected = 1;
                }
                else {
                    button_selected = 0;
                }
            }

            else if (input == '\n' || input == ' ') {

                if (button_selected == 0) {
                    return button_selected;
                    in_menu = 0;
                    printf("\033[?25h");
                    printf("\033[?1049l");
                }
                return button_selected;
                in_menu = 0;
                printf("\033[?25h");
                printf("\033[?1049l");
            }

            else if (input == 27) {
                in_menu = 0;
                printf("\033[?25h");
                printf("\033[?1049l");
            }
        }

        usleep(30000);
    }
}


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
            else if (x == CANVAS_WIDTH / 2 - 14 && y == CANVAS_HEIGHT / 2 - 1)  {
                x += 13;
                printf("Player %i ganhou!", winner);
            }
            else {
                printf(" ");
            }
        }

        printf("\n");
    }
}