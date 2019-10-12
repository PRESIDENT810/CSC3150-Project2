//
// Created by 仲凯宁 on 2019-10-12.
//

#ifndef CSC3150_ASSIGNMENT_2_UTIL_H
#define CSC3150_ASSIGNMENT_2_UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <curses.h>
#include <termios.h>
#include <fcntl.h>
#include "Log.h"
#include "Frog.h"

#define ROW 10
#define COLUMN 50


class Game {
private:
    char action;

public:
    int living; // 1: living; 0: died; -1: quit 2: win

    Game() {
        this->action = '0';
        this->living = 1;
    }

    // P.S. print frog and pring log must go together (first print log then print frog)

    void init_game() {
        printf("Game Starts!\n");
        printf("\033[?25l");
        sleep(1);
        printf("\033[2J\033[H"); // clear the screen and reset the cursor to upper left
    }

    int judge(Frog *frog, Log *logs[]) {
        if (frog->y_pos == 12)
            return 1;
        else if (frog->y_pos == 1)
            return 2;

        Log *log = logs[frog->y_pos - 2];
        if (log->direction == 1) {
            if (frog->x_pos >= log->left_pos && frog->x_pos <= log->left_pos + log->len + 1) {
                return 1; // still live
            } else {
                this->living = 0;
                return 0;
            }
        }
        else if (log->direction == -1) {
            if (frog->x_pos >= log->left_pos+1 && frog->x_pos <= log->left_pos + log->len + 2) {
                return 1; // still live
            } else {
                this->living = 0;
                return 0;
            }
        }
    }

    void show_status() {
        printf("\033[H\033[2J");
        sleep(2);
        if (living == 2) {
            printf("YOU LUCKY BASTARD (win)\n");
        } else if (living == 0) {
            printf("YOU SUCK (lose)\n");
        } else {
            printf("YOU LITTLE COWARD (quit)\n");
        }
    }
};

// Determine a keyboard is hit or not. If yes, return 1. If not, return 0.
int kbhit(void) {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);

    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);

    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}


#endif //CSC3150_ASSIGNMENT_2_UTIL_H
