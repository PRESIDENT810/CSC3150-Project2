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
    int direction; // 0: left; 1: right

    Log(int idx = 0, int len = 10, int left_pos = 0) {
        this->row = row + 1; // row starts from 1
        this->len = len;
        this->left_pos = left_pos;
    }

    void printLog() {
//        printf("\033[%d;1H", this->row);
        printf("\033[%d;%dH", this->row + 1, left_pos);
        for (int i = 0; i < COLUMN; i++) {
            if (i < left_pos || i > left_pos + len) putchar(' ');
            else putchar('=');
        }
    }

    void logs_move(void *t) {


        /*  Move the logs  */
        switch (this->direction) {
            case 0: // moving left
                if (this->left_pos == 0) { // hit the left wall
                    this->direction = 1; // should move right
                    this->left_pos++;
                } else {
                    this->left_pos--;
                }
                break;

            case 1:
                if (this->left_pos + len == COLUMN) { // hit the right wall
                    this->direction = 0; // should move left
                    this->left_pos--;
                } else {
                    this->left_pos++;
                }
                break;
            default:
                break;
        }
    }

};

#endif //CSC3150_ASSIGNMENT_2_LOG_H
