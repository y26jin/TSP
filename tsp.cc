#include "tsp.h"
/**
   TSP function implementation

int TSP(void (*algm)(void))
{
  int err = 0;
  (*algm)();
  return err;
}
**/

int main(int argc, char* argv[]){
  /**
     There are two arguments to be passed in: \
     1. Target file name \
     2. The algorithm \
   **/
  fprintf(stdout, "A* algorithm for finding TSP\n");
  fprintf(stdout, "Now pick the target data...\n");
  
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

  /**
     Run algorithm. \
   **/
  if(algm == ASTAR)
    {
      TSP(AStar);
    }
  else if(algm == LOCALSEARCH)
    {
      TSP(LocalSearch);
    }
  else
    {
      fprintf(stderr, "What in the world are you running?\n");
      exit(3);
    }

  return 0;
}
