#include "gamefunction.c"

int main() {

    //initalising structs
    player player1;
    mapData map[ScreenX * ScreenY];
    astroidData astroids[maxAstroids];

    initaliseGame(&player1, map, astroids);

    //game loop (q to quit)
    while (input != 'q') {

        if (strcmp(globalEventFlag, "DEAD") == 0) {
            writeFile();
            break;
        } else if (strcmp(globalEventFlag, "LEVEL_UP") == 0) {
            nextLevelLoad(&player1, map, astroids);
        } else if  (strcmp(globalEventFlag, "WIN") == 0){
            printf("wou won!!!!");
            printf("Press any key to load:  ");
            scanf(" %c", &null);
            break;
        }
        strcpy(globalEventFlag, ""); // reset flag
        
        loadScreen(&player1, map, astroids);//loading the display with player pos
        
        //asking and taking the users input
        printf("use w/a/s/d to move, press q to quit: ");
        scanf(" %c", &input); 
    
        //moving player pos based on input 
        switch (input) {
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

        gameLoopCheck(&player1, map, astroids, &trashCollection);

        astroidLoop(astroids, map);

        
        gameLoopCheck(&player1, map, astroids, &trashCollection);

    }

    return 0;
}