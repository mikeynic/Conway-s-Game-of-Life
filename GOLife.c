#include <stdio.h>
#include <stdlib.h>
#include <windows.h>



//things needed to change how big the board is
int BOARD_SIZE = 17;
int neighbours[289][8];     //8 stays the same as it is the max possible number of neighbours
char playingboard[289];
char buffer[289];



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

void set_beacons(){
/*
NOTE: only for 10 x 10 grid
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

void set_glider(){
    /*

    NOTE: only sets glider for a 30 x 30 grid
    sets initial state like this:

. . * . . . . . . . . . . . . . . . . . . . . . . . . . . .
. . . * . . . . . . . . . . . . . . . . . . . . . . . . . .
. * * * . . . . . . . . . . . . . . . . . . . . . . . . . .
. . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
. . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
. . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
. . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
. . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
. . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
. . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
. . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
. . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
. . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
. . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
. . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
. . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
. . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
. . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
. . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
. . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
. . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
. . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
. . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
. . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
. . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
. . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
. . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
. . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
. . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
. . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

    */
    playingboard[2] = '*';
    playingboard[33] = '*';
    playingboard[61] = '*';
    playingboard[62] = '*';
    playingboard[63] = '*';
}

void set_pulsar(){
    playingboard[38] = '*';playingboard[39] = '*';playingboard[40] = '*';playingboard[44] = '*';playingboard[45] = '*';playingboard[46] = '*';
    playingboard[70] = '*';playingboard[75] = '*';playingboard[77] = '*';playingboard[82] = '*';
    playingboard[87] = '*';playingboard[92] = '*';playingboard[94] = '*';playingboard[99] = '*';
    playingboard[104] = '*';playingboard[109] = '*';playingboard[111] = '*';playingboard[116] = '*';
    playingboard[123] = '*';playingboard[124] = '*';playingboard[125] = '*';playingboard[129] = '*';playingboard[130] = '*';playingboard[131] = '*';
    playingboard[157] = '*';playingboard[158] = '*';playingboard[159] = '*';playingboard[163] = '*';playingboard[164] = '*';playingboard[165] = '*';
    playingboard[172] = '*';playingboard[177] = '*';playingboard[179] = '*';playingboard[184] = '*';
    playingboard[189] = '*';playingboard[194] = '*';playingboard[196] = '*';playingboard[201] = '*';
    playingboard[206] = '*';playingboard[211] = '*';playingboard[213] = '*';playingboard[218] = '*';
    playingboard[242] = '*';playingboard[243] = '*';playingboard[244] = '*';playingboard[248] = '*';playingboard[249] = '*';playingboard[250] = '*';

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
//            printf("top left corner %d\n", x);
        }
        else if(x == (BOARD_SIZE -1)){
            //top right corner
            neighbours[x][0] = (x - 1);
            neighbours[x][1] = (x + BOARD_SIZE -1);
            neighbours[x][2] = (x + BOARD_SIZE);
//            printf("top right corner %d\n", x);
        }
        else if(x == ((BOARD_SIZE * BOARD_SIZE) - (BOARD_SIZE))){
            //bottom left corner
            neighbours[x][0] = (x - BOARD_SIZE);
            neighbours[x][1] = (x - BOARD_SIZE + 1);
            neighbours[x][2] = (x + 1);
//            printf("bottom left corner %d\n", x);
        }
        else if(x == ((BOARD_SIZE * BOARD_SIZE) - 1)){
            //bottom right corner
            neighbours[x][0] = (x - BOARD_SIZE -1);
            neighbours[x][1] = (x - BOARD_SIZE);
            neighbours[x][2] = (x - 1);
//            printf("bottom right corner %d\n", x);
        }
//edges
        else if(x % BOARD_SIZE == 0){
            //this is for the left hand side edge
            neighbours[x][0] = (x - BOARD_SIZE);
            neighbours[x][1] = (x - BOARD_SIZE + 1);
            neighbours[x][2] = (x + 1);
            neighbours[x][3] = (x + BOARD_SIZE);
            neighbours[x][4] = (x + BOARD_SIZE + 1);
//            printf("left %d\n", x);
        }
        else if(x % (BOARD_SIZE) == (BOARD_SIZE -1)){
            //this is for the right hand side edge
            neighbours[x][0] = (x - BOARD_SIZE - 1);
            neighbours[x][1] = (x - BOARD_SIZE);
            neighbours[x][2] = (x - 1);
            neighbours[x][3] = (x + BOARD_SIZE - 1);
            neighbours[x][4] = (x + BOARD_SIZE);
//            printf("right %d\n", x);
        }
        else if(x >= 0 && x < BOARD_SIZE){
            //this is for the top edge
            neighbours[x][0] = (x - 1);
            neighbours[x][1] = (x + 1);
            neighbours[x][2] = (x + BOARD_SIZE - 1);
            neighbours[x][3] = (x + BOARD_SIZE);
            neighbours[x][4] = (x + BOARD_SIZE + 1);
//            printf("top %d\n", x);
        }
        else if(x <= (BOARD_SIZE * BOARD_SIZE) && x > ((BOARD_SIZE * BOARD_SIZE) - BOARD_SIZE)){
            //this is for the bottom edge
            neighbours[x][0] = (x - BOARD_SIZE - 1);
            neighbours[x][1] = (x - BOARD_SIZE);
            neighbours[x][2] = (x - BOARD_SIZE + 1);
            neighbours[x][3] = (x - 1);
            neighbours[x][4] = (x + 1);
//            printf("bottom %d\n", x);
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
        print_board();printf("\n");
        
        Sleep(500);
    }
}

int main(){
    initialise_board();
//    set_beacons();
//    set_glider();
    set_pulsar();
    initialise_neighbours();
    set_neighbours();
    print_board();
    the_game();
return 0;
}
