#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <cmath>
#include <ctime>

/***
    Edge
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

/**
   MST function. Using Kruskal's algm
 **/
void MST(City * city, unsigned int length, std::vector<Edge> &mst)
{
  // finished vertex list
  unsigned int *finish = (unsigned int *)malloc(sizeof(unsigned int)*length);

  // priority queue to store edges closest to MST
  std::vector<Edge> PQ2;
  for(unsigned int i=0;i<length;i++)
    {
      finish[i] = 0;
      for(unsigned int j=0;j<length;j++){
	Edge temp2;
        temp2.u = i;
        temp2.v = j;
	double distance = sqrt((double)((city[i].x-city[j].x)*(city[i].x-city[j].x) + (city[i].y-city[j].y)*(city[i].y-city[j].y)));
	temp2.d = distance;
	PQ2.push_back(temp2);
      }
    }
  finish[0] = 1;
  std::make_heap(PQ2.begin(), PQ2.end());
  std::sort_heap(PQ2.begin(), PQ2.end());
  while(!PQ2.empty())
    {
      Edge tempEdge = PQ2.front();
      PQ2.erase(PQ2.begin());
      if(finish[tempEdge.u] == 1 && finish[tempEdge.v] == 0){
	// one in the finish list, the other is not
	mst.push_back(tempEdge);
	finish[tempEdge.v] = 1;
      }
    }
}

