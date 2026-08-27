#include <fcntl.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

static struct termios orig_tty;

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