#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

#define PLAYER_SPEED 1
#define CANVAS_WIDTH 100
#define CANVAS_HEIGHT 15
#define PLAYER_LENGTH 3
#define TICK_SPEED 100000
#define WINNING_TEXT_SIZE 14

static struct termios orig_tty;

typedef struct {
    int x;
    int y;
    int dx;
    int dy;
} ball;

typedef struct {
    int width;
    int height;
} canvas;

typedef struct {
    int x;
    int y;
    int length;
    int speed;
    char type;
} player;

static void gen_player(player *Player, char type);

static void player_logic(player *Player, player *Player2);
static void set_conio_mode(void);
static void reset_terminal_mode(void);
static int ball_logic(ball *Ball, const player *Player1, const player *Player2);

static void show_winner(int winner);
static void print_canvas(const canvas *Window, const ball *Ball, const player *Player, const player *Player2);
static void gen_canvas(canvas *Window,ball *Ball,player *Player,player *Player2);
static void gen_ball(ball *Ball);

int main(void) {
    int GameRunning = 1;

    srand(time(NULL));

    canvas Window;
    ball Ball;
    player Player;
    player Player2;

    set_conio_mode();
    gen_canvas(&Window, &Ball, &Player, &Player2);

    printf("\033[2J");

    while (GameRunning) {
        player_logic(&Player, &Player2);

        printf("\033[H");
        print_canvas(&Window, &Ball, &Player, &Player2);

        switch (ball_logic(&Ball, &Player, &Player2)) {
            case 1:
                GameRunning = 0;
                show_winner(1);
                break;
            case 2:
                GameRunning = 0;
                show_winner(2);
                break;
            default:
                break;
        }

        usleep(TICK_SPEED);
    }

    return 0;
}

void gen_canvas(canvas *Window,ball *Ball,player *Player,player *Player2) {
    Window->width = CANVAS_WIDTH;
    Window->height = CANVAS_HEIGHT;

    gen_ball(Ball);
    gen_player(Player, '1');
    gen_player(Player2, '2');
}

void gen_ball(ball *Ball) {
    Ball->x = CANVAS_WIDTH / 2;
    Ball->y = CANVAS_HEIGHT / 2;
    Ball->dx = (rand() % 2) ? 1 : -1;
    Ball->dy = (rand() % 2) ? 1 : -1;
}

void print_canvas(const canvas *Window,const ball *Ball, const player *Player, const player *Player2) {
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
            else if ((x == Player->x && y >= Player->y && y < Player->y + Player->length)
                || x == Player2->x && y >= Player2->y && y < Player2->y + Player2->length) {
                printf("#");
            }
            else {
                printf(" ");
            }
        }

        printf("\n");
    }
}

int ball_logic(ball *Ball, const player *Player, const player *Player2) {
    if (Ball->y <= 1 || Ball->y >= CANVAS_HEIGHT - 2) {
        Ball->dy *= -1;
    }

    if (Ball->dx < 0 &&
        Ball->x == Player->x + 1 &&
        Ball->y >= Player->y &&
        Ball->y < Player->y + Player->length) {
        Ball->dx = 1;
        }

    if (Ball->dx > 0 &&
        Ball->x == Player2->x - 1 &&
        Ball->y >= Player2->y &&
        Ball->y < Player2->y + Player2->length) {
        Ball->dx = -1;
        }

    if (Ball->x <= 1) {
        return 2;
    }

    if (Ball->x >= CANVAS_WIDTH - 2) {
        return 1;
    }

    Ball->x += Ball->dx;
    Ball->y += Ball->dy;

    return 0;
}

void gen_player(player *Player, char type) {
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

void player_logic(player *Player, player *Player2) {
    unsigned char ch;

    while (read(STDIN_FILENO, &ch, 1) > 0) {
        if (ch == 'w') {
            if (Player->y > 1) {
                Player->y -= Player->speed;
            }
        }
        else if (ch == 's') {
            if (Player->y + Player->length < CANVAS_HEIGHT - 1) {
                Player->y += Player->speed;
            }
        }
        else if (ch == 'i') {
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

void reset_terminal_mode(void) {
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_tty);
}

void set_conio_mode(void) {
    struct termios new_tty;

    tcgetattr(STDIN_FILENO, &orig_tty);
    atexit(reset_terminal_mode);

    new_tty = orig_tty;
    new_tty.c_lflag &= ~(ICANON | ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &new_tty);

    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
}

void show_winner(int winner) {
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
