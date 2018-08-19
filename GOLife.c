#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int edge_setter = 0;
int BOARD_SIZE = 10;
int neighbours[100][8];

char playingboard[100];
char buffer[100];

void initialise_board(){
    for(int i = 0; i < (BOARD_SIZE * BOARD_SIZE); i++){
        playingboard[i] = '.';
    }
}    

void print_board(){
    int x = 0;

    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j < BOARD_SIZE; j++){
            printf("%c ",playingboard[x]);
            x++;
        }
        printf("\n");
    }
}

void set_beacon(){
/*
sets initial state like this:
. . . . . . . . . .
. . * * . . . . . .
. . * . . . . . . .
. . . . . * . . . .
. . . . * * . . . .
. . . . . . . . . .
. . . . . . . . . .
. . . . . . . * . .
. . . . . . . * . .
. . . . . . . * . .
*/
    playingboard[12] = '*';
    playingboard[13] = '*';
    playingboard[22] = '*';
    playingboard[35] = '*';
    playingboard[44] = '*';
    playingboard[45] = '*';

    playingboard[97] = '*';
    playingboard[87] = '*';
    playingboard[77] = '*';
}

void initialise_neighbours(){
    for(int i = 0; i < (BOARD_SIZE * BOARD_SIZE); i++){
        for(int j = 0; j < 8; j++){
            neighbours[i][j] = -1;
        }
    }
}

void set_neighbours(){
// sets the number of each neighbour of each member in playingboard array
    for(int x = 0; x < (BOARD_SIZE * BOARD_SIZE); x++){
//corners
        if(x == 0){
            //top left corner
            neighbours[x][0] = (x + 1);
            neighbours[x][1] = (BOARD_SIZE);
            neighbours[x][2] = (BOARD_SIZE + 1);
            printf("top left corner %d\n", x);
        }
        else if(x == (BOARD_SIZE -1)){
            //top right corner
            neighbours[x][0] = (x - 1);
            neighbours[x][1] = (x + BOARD_SIZE -1);
            neighbours[x][2] = (x + BOARD_SIZE);
            printf("top right corner %d\n", x);
        }
        else if(x == ((BOARD_SIZE * BOARD_SIZE) - 10)){
            //bottom left corner
            neighbours[x][0] = (x - BOARD_SIZE);
            neighbours[x][1] = (x - BOARD_SIZE + 1);
            neighbours[x][2] = (x + 1);
            printf("bottom left corner %d\n", x);
        }
        else if(x == ((BOARD_SIZE * BOARD_SIZE) - 1)){
            //bottom right corner
            neighbours[x][0] = (x - BOARD_SIZE -1);
            neighbours[x][1] = (x - BOARD_SIZE);
            neighbours[x][2] = (x - 1);
            printf("bottom right corner %d\n", x);
        }
//edges
        else if(x % BOARD_SIZE == 0){
            //this is for the left hand side edge
            neighbours[x][0] = (x - BOARD_SIZE);
            neighbours[x][1] = (x - BOARD_SIZE + 1);
            neighbours[x][2] = (x + 1);
            neighbours[x][3] = (x + BOARD_SIZE);
            neighbours[x][4] = (x + BOARD_SIZE + 1);
            printf("left %d\n", x);
        }
        else if(x % (BOARD_SIZE) == 9){
            //this is for the right hand side edge
            neighbours[x][0] = (x - BOARD_SIZE - 1);
            neighbours[x][1] = (x - BOARD_SIZE);
            neighbours[x][2] = (x - 1);
            neighbours[x][3] = (x + BOARD_SIZE - 1);
            neighbours[x][4] = (x + BOARD_SIZE);
            printf("right %d\n", x);
        }
        else if(x >= 0 && x < BOARD_SIZE){
            //this is for the top edge
            neighbours[x][0] = (x - 1);
            neighbours[x][1] = (x + 1);
            neighbours[x][2] = (x + BOARD_SIZE - 1);
            neighbours[x][3] = (x + BOARD_SIZE);
            neighbours[x][4] = (x + BOARD_SIZE + 1);
            printf("top %d\n", x);
        }
        else if(x <= (BOARD_SIZE * BOARD_SIZE) && x > ((BOARD_SIZE * BOARD_SIZE) - BOARD_SIZE)){
            //this is for the bottom edge
            neighbours[x][0] = (x - BOARD_SIZE - 1);
            neighbours[x][1] = (x - BOARD_SIZE);
            neighbours[x][2] = (x - BOARD_SIZE + 1);
            neighbours[x][3] = (x - 1);
            neighbours[x][4] = (x + 1);
            printf("bottom %d\n", x);
        }
        else{
            //every generic peice that is not a corner or a side piece
            neighbours[x][0] = (x - BOARD_SIZE - 1);
            neighbours[x][1] = (x - BOARD_SIZE);
            neighbours[x][2] = (x - BOARD_SIZE + 1);
            neighbours[x][3] = (x - 1);
            neighbours[x][4] = (x + 1);
            neighbours[x][5] = (x + BOARD_SIZE - 1);
            neighbours[x][6] = (x + BOARD_SIZE);
            neighbours[x][7] = (x + BOARD_SIZE + 1);
        }
    }
}

void playingboard_to_buffer(){
    for(int i = 0; i < (BOARD_SIZE * BOARD_SIZE); i++){
        buffer[i] = playingboard[i];
    }
}

void buffer_to_playingboard(){
    for(int i = 0; i < (BOARD_SIZE * BOARD_SIZE); i++){
        playingboard[i] = buffer[i];
    }
}

void the_game(){
    int conway = 1;
    while(conway == 1){
        playingboard_to_buffer();
        for(int x = 0; x < (BOARD_SIZE * BOARD_SIZE); x++){
            //test for life
            int tempNeighbors = 0;
            for(int i = 0; i < 8; i++){
                if(neighbours[x][i] != -1){
                    if (playingboard[neighbours[x][i]] == '*'){
                        tempNeighbors++;
                    }
                }
            }
//            printf("%d\n", tempNeighbors);
            if(tempNeighbors < 2 && playingboard[x] == '*'){
                buffer[x] = '.';
            }
            if((tempNeighbors == 2 || tempNeighbors == 3) && playingboard[x] == '*'){
                buffer[x] = '*';
            }
            if(tempNeighbors > 3 && playingboard[x] == '*'){
                buffer[x] = '.';
            }
            if(tempNeighbors == 3 && playingboard[x] == '.'){
                buffer[x] = '*';
            }
        }
        buffer_to_playingboard();
        //end part of "the game"
        printf("\n");print_board();
        Sleep(1000);
    }
}

int main(){
    initialise_board();
    set_beacon();
    initialise_neighbours();
    set_neighbours();
    print_board();
    the_game();
return 0;
}
