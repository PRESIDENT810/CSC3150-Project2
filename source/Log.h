//
// Created by 仲凯宁 on 2019-10-12.
//

#ifndef CSC3150_ASSIGNMENT_2_LOG_H
#define CSC3150_ASSIGNMENT_2_LOG_H

#define ROW 10
#define COLUMN 50

//
// Created by 仲凯宁 on 2019-10-12.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <curses.h>
#include <termios.h>
#include <fcntl.h>

class Log {
public:
    int row;
    int len;
    int left_pos;
    int direction; // 1: left; 1: right
    int randseed;

    Log(int idx = 0, int len = 10, int left_pos = 0, int direction = 1, int randseed = 0) {
        this->row = idx + 1; // row starts from 1
        this->len = len;
        this->left_pos = left_pos;
//        this->direction = direction;
        this->direction = 1;
    }

    void printLog() {
        printf("\033[%d;1H", this->row + 1);

        if (this->direction == 1) {
            for (int i = 0; i < COLUMN; i++) {
                if (i >= this->left_pos && i <= this->left_pos + this->len) putchar('=');
//            else if (this->left_pos+this->len > COLUMN && i < (this->left_pos+this->len)%COLUMN) putchar('=');
                else putchar(' ');
            }
        }
        else{
            for (int i = 0; i < COLUMN; i++) {
                if (i >= this->left_pos && i <= this->left_pos + this->len) putchar('=');
//            else if (this->left_pos+this->len > COLUMN && i < (this->left_pos+this->len)%COLUMN) putchar('=');
                else putchar(' ');
            }
        }


        printf("\033[%d;51H", this->row + 1);
        for (int i = 0; i < COLUMN; i++) {
            putchar(' ');
        }
    }

    void logs_move() {
        /*  Move the logs  */
        switch (this->direction) {
            case -1: // moving left
                this->left_pos--;
                if (this->left_pos+this->len == 0) {
                    this->len = rand() % 15 + 10;
                    this->left_pos = 50;
                }
                break;

            case 1: // moving right
                this->left_pos++;
                srand(this->len);
                if (this->left_pos == COLUMN - 1) {
                    this->len = rand() % 15 + 10;
                    this->left_pos = -this->len;
                }
                break;
            default:
                break;
        }
    }
};

#endif //CSC3150_ASSIGNMENT_2_LOG_H
