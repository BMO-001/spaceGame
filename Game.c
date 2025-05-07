#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

bool typeCheck(char variable[], char required[]);

char input; //user input

// setting the size of the "display"
int ScreenX = 30;
int ScreenY = 15;
int astroidDamage = 100;
char globalEventFlag[10]; 
int gameLevel;

int trashCollection = 0;

int maxAstroids = 5;

//struct for the payer pos
typedef struct {
    int x;
    int y;
    int hp;
    int maxHp;
    int fule;
    int maxFule;
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

bool typeCheck(char variable[], char required[]);
void genAstroids(astroidData *astroids);
void astroidLoop(astroidData *astroids, mapData *map);
void genMap(mapData *map);
void readFile();
void writeFile();
void gameLoopCheck(player *p, mapData *map, astroidData *asteroids, int *trashCollected);
void nextLevelLoad(player *p, mapData *map, astroidData *astroids);
void loadScreen(player *p, mapData *map, astroidData *astroids);
void initaliseGame(player *p, mapData *map, astroidData *astroids);

bool typeCheck(char variable[], char required[]) {
    //variabkle to store type
    char type[10];
    //if the variable is a singke "thing" and is a letter than its a character
    if (strlen(variable) == 1 && ((variable[0] >= 33 && (variable[0] <= 47)) || ((variable[0] >= 58 && variable[0] <= 126)))) {
        strcpy(type, "char");
    } else {
        //if there is a decimal point its a float
        for (int i=0; i<strlen(variable); i++) {
            if (variable[i] == '.') {
                strcpy(type, "float");
                break;
            } else if (variable[i] < '0' || variable[i] > '9') {
                strcpy(type, "string");
            }else {//otherwise its an int
                strcpy(type, "int");
            }
        }
    }
    printf("The character is a: %s\n", type);
    if (strcmp(type, required) == 0){
        return 1;
    } else {
        return 0;
    }
}

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
        while (astroids[i].dx == 0 && astroids[i].dy == 0){
            astroids[i].dx = (rand() % 3) - 1;
            astroids[i].dy = (rand() % 3) - 1;
        }
    }
}

void astroidLoop(astroidData *astroids, mapData *map){

        // cleering the map of old astroids to remove goshts
        for (int i = 0; i < ScreenX * ScreenY; i++) {
            if (strcmp(map[i].type, "Astro") == 0) {
                strcpy(map[i].type, "Empty");
                map[i].movable = true;
            }
        }
            // updating the astroid pos based on their trajectry
            for (int i = 0; i < maxAstroids; i++) {
                astroids[i].x += astroids[i].dx;
                astroids[i].y += astroids[i].dy;
    
                if (astroids[i].x < 0 || astroids[i].x >= ScreenX ||
                    astroids[i].y < 0 || astroids[i].y >= ScreenY) {
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
        while (astroids[i].dx == 0 && astroids[i].dy == 0){
            astroids[i].dx = (rand() % 3) - 1;
            astroids[i].dy = (rand() % 3) - 1;
        }
                }
        
                int index = astroids[i].y * ScreenX + astroids[i].x;
                strcpy(map[index].type, "Astro");
                map[index].movable = false;
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

void readFile(){
    char txt[200];
    char null;
    FILE *fptr;
    fptr = fopen("gametxt.txt", "r");
        while (fgets(txt, 200, fptr)) {
            printf("%s", txt);
        }
        fclose(fptr);
        printf("Press any key to load:  ");
        scanf(" %c", &null);

}

void writeFile(){
    FILE *fptr;
    fptr = fopen("leaderboard.txt", "a");
    fprintf(fptr, "Level: %d\n", (gameLevel));
            fclose(fptr);
    }

void gameLoopCheck(player *p, mapData *map, astroidData *asteroids, int *trashCollected) {

if (p->x < 0) p->x = 0;
if (p->x >= ScreenX) p->x = ScreenX - 1;
if (p->y < 0) p->y = 0;
if (p->y >= ScreenY) p->y = ScreenY - 1;

    int i = p->y * ScreenX + p->x;

    //level chaeck
    if (gameLevel == 10){
        strcpy(globalEventFlag, "WIN");
        return;
    }

    //fule used
    p->fule -=1;

    // player collision and collection check
    if (strcmp(map[i].type, "Trash") == 0) {
        strcpy(map[i].type, "Empty");
        (*trashCollected)++;
    } else if (strcmp(map[i].type, "Astro") == 0) {
        p->hp -= 50;
        if (p->hp < 0) p->hp = 0;
    }  
    
    //fule check 
    if (p->fule <= 0 ){
        printf("\nYou ran out of fule!!\n");
        strcpy(globalEventFlag, "DEAD");
        return;
    }

    // health check
    if (p->hp <= 0) {
        printf("\nYou were destroyed by asteroids!\n");
        strcpy(globalEventFlag, "DEAD");
        return;
    }

    // trash left check (next level)
    for (int j = 0; j < ScreenX * ScreenY; j++) {
        if (strcmp(map[j].type, "Trash") == 0) {
            strcpy(globalEventFlag, ""); // game continues
            return;
        }
    }

    // No trash left
    strcpy(globalEventFlag, "LEVEL_UP");
}
void nextLevelLoad(player *p, mapData *map, astroidData *astroids){

    gameLevel ++;
    char upgrade[10];

    printf("\n \n \n \n \n \n \n Congratulations Traveler, Level Complete \n");
    printf("use the trash you collected to upgrade your ship:\n");
    printf("1. no actrion, go to next levle \n");
    printf("2. increase your fule tank size (10 trash) ");
    printf("3. somethings... \n");
    printf("please enter your choice  1-2-3: ");
    scanf(" %s", &upgrade);

    while ((typeCheck(upgrade, "int")) == 0){
        printf("please enter your choice  1-2-3: ");
        scanf(" %s", &upgrade);
        }
    if (upgrade[0] == '2') {
        trashCollection -= 10;
        p->maxFule += 20;
    } 

    //gen next level data
    genMap(map);
    genAstroids(astroids);
    p->x = ScreenX/2;
    p->y = ScreenY/2;
    p->fule = p->maxFule;

}


//funtion to display the screen
void loadScreen(player *p, mapData *map, astroidData *astroids) {

    astroidLoop(astroids, map);

    printf("fule: %d/%d | Trash: %d | level: %d\n", p->fule, p->maxFule, trashCollection, gameLevel);

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
            
        }
        printf("\n");//new line 
    }
}

void initaliseGame(player *p, mapData *map, astroidData *astroids) {
    srand(time(NULL));
    readFile();

    gameLevel = 9;

    p->x = ScreenX / 2;
    p->y = ScreenY / 2;
    p->hp = 100;
    p->maxHp = 100;
    p->fule = 50;
    p->maxFule = 50;

    genMap(map);
    genAstroids(astroids);
}

int main() {

    //initalising structs
    player player1;
    mapData map[ScreenX * ScreenY];
    astroidData astroids[maxAstroids];

    initaliseGame(&player1, map, astroids);

    //game loop (q to quit)
    while (input != 'q') {

        if (strcmp(globalEventFlag, "DEAD") == 0) {
            break;
        } else if (strcmp(globalEventFlag, "LEVEL_UP") == 0) {
            nextLevelLoad(&player1, map, astroids);
        } else if  (strcmp(globalEventFlag, "WIN") == 0){
            printf("wou won!!!!");
            break;
        }

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

        strcpy(globalEventFlag, ""); // reset flag

        gameLoopCheck(&player1, map, astroids, &trashCollection);

    }
    writeFile();

    return 0;
}