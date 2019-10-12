//
// Created by 仲凯宁 on 2019-10-12.
//

#ifndef CSC3150_ASSIGNMENT_2_FROG_H
#define CSC3150_ASSIGNMENT_2_FROG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <curses.h>
#include <termios.h>
#include <fcntl.h>
#include "Log.h"

class Frog {
private:
    void move_up() {
        if (this->y_pos != 1)
        this->y_pos--;
    }

    void move_down() {
        if (this->y_pos != 12)
        this->y_pos++;
    }

    void move_left() {
        if (this->x_pos != 0)
        this->x_pos--;
    }

    void move_right() {
        if (this->x_pos != 49)
        this->x_pos++;
    }

public:
    int x_pos;
    int y_pos;

    Frog(int y = 12, int x= 25) {
        this->x_pos = x;
        this->y_pos = y; // y means the actual line which frog is in
    }

    void move_withLog(Log *log){
        if (this->y_pos == log->row) this->x_pos += log->direction;
    }

    void do_action(char key) {
        switch (key) {
            case 'w':
                this->move_up();
                break;
            case 'a':
                this->move_left();
                break;
            case 's':
                this->move_down();
                break;
            case 'd':
                this->move_right();
                break;
            default:
                break;
        }
    }

    void print_frog() {
        printf("\033[%d;%dH", this->y_pos, this->x_pos);
        printf("0");
    }
};


#endif //CSC3150_ASSIGNMENT_2_FROG_H
