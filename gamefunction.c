#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "gamefunction.h"

// global variable definitions
int ScreenX ;
int ScreenY ;
int astroidDamage = 100;
char globalEventFlag[10]; 
int gameLevel;
int trashCollection;
int maxAstroids;
char input; 
char null;

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
    //printf("the character is a: %s\n", type);
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

        if (astroids[i].x < 0 || astroids[i].x >= ScreenX || astroids[i].y < 0 || astroids[i].y >= ScreenY) {
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
    FILE *fptr;
    fptr = fopen("gametxt.txt", "r");
        while (fgets(txt, 200, fptr)) {
            printf("%s \n", txt);
        }
        fclose(fptr);
        printf("Press any key to load:  ");
        scanf(" %c", &null);

}

void writeFile(){
    int fscore;
    FILE *fptr;
    fptr = fopen("bestScore.txt", "r");
    fscanf(fptr, "%d", &fscore); 
    printf("the current highets score was %d\n", fscore);
    printf("you scored:  %d\n", gameLevel);

    if ( gameLevel > fscore){
    fptr = fopen("bestScore.txt", "w");
    fprintf(fptr, "%d\n", (gameLevel));
            fclose(fptr);
    }
}
    

void gameLoopCheck(player *p, mapData *map, astroidData *asteroids) {

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

    // player collision and collection check
    if (strcmp(map[i].type, "Trash") == 0) {
        strcpy(map[i].type, "Empty");
        trashCollection++;
    } else if (strcmp(map[i].type, "Astro") == 0) {
        printf("hittttt");
        p->hp -= 100;
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

    printf("\n\n--- Level %d Complete! ---\n", gameLevel - 1);
    printf("Use your collected trash (%d) to upgrade your ship:\n", trashCollection);
    printf("1. No upgrade (Free)\n");
    printf("2. Increase max fuel by +10 (Cost: 10 trash)\n");
    printf("3. Increase max HP by +50 (Cost: 10 trash)\n");
    printf("4. Heal +25 HP (Cost: 10 trash)\n");

    scanf(" %s", upgrade);

    while ((typeCheck(upgrade, "int")) == 0){
        printf("please enter your choice  1-2-3: ");
        scanf(" %s", upgrade);
        }

    switch (upgrade[0]) {
        case '1':
            printf("no upgrade selected prepare for the next level....\n");
            break;

        case '2':
            if (trashCollection >= 10) {
                trashCollection -= 10;
                p->maxFule += 10;
                printf("fuel tank upgraded!! \n max fuel is now %d \n", p->maxFule);
            } else {
                printf("you dont have enough trash\n prepare for the next level.... \n");
            }
            break;

        case '3':
            if (trashCollection >= 10) {
                trashCollection -= 10;
                p->maxHp += 50;
                printf("max HP increased!! \n  max HP is now %d\n", p->maxHp);
            } else {
                printf("you dont have enough trash\n prepare for the next level.... \n");
            }
            break;

        case '4':
            if (trashCollection >= 5) {
                trashCollection -= 5;
                p->hp += 25;
                if (p->hp > p->maxHp) p->hp = p->maxHp;
                printf("you healed 25 HP!! /n your HP is now %d \n", p->hp);
            } else {
                printf("you dont have enough trash\n prepare for the next level.... \n");
            }
            break;
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

    printf("fule: %d/%d | Trash: %d | level: %d\n", p->fule, p->maxFule, trashCollection, gameLevel);

    // looping through the 1d array 
    //using x and y to break in to 2d 
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

    gameLevel = 1;

    p->x = ScreenX / 2;
    p->y = ScreenY / 2;
    trashCollection = 0;
    genMap(map);
    genAstroids(astroids);
}

void setDifficulty(player *p) {
    char choice[10];

    printf("Select Difficulty:\n");
    printf("1. Easy\n");
    printf("2. Normal\n");
    printf("3. Hard \n");
    printf("Enter 1-3: ");
    scanf("%s", choice);

    while ((typeCheck(choice, "int")) == 0){
        printf("please enter your choice  1-2-3: ");
        scanf(" %s", choice);
        }

    switch (choice[0]) {
        case '1': // Easy
            ScreenX = 20;
            ScreenY = 10;
            maxAstroids = 5;
            p->hp = 100;
            p->maxHp = 100;
            p->fule = 60;
            p->maxFule = 60;
            break;
        case '2': // Normal
            ScreenX = 30;
            ScreenY = 15;
            maxAstroids = 10;
            p->hp = 100;
            p->maxHp = 100;
            p->fule = 80;
            p->maxFule = 80;
            break;
        case '3': // Hard
            ScreenX = 40;
            ScreenY = 20;
            maxAstroids = 15;
            p->hp = 100;
            p->maxHp = 100;
            p->fule = 100;
            p->maxFule = 100;
            break;
    }
}