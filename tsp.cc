#include "tsp.h"

/**
   A* Algorithm
 **/

void AStar(City * city, unsigned int length)
{
  int Nodes = 0;
  vector<Node> open;
  vector<Node> close;
  vector<Node> cities;
  //  map<Node, Node> came_from;
  int *came_from = (int*)malloc(sizeof(int)*length);

  int index = 0;
  for(index=0;index<length;index++){
    Node temp;
    came_from[index] = -1;
    for(int i=0;i<index;i++){
      temp.move.push_back(1);
    }
    for(int i=index;i<length;i++){
      temp.move.push_back(0);
    }
    temp.city = city[index];
    temp.gScore = 0;
    temp.fScore = MST(city,length,temp.move,index);

    cities.push_back(temp);
  }

  open.push_back(cities[0]);
  Node current;
  int isGoal = 0;
  while(!open.empty()){
    // heapify
    make_heap(open.begin(), open.end());
    sort_heap(open.begin(), open.end());

    // get the least f-value node
    //    Node current = open.front();
    current=open.front();
    if(current.city.label == 'A' && isGoal != 0){
      // finished
      fprintf(stdout,"Done\n");
    }
    isGoal = 1;
    open.erase(open.begin());
    close.push_back(current);
    fprintf(stdout, "current = %c\n", current.city.label);

    // what open set looks like now
    vector<Node>::iterator it;
    fprintf(stdout,"open set = ");
    for(it=open.begin();it!=open.end();it++){
      fprintf(stdout, "%c ",(*it).city.label);
    }
    fprintf(stdout,"\n");

    // what close set looks like now
    fprintf(stdout,"close set = ");
    for(it=close.begin();it!=close.end();it++){
      fprintf(stdout, "%c ",(*it).city.label);
    }
    fprintf(stdout,"\n");

    // generate neighbor
    vector<Node> neighbor;
    fprintf(stdout, "current neighbors = ");
    for(it=cities.begin();it!=cities.end();it++){
      vector<Node>::iterator cc;
      for(cc=close.begin();cc!=close.end();cc++){
	if((*cc).city.label == (*it).city.label) break;
      }
      if(cc == close.end()){ // no nodes from close set
	neighbor.push_back(*it);
	fprintf(stdout, "%c ", (*it).city.label);
	Nodes++;
      }
    }
    fprintf(stdout,"\n");

    // traverse neighbors
    for(it=neighbor.begin(); it!=neighbor.end(); ++it){
      double tempG = current.gScore + D(current.city.x, current.city.y, (*it).city.x, (*it).city.y);
      vector<Node>::iterator tt, tt1, tt2;
      // in close set and g score is good
      // dont need to evaluate this node, switch to the next
      for(tt1=close.begin();tt1!=close.end();tt1++){
	if((*it).city.label==(*tt1).city.label) break; // if show in close set
      }
      for(tt2=open.begin();tt2!=open.end();tt2++){
        if((*it).city.label==(*tt2).city.label) break; // if show in open set
      }

      if(tt1 != close.end() && tempG>=(*it).gScore) {
	// in close set
	continue;
      }

      if(tt1 == close.end() || tempG < (*it).gScore ){
	// not in close set
	//came_from.insert(pair<Node, Node>((*it), current));
	vector<Node>::iterator ita;
	for(ita=cities.begin();ita != cities.end();ita++){
	  (*ita).move[(*it).city.label - 'A'] = 1;
	}
	came_from[(*it).city.label-'A'] = current.city.label - 'A';
	(*it).gScore = tempG;
	(*it).fScore = (*it).gScore + MST(city,length,current.move,(*it).city.label - 'A');
	
	fprintf(stdout, "path = (%c,%c), cost = %f, MST = %f\n",current.city.label,(*it).city.label,(*it).gScore, MST(city,length,current.move,(*it).city.label - 'A'));
	if(tt2 == open.end()){
	  // not in open set
	  open.push_back(*it);
	}
      }

    }
    
  }
  came_from[0] = current.city.label - 'A';
  int s = 0;
  double realCost = 0;
  do{
    fprintf(stdout, "%c is from %c, cost = %f\n", s+'A', came_from[s] + 'A', D(city[s].x, city[s].y, city[came_from[s]].x, city[came_from[s]].y));
    s = came_from[s];
    realCost = realCost + D(city[s].x, city[s].y, city[came_from[s]].x, city[came_from[s]].y);
  }while(s!=0);
  fprintf(stdout,"realCost=%f\n",realCost);
  fprintf(stdout, "number of nodes = %d\n", Nodes);
}


