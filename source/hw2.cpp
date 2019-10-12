#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <curses.h>
#include <termios.h>
#include <fcntl.h>
#include <pthread.h>
#include "Log.h"
#include "Frog.h"
#include "util.h"

#define ROW 10
#define COLUMN 50

Frog *frog = new Frog();
Game *game = new Game();
Log *log1 = new Log();
Log *log2 = new Log();
Log *log3 = new Log();
Log *log4 = new Log();
Log *log5 = new Log();
Log *log6 = new Log();
Log *log7 = new Log();
Log *log8 = new Log();
Log *log9 = new Log();
Log *log10 = new Log();
Log *logs[] = {log1, log2, log3, log4, log5, log6, log7, log8, log9, log10};

void *init_log(void *threadid) {
    long tid;
    tid = (long) threadid;
    logs[(int) tid]->row = (int) tid + 1;
    logs[(int) tid]->left_pos = rand()%(50-logs[(int) tid]->len);
    logs[(int) tid]->printLog();
}

int main(int argc, char *argv[]) {
    game->init_game();

    /*  Create pthreads for wood move and frog control.  */
    pthread_t threads[ROW];
    int rc;

    for (long i = 0; i < ROW; i++) {
//        printf("In main: create thread %ld\n", i);
        rc = pthread_create(&threads[i], NULL, init_log, (void *) i);
        pthread_join(threads[i], NULL);

        if (rc) {
            printf("ERROR: return code from pthread_create() is %d", rc);
            exit(1);
        }
    }

    frog->print_frog();




    /*  Check keyboard hits, to change frog's position or quit the game. */

    /*  Check game's status  */

    /*  Print the map on the screen  */

    /*  Display the output for user: win, lose or quit.  */



    int isQuit = 0;
    while (!isQuit) {
        if (kbhit()) {

            char dir = getchar();

            //printf("\033[H\033[2J");

            if (dir == 'w' || dir == 'W') {
                frog->do_action('w');
            }

            if (dir == 'a' || dir == 'A') {
                frog->do_action('a');
            }

            if (dir == 'd' || dir == 'D') {
                frog->do_action('d');
            }

            if (dir == 's' || dir == 'S') {
                frog->do_action('s');
            }

            game->update(frog, logs);

            if (dir == 'q' || dir == 'Q') {
                printf("Quit!\n");
                isQuit = 1;
            }
        }
    }
    return 0;

}
