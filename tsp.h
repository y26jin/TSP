#include <fstream>
#include <sstream>
#include <cmath>

// Algorithm macro
#define ERROR_ALGM -1
#define ASTAR 1
#define LOCALSEARCH 2
unsigned int algm; // indicate which algorithm is running
unsigned int numCity = -1; // number of cities

#define BUFF_SIZE 40 // buff for reading file line by line
#define CITY_SIZE 26 // max number of cities

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
extern void TSP(void (*algm)(void))
{
  if(!(algm == &AStar || algm == &LocalSearch))
    {
      fprintf(stderr, "Algorithm not defined\n");
    }
  else (*algm)();
}

/**
   City Structure
 **/
struct City
{
  char label; // which city is it? ABCDEFG?
  unsigned int x; // x coordinate
  unsigned int y; // y coordinate
};

