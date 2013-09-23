#include <fstream>
#include <sstream>
#include <cmath>

// Algorithm macro
#define ERROR_ALGM -1
#define ASTAR 1
#define LOCALSEARCH 2
int algm; // indicate which algorithm is running

// For herustic function
#define Ax 0
#define Ay 0

/**
   Euclidean distance
 **/

//#define G(x1, x2, y1, y2) sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2))
#define G(x1, x2, y1, y2) ((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2))

/**
   Herustic function
 **/

#define H(x, y) G(Ax, x, Ay, y)

/**
   Total cost function
 **/

#define F(x1, x2, y1, y2) G(x1, x2, y1, y2) + H(x2, y2)

/**
   A* Algorithm search function
 **/
extern void AStar(){fprintf(stdout, "A* algm\n");}

/**
   Local Search function
 **/
extern void LocalSearch(){fprintf(stdout, "Local Search\n");}

/**
   TSP API
 **/
extern int TSP(void (*algm)(void));
