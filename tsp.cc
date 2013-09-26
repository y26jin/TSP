#include "tsp.h"

/**
   A* Algorithm
 **/
void AStar(City * city, unsigned int length)
{
  for(unsigned int t=0;t<length;++t)
    {      
      char current = city[t].label; // current step
      unsigned int numVisit = 1, realCost = 0, funcCost = 0;

      unsigned int *neighbor = (unsigned int *)malloc(length * sizeof(unsigned int));
      for(int i=0;i<length;++i)
	{
	  if(i == t) neighbor[i] = 1;
	  else neighbor[i] = 0;
	  fprintf(stdout, "%d ", neighbor[i]);
	}
      fprintf(stdout,"\n");
      fprintf(stdout, "%c ", current);

      while(numVisit < length)
	{
	  unsigned int i = 0, minF = 65536, minNum = 0, isfirst = 0;
	  for(i=0;i<length; ++i)
	    {
	      // possible nodes in between start and end
	      if(neighbor[i] == 1) continue;
	      
	      if(neighbor[i] == 0)
		{
		  unsigned int tempF = F(city[current-city[0].label].x, city[current-city[0].label].y,
					 city[i].x, city[i].y,
					 city[t].x, city[t].y);
		  if(isfirst == 0) {
		    minF = tempF;
		    minNum = i;
		    isfirst++;
		  }
		  else if(minF > tempF)
		    {
		      minF = tempF;
		      minNum = i;
		    }
		}
	    }
	  // actual cost of this move
	  realCost = realCost + G(city[t].x, city[minNum].x, city[t].y, city[minNum].y);
	  funcCost = funcCost + minF;
	  
	  /**	      fprintf(stdout, "Admissble Check: H=%d, H*=%d, minF=%d\n", 
		   H(city[current-start].x, city[current-start].y,
		   city[minNum].x, city[minNum].y,
		   city[end-start].x, city[end-start].y),
		   G(city[current-start].x, city[current-start].y,
		   city[end-start].x, city[end-start].y),
		   minF);
	  **/
	  current = city[minNum].label;
	  numVisit++;
	  neighbor[minNum] = 1;
	  fprintf(stdout, "%c ", current);
	}
      fprintf(stdout, "%c\n", city[t].label);
      fprintf(stdout, " Actual Cost For start %c end %c = %d\n", city[t].label, city[t].label, realCost);
      for(int i=0;i<length;i++){fprintf(stdout, "%d ", neighbor[i]);}
      fprintf(stdout, "\n");
    }
}


/**
   Local Search
 **/
void LocalSearch(City * city, unsigned int length)
{
  
}

int main(int argc, char* argv[]){
  /**
     There are two arguments to be passed in: \
     1. Target file name \
     2. The algorithm \
   **/
  fprintf(stdout, "=========================\n");
  // concatenate target file name in trail to relative path
  char targetName[20] = "./problemA1/";
  strncat(targetName, argv[1], sizeof(targetName));
  if(targetName == NULL)
    {
      fprintf(stderr, "Target name failed to concatenate\n");
      exit(1);
    }
  else
    {
      fprintf(stdout, "Target name is %s\n", targetName);
    }

  // test if the target file exists
  std::ifstream targetFile(targetName);
  if(targetFile.good())
    {
      fprintf(stdout, "Target file exists.\n");
    }
  else
    {
      fprintf(stderr, "Target file does not exist. Check it once more!\n");
      exit(1);
    }
  fprintf(stdout, "=========================\n");
  /**
     Pick the algorithm \
   **/
  if(strncmp(argv[2], "A-Star", 6) == 0)
    {
      algm = ASTAR;
    }
  else if(strncmp(argv[2], "Local-Search", 12) == 0)
    {
      algm = LOCALSEARCH;
    }
  else
    {
      algm = ERROR_ALGM;
    }

  /**
     Load data into memory. \
   **/
  std::stringstream ss;
  char buff[BUFF_SIZE];  
  City *cities;
  unsigned int index = 0;

  while(targetFile.getline(buff, BUFF_SIZE))
    {
      ss<<buff;
      if(numCity == -1)
	{
	  ss >> numCity;
	  cities = (City*)malloc(sizeof(City)*numCity);
	}
      else
	{
	  ss >> cities[index].label;
	  ss >> cities[index].x;
	  ss >> cities[index].y;
	  ++index;
	}
      // reset stringstream
      ss.str("");
      ss.clear();
    }
  // test loading part out
  fprintf(stdout, "numCity = %d\n", numCity);
  for(int i=0; i<numCity; ++i)
    {
      fprintf(stdout, "%c %d %d \n", cities[i].label, cities[i].x, cities[i].y);
    }

  fprintf(stdout, "========================\n");
  /**
     Run algorithm. \
   **/
  if(algm == ASTAR)
    {
      // run A* algorithm
      TSP(AStar, cities, numCity);
    }
  else if(algm == LOCALSEARCH)
    {
      // run local search
      TSP(LocalSearch, cities, numCity);
    }
  else
    {
      fprintf(stderr, "What in the world are you running?\n");
    }

  return 0;
}
