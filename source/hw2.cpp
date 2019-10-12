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
#define WAIT 150000

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
int isQuit = 0;
pthread_mutex_t game_mutex;
pthread_mutex_t cursor_mutex;
pthread_mutex_t log_mutex;
pthread_cond_t endgame;
pthread_t threads[ROW];

void update_frog(Frog *frog) {
    frog->print_frog();
}

void update_bank(Frog *frog) {
    if (frog->y_pos == 12 || frog->y_pos == 2 || frog->y_pos == 11) {
        printf("\033[1;1H");
        printf("||||||||||||||||||||||||||||||||||||||||||||||||||                                      ");
        printf("\033[12;1H");
        printf("||||||||||||||||||||||||||||||||||||||||||||||||||                                      ");
    }
    return;
}

void *update_log(void *threadid) {
    long tid;
    tid = (long) threadid;
    Log *current_log = logs[(int) tid];
    current_log->row = (int) tid + 1;
    current_log->len = rand() % 25;
    srand(tid);
    current_log->direction = 2 * (tid % 2) - 1;
    current_log->left_pos = rand() % (50 - logs[(int) tid]->len - 1);
    while (!isQuit) {
        pthread_mutex_lock(&cursor_mutex);
        current_log->printLog();
        update_bank(frog);
        frog->move_withLog(current_log);
        update_frog(frog);
        current_log->logs_move();
        game->living = game->judge(frog, logs);
        if (game->living != 1) {
            pthread_mutex_unlock(&cursor_mutex);
            pthread_exit(NULL);
        }
        pthread_mutex_unlock(&cursor_mutex);
        usleep(WAIT);
    }
}

/*  Check keyboard hits, to change frog's position or quit the game. */
void *KeyBoardInput(void *threadid) {

    pthread_mutex_lock(&game_mutex); // lock the game_mutex so the main thread does not quit

    while (!isQuit) {
        if (kbhit()) {
            pthread_mutex_lock(&cursor_mutex); // lock the game_mutex so the main thread does not quit
            frog->reset_cursor();
            char dir = getchar();

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

            if (dir == 'q' || dir == 'Q') {
                printf("\033[2J\033[H"); // clear the screen and reset the cursor to upper left
                printf("Quit!\n");
                isQuit = 1;
                game->living = -1;
                pthread_cond_signal(&endgame);
                pthread_mutex_unlock(&game_mutex); // unlock the mutex so the game ends as main thread quits
            }
        }
        pthread_mutex_unlock(&cursor_mutex);
        if (game->living != 1) {
            for (int i = 0; i < 10; i++){
                pthread_join(threads[i], NULL);
            }
            printf("\033[2J\033[H"); // clear the screen and reset the cursor to upper left
            pthread_cond_signal(&endgame);
            pthread_mutex_unlock(&game_mutex);
            break;
        }
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {

    pthread_mutex_init(&game_mutex, NULL);// initialize game_mutex so game does not end
    pthread_mutex_init(&cursor_mutex, NULL); // initialize cursor_mutex so only one cursor is used at one time
    pthread_mutex_init(&log_mutex, NULL); // initialize log_mutex so only one log is updating at one time

    game->init_game();
    update_bank(frog);

    /*  Create pthreads for wood move and frog control.  */
    int rc;

    for (long i = 0; i < ROW; i++) {
//        printf("In main: create thread %ld\n", i);
        rc = pthread_create(&threads[i], NULL, update_log, (void *) i);

        if (rc) {
            printf("ERROR: return code from init_log() is %d", rc);
            exit(1);
        }
    }

    frog->print_frog();

    pthread_t *KeyBoard = (pthread_t *) calloc(1, sizeof(pthread_t));
    rc = pthread_create(KeyBoard, NULL, KeyBoardInput, (void *) 0);

    if (rc) {
        printf("ERROR: return code from KeyBoardInput() is %d", rc);
        exit(1);
    }

    pthread_cond_wait(&endgame, &game_mutex);
    game->show_status();
    pthread_mutex_destroy(&game_mutex);
    pthread_exit(NULL);



    /*  Check game's status  */

    /*  Print the map on the screen  */

    /*  Display the output for user: win, lose or quit.  */

    return 0;
}



