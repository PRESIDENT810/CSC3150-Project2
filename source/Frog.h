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

class Frog {
private:
    void move_up() {
        y_pos++;
    }

    void move_down() {
        y_pos--;
    }

    void move_left() {
        x_pos--;
    }

    void move_right() {
        x_pos++;
    }

public:
    int x_pos;
    int y_pos;

    Frog(int x, int y) {
        this->x_pos = x + 1; // the position of this frog starts from 1
        this->y_pos = y + 1;
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
        printf("\033[%d;%dH", this->x_pos + 1, this->y_pos);
        printf("0");
    }
};


#endif //CSC3150_ASSIGNMENT_2_FROG_H
