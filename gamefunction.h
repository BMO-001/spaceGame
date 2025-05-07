#ifndef gamefunction_h
#define gamefunction_h

#include <stdbool.h>

// Global variables (declared as extern, defined elsewhere)
extern int ScreenX;
extern int ScreenY;
extern int astroidDamage;
extern char globalEventFlag[10];
extern int gameLevel;
extern int trashCollection;
extern int maxAstroids;

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

// Function declarationsbool typeCheck(char variable[], char required[]);
void genAstroids(astroidData *astroids);
void astroidLoop(astroidData *astroids, mapData *map);
void genMap(mapData *map);
void readFile();
void writeFile();
void gameLoopCheck(player *p, mapData *map, astroidData *asteroids, int *trashCollected);
void nextLevelLoad(player *p, mapData *map, astroidData *astroids);
void loadScreen(player *p, mapData *map, astroidData *astroids);
void initaliseGame(player *p, mapData *map, astroidData *astroids);

#endif 
