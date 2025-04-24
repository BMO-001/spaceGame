#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int ScreenX = 40;
int ScreenY = 20;

typedef struct {
    int x;
    int y;
} player;

void loadScreen(player p) {

    // Print the screen
    for (int y = 0; y < ScreenY; y++) {
        for (int x = 0; x < ScreenX; x++) {
            if (p.x == x && p.y == y) {
                printf("&"); // Player
            } else {
                printf(".");
            }
        }
        printf("\n");
    }
}

int main() {
    char input;

    srand(time(NULL));

    player player1;
    player1.x = ScreenX/2;     
    player1.y = ScreenY/2; 

    while (input != 'q') {
        loadScreen(player1);

        printf("use w/a/s/d to move, press q to quit: ");
        scanf(" %c", &input); 

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