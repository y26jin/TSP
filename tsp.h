#ifndef TSP_H
#define TSP_H
#endif

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

/**
   Center of gravity of all the points. For herustic function
 **/
#define Cx 0
#define Cy 0


/**
   Euclidean distance
 **/

#define G(x1, x2, y1, y2) ((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2))

/**
   Herustic function
 **/
unsigned int initH = 0;
#define H(x, y) G(Cx, x, Cy, y) - initH

/**
   Total cost function
 **/

#define F(x1, x2, y1, y2) G(x1, x2, y1, y2) + H(x2, y2)

/**                                                                                                                                                                                
   City Structure                                                                                                                                                                  
**/
struct City
{
  char label; // which city is it? ABCDEFG?                                                                                                                                        
  unsigned int x; // x coordinate                                                                                                                                                  
  unsigned int y; // y coordinate                                                                                                                                                  
};

/**
   Brute Force Search
 **/
extern void bruteForce(City * city, unsigned int length, char start, char end);

/**
   A* Algorithm
 **/
extern void AStar(City * city, unsigned int length, char start, char end);

/**   
   Local Search function
 **/
extern void LocalSearch(City * city, unsigned int length, char start, char end);


/**
   TSP API
 **/
extern void TSP(void (*algm)(City *, unsigned int, char, char), 
		City * city, unsigned int length, char start, char end)
{
  if(!(algm == &AStar || algm == &LocalSearch))
    {
      fprintf(stderr, "Algorithm not defined\n");
    }
  else (*algm)(city, length, start, end);
}