/**
   Local Search

// helper and miniLocalSearch do mutual recursion to go through each moveset
void miniLocalSearch(City * city, unsigned int length, char start, double p, unsigned int *moveset, int* citylist, unsigned int length1);
// helper grabs necessary info for miniLocalSearch to run
void helper(City * city, unsigned int length, unsigned int *moveset, char start, double p){
  City * newcity = NULL; 
  int curlen = 0;
  int *citylist = (int*)malloc(sizeof(int)*length);
  for(int i=0;i<length;i++){
    if(moveset[i] == 0){
      curlen++;
      newcity = (City*)realloc(newcity, sizeof(City)*curlen);
      newcity[curlen-1].label = city[i].label;
      newcity[curlen-1].x = city[i].x;
      newcity[curlen-1].y = city[i].y;
      citylist[i] = 1;
    }
    else citylist[i] = 0;
  }
  fprintf(stdout,"in helper, curlen = %d\n", curlen);  
  if(curlen == 0) return;
  else  miniLocalSearch(newcity, curlen, start, p, moveset, citylist, length);
}
// miniLocalSearch
// It does almost the same thing as LocalSearch. Primarily work on movesets and generate movesets for its children nodes
void miniLocalSearch(City * city, unsigned int length, char start, double p, unsigned int *moveset, int* citylist, unsigned int length1){
  if(length == 0){
    return;
  }

  else{
    fprintf(stdout, "in mini!\n");
    char current=start;
    int nextNum=0,currentNum=0,numVisit=0;
    double currentCost = 0;
    while(1){
      while(moveset[nextNum] == 1){nextNum=rand()%length1;}
      double tempCost = currentCost + D(city[nextNum].x, city[nextNum].y, city[currentNum].x, city[currentNum].y);

      if(currentCost > tempCost)
	{
	  numVisit++;
	  current = city[nextNum%length].label;
	  moveset[nextNum] = 1;
	  currentNum = nextNum%length;
	  currentCost = tempCost;

	  fprintf(stdout, "%c ", current);

	  helper(city, length, moveset, current, p);
	}
      else
	{
	  //with probability p...                                                                                                                                              
	  double tempP = rand()%10000 / 10000;
	  if(tempP < p)
	    {
	      numVisit++;
	      current = city[nextNum%length].label;
	      moveset[nextNum] = 1;
	      currentNum = nextNum%length;
	      currentCost = tempCost;

	      fprintf(stdout, "%c ", current);

	      helper(city, length, moveset, current, p);
	    }
	}

      // all the neighbors have been visited                                                                                                                                   
      if(numVisit == length - 1) break;
      
    }
  }
}
// LocalSearch
void LocalSearch(City * city, unsigned int length)
{
  for(unsigned int t=0;t<length;++t)
  {
      // start from node t and travel till we have a TSP
      // will try every node 
      char current = city[t].label, end = city[t].label;
      unsigned int isCurrentEnd = 0, nextNum = t, nextNum2 = t, currentNum = t, numVisit = 0;
      double currentCost = 0, temperature = 2;

      // as we choose move randomly from moveset, we can simply use an array to store moves
      unsigned int *moveset = (unsigned int*)malloc(sizeof(unsigned int) * length);
      for(int i=0;i<length;i++){moveset[i]=0;}
      moveset[t]=1;

      fprintf(stdout, "%c ", current);
      //      while(isCurrentEnd == 0)
      while(1)
	{
	  // all the neighbors have been visited                                                                                                                                   
          if(numVisit == length - 1) break;
	  // randomly choose a move 
	  while(moveset[nextNum] == 1){nextNum=rand()%length;}
	  double tempCost = currentCost + D(city[nextNum].x, city[nextNum].y, city[currentNum].x, city[currentNum].y);
	  double p = exp(-(tempCost - currentCost)/temperature);

	  if(currentCost > tempCost)
	    {
	      numVisit++;
	      current = city[nextNum].label;
	      moveset[nextNum] = 1;
	      currentNum = nextNum;
	      currentCost = tempCost;

  	      fprintf(stdout, "%c ", current);

	      helper(city, length, moveset, current, p);
	    }
	  else
	    {
	      //with probability p...
	      double tempP = rand()%10000 / 10000;
	      if(tempP < p)
		{
		  numVisit++;
		  current = city[nextNum].label;
		  moveset[nextNum] = 1;
		  currentNum = nextNum;
		  currentCost = tempCost;

		  fprintf(stdout, "%c ", current);

		  helper(city, length, moveset, current,p);
		}
	    }
	  

	}
      
      fprintf(stdout, "%c cost = %f\n", end, currentCost);
      fprintf(stdout, "\n");
  }
}
**/

int main(int argc, char* argv[]){
  /**
     There are two arguments to be passed in: \
     1. Target file name \
     2. The algorithm \
   **/
  srand(time(NULL));
  fprintf(stdout, "=========================\n");
  // concatenate target file name in trail to relative path
  char targetName[40] = "./problemA1/";
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
  ifstream targetFile(targetName);
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
  stringstream ss;
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
