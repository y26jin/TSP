#include "tsp.h"

void AStar(City * city, unsigned int length, char start, char end)
{
  /**
     Find the center of gravity of all the cities and update (Cx,Cy), initH
   **/

  unsigned int sumX = 0, sumY = 0, signedArea = 0;
  // signed Area
  for(int i=0;i<length-1;++i)
    {
      signedArea =  signedArea + (city[i].x * city[i+1].y - city[i+1].x * city[i].y);
    }
  
  // Cx
  for(int i=0;i<length-1;++i)
    {
      sumX = sumX + (city[i].x + city[i+1].x) * (city[i].x * city[i+1].y - city[i+1].x * city[i].y);
    }
  sumX = sumX / (3*signedArea);

  // Cy
  for(int i=0;i<length-1;++i)
    {
      sumY = sumY + (city[i].y + city[i+1].y) * (city[i].x * city[i+1].y - city[i+1].x * city[i].y);
    }
  sumY = sumY / (3*signedArea);
  
  // update initH
  unsigned int j = 0;
  while(j<length && city[j].label != start){++j;}

  initH = G(Cx, city[j].x, Cy, city[j].y);
  
  char current = start; // current step
  do
    {
	  unsigned int currentX = 0, currentY = 0, currentNum = 0;
	  unsigned int minF = 65536, minNum = 0;
	  char minNode;
	  unsigned int i=0;
	  while(i<length && city[i].label != current){++i;}
	  
	  currentX = city[i].x;
	  currentY = city[i].y;
	  currentNum = i;
	  
	  for(i=0;i<length;++i)
	    {
	      // current node
	      if(currentNum == i)
		{
		  continue;
		}
	      else
		{
		  unsigned int tempF = F(currentX, city[i].x, currentY, city[i].y);
		  if(tempF < minF)
		    {
		      minF = tempF;
		      minNode = city[i].label;
		      minNum = i;
		    }
		}
	    }

	  current = minNode;
	  fprintf(stdout, "%c F=%d\n", current, minF);

    }while(current != end);
}

void LocalSearch(City * city, unsigned int length, char start, char end)
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
      TSP(AStar, cities, numCity, 'A', 'A');
    }
  else if(algm == LOCALSEARCH)
    {
      // run local search
      TSP(LocalSearch, cities, numCity, 'A', 'A');
    }
  else
    {
      fprintf(stderr, "What in the world are you running?\n");
    }

  return 0;
}
