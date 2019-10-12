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
    int living; // 1: living; 0: died; -1: quit

public:
    Game() {
        this->action = '0';
        this->living = 1;
    }

    // P.S. print frog and pring log must go together (first print log then print frog)

    void update(Frog *frog, Log *log[]) {
        if (frog->y_pos == 11 || frog->y_pos == 12 || frog->y_pos == 1 || frog->y_pos == 2) print_bank();
        for (int i = 0; i < ROW; i++){
            log[i]->logs_move();
            log[i]->printLog();
        }
        frog->print_frog();
    }

    void print_bank() {
        printf("\033[1;1H");
        printf("||||||||||||||||||||||||||||||||||||||||||||||||||");
        printf("\033[12;1H");
        printf("||||||||||||||||||||||||||||||||||||||||||||||||||");
    }

    void init_game() {
        printf("Game Starts!\n");
        printf("\033[?25l");
        sleep(1);
        printf("\033[2J\033[H"); // clear the screen and reset the cursor to upper left

        this->print_bank();
    }

    int judge(Frog *frog, Log *log) {
        if (frog->x_pos >= log->left_pos && frog->x_pos <= log->left_pos + log->len) {
            return 1; // still live
        } else {
            this->living = 0;
            return 0;
        }
    }

    void show_status() {
        printf("\033[H\033[2J");
        if (living == 1) {
            printf("YOU LUCKY BASTARD (win)");
        } else if (living == 0) {
            printf("YOU DIED (lose)");
        } else {
            printf("YOU LITTLE COWARD (quit)");
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
