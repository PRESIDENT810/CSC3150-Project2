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

Frog *frog = new Frog(10, 25);
Log logs[10];
Game *game = new Game();

void *init_log(void *threadid){
    int logid = 0;
    logid = (int)logid;
    Log current_log = Log(logid, 15, logid);
    logs[logid] =current_log;
    current_log.printLog();
}

int main( int argc, char *argv[] ){
    game->init_game();

    /*  Create pthreads for wood move and frog control.  */
    pthread_t threads[ROW];
    int rc;

    for(int i =0; i<ROW; i++){
//        printf("In main: create thread %ld\n", i);
        rc = pthread_create(&threads[i], NULL, init_log, (void*)i);
        pthread_join(threads[i],NULL);
        break;
        if(rc){
            printf("ERROR: return code from pthread_create() is %d", rc);
            exit(1);
        }
    }




    /*  Check keyboard hits, to change frog's position or quit the game. */

    /*  Check game's status  */

    /*  Print the map on the screen  */

    /*  Display the output for user: win, lose or quit.  */



    int isQuit = 0;
	while (!isQuit) {
        if (kbhit()) {

            char dir = getchar();

            //printf("\033[H\033[2J");

            if (dir == 'w' || dir == 'W') frog->do_action('w');

            if (dir == 'a' || dir == 'A') frog->do_action('a');

            if (dir == 'd' || dir == 'D') frog->do_action('d');

            if (dir == 's' || dir == 'S') frog->do_action('s');

            if (dir == 'q' || dir == 'Q') {
                printf("Quit!\n");
                isQuit = 1;
            }
        }
    }
	return 0;

}
