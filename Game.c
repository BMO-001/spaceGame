#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

// setting the size of the "display"
int ScreenX = 40;
int ScreenY = 20;

int maxAstroids = 5;

//struct for the payer pos
typedef struct {
    int x;
    int y;
} player;

//struct for map pos data
typedef struct {
    char type[10];
    bool movable;
} mapData;

//struct for map pos data
typedef struct {
    int x;
    int y;
    int dx;
    int dy;
} astroidData;

// funtion to generate astroids
void genAstroids( astroidData *astroids){
    for (int i = 0; i < maxAstroids; i++){
        int side = rand() % 4;

        switch (side) {
            case 0: // top
            astroids[i].x = rand() % ScreenX;
            astroids[i].y = 0;
                break;
            case 1: // right
            astroids[i].x = ScreenX - 1;
            astroids[i].y = rand() % ScreenY;
                break;
            case 2: // bottom
            astroids[i].x = rand() % ScreenX;
            astroids[i].y = ScreenY - 1;
                break;
            case 3: // left
            astroids[i].x = 0;
            astroids[i].y = rand() % ScreenY;
                break;
        }
        astroids[i].dx = (rand() % 3) - 1;
        astroids[i].dy = (rand() % 3) - 1;
    }
}
// funtion to generate the map 
void genMap(mapData *map){
    
    for (int y = 0; y < ScreenY; y++) {
        for (int x = 0; x < ScreenX; x++) {

            int i = y * ScreenX + x; // from youtube vid to get 1d array value from x and y

            if ((rand() % 100) < 7) {
                strcpy(map[i].type, "Trash");
                map[i].movable = true;

            } else {
                strcpy(map[i].type, "Empty");
                map[i].movable = true;
            }

        }
    }


}

//funtion to display the screen
void loadScreen(player *p, mapData *map, astroidData *astroids) {
    
        // updating the astroid pos based on their trajectry
        for (int i = 0; i < maxAstroids; i++) {
            astroids[i].x += astroids[i].dx;
            astroids[i].y += astroids[i].dy;
    
            int index = astroids[i].y * ScreenX + astroids[i].x;
            strcpy(map[index].type, "Astro");
            map[index].movable = false;
        }

    // looping through the 1d array 
    //using x and y to break in to 2d w
    for (int y = 0; y < ScreenY; y++) {
        for (int x = 0; x < ScreenX; x++) {
            int i = y * ScreenX + x;

            if (p->x == x && p->y == y) {
                printf("&"); //player symobol
            } else if (strcmp(map[i].type, "Trash") == 0) {
                printf("#"); // trash
            } else if (strcmp(map[i].type, "Astro") == 0) {
                printf("@"); // astroid
            } else {
                printf("."); // empty space
            }
                

            if (strcmp(map[i].type, "Trash") != 0) {
                strcpy(map[i].type, "Empty");
                map[i].movable = true;}
            
        }
        printf("\n");//new line 
    }
}

int main() {
    char input; //user input

    srand(time(NULL));//setting random seed 

    //initalising player at center
    player player1;
    player1.x = ScreenX/2;     
    player1.y = ScreenY/2; 

    mapData map[ScreenX * ScreenY];
    astroidData astroids[maxAstroids];

    genAstroids(astroids);

    genMap(map);

    //game loop (q to quit)
    while (input != 'q') {
        loadScreen(&player1, map, astroids);//loading the display with player pos

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