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
   Euclidean distance
 **/

unsigned int G(unsigned int x1, 
	       unsigned int y1, 
	       unsigned int x2, 
	       unsigned int y2) {return (unsigned int)sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));}

/**
   Herustic function
 **/
unsigned int H(unsigned int x1, 
	       unsigned int y1, 
	       unsigned int x2, 
	       unsigned int y2, 
	       unsigned int ex, 
	       unsigned int ey) {return (G(x1, y1, x2, y2) - G(x2, y2, ex, ey));}

/**
   Total cost function
 **/

unsigned int F(unsigned int x1, 
	       unsigned int y1, 
	       unsigned int x2,
	       unsigned int y2,
	       unsigned int ex,
	       unsigned int ey) {return (G(x1, y1, x2, y2) + H(x1, y1, x2, y2, ex, ey));}

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
   A* Algorithm
 **/
extern void AStar(City * city, unsigned int length);

/**   
   Local Search function
 **/
extern void LocalSearch(City * city, unsigned int length);


/**
   TSP API
 **/
extern void TSP(void (*algm)(City *, unsigned int), 
		City * city, unsigned int length)
{
  if(!(algm == &AStar || algm == &LocalSearch))
    {
      fprintf(stderr, "Algorithm not defined\n");
    }
  else (*algm)(city, length);
}

