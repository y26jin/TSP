#ifndef TSP_H
#define TSP_H
#endif

#include <fstream>
#include <sstream>
#include <cmath>
#include <ctime>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>

// Algorithm macro
#define ERROR_ALGM -1
#define ASTAR 1
#define LOCALSEARCH 2

unsigned int algm; // indicate which algorithm is running
unsigned int numCity = -1; // number of cities

#define BUFF_SIZE 40 // buff for reading file line by line
#define CITY_SIZE 26 // max number of cities

using namespace std;

/**
   Euclidean distance
 **/

double D(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2)
{
  return sqrt( (double)((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2)) );
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

/**
   Edge structure
 **/
struct Edge
{
  unsigned int u;
  unsigned int v;
  double d;
  bool operator<(const Edge &de) const
  {
    return d < de.d;
  }
};


struct Node
{
  City city;
  double gScore;
  double fScore;
  vector<unsigned int> move;
  bool operator<(const Node &n) const
  {
    return fScore < n.fScore;
  }
};

struct find_node
{
  char label;
find_node(char a):label(a) {}
  bool operator() (const Node &b) const
  {
    return label == b.city.label;
  }
};

/**
   MST. Using Kruskal's algm
 **/
double MST(City * city, unsigned int length, vector<unsigned int> &move, unsigned int node)
{
  double cost = 0;
  vector<Edge> PQ2;
  vector<Edge> mst;
  unsigned int *finish = (unsigned int*)malloc(sizeof(unsigned int)*length);
  
  for(unsigned int i=0;i<length;i++)
    {
      finish[i] = move[i];
      for(unsigned int j=0;j<length;j++){
        Edge temp2;
        temp2.u = i;
        temp2.v = j;
	double distance = D(city[i].x, city[i].y, city[j].x, city[j].y);
        temp2.d = distance;
        PQ2.push_back(temp2);
      }
    }
  finish[node] = 1;

  make_heap(PQ2.begin(), PQ2.end());
  sort_heap(PQ2.begin(), PQ2.end());
  while(!PQ2.empty())
    {
      Edge tempEdge = PQ2.front();
      PQ2.erase(PQ2.begin());
      if(finish[tempEdge.u] == 1 && finish[tempEdge.v] == 0){
        finish[tempEdge.v] = 1;
	cost = cost + tempEdge.d;
      }
    }
  return cost;
}

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

