#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// setting the size of the "display"
int ScreenX = 40;
int ScreenY = 20;

//struct for the payer pos
typedef struct {
    int x;
    int y;
} player;

//funtion to display the screen
void loadScreen(player p) {

    // looping through the 1d array 
    //using x and y to break in to 2d 
    for (int y = 0; y < ScreenY; y++) {
        for (int x = 0; x < ScreenX; x++) {
            if (p.x == x && p.y == y) {
                printf("&"); //player symobol
            } else {
                printf("."); // empty space
            }
        }
        printf("\n");//new line 
    }
}

int main() {
    char input; //user input

    //initalising player at center
    player player1;
    player1.x = ScreenX/2;     
    player1.y = ScreenY/2; 

    //game loop (q to quit)
    while (input != 'q') {
        loadScreen(player1);//loading the display with player pos

        //asking and taking the users input
        printf("use w/a/s/d to move, press q to quit: ");
        scanf(" %c", &input); 

        //moving player pos based on input 
        switch (input) {
			  break;
			case 'w':
			player1.y--;
			  break;
			case 'a':
            player1.x--;
			  break;
			case 's':
			player1.y++;
			  break;
			case 'd':
			player1.x++;
			  break;
			default:
            break;
		  }
    }

    return 0;
}