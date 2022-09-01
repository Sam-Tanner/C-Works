#include <iostream>
#include <vector>
#include "Infection.hpp"
#include <time.h>
#include <stdlib.h>
#include <cmath>
#include <fstream>

using namespace std;

//random number generator from 0 to x-1
int rnd(int x)
{
  return (int(floor(x*(float(rand())/float(RAND_MAX)))));
}

//finds result of a meeting between two Individuals
bool meeting(Individual A, Individual B)
{
  //checks if A is infected and the B both isnt infected or immune
  if((A.getInf()==1 and B.getInf()==0 and B.getImn()==0))
  {
    //generates a number using rnd(x) from 0 to 99, if below 50 (i.e. 50% of the time) it sets a flag to infect B
    int infection=rnd(100);
    if(infection<50)
    {
      //B.set(1,0,1); //doesn't work :(
      return (1);
    }
  }
  //if condition isn't met, no flag set
  return(0);
}

//checks total amount of given status of all held Individual classes
int total(vector <Individual> inhabs, int A)
{
  //sets initial total
  int tot=0;
  //runs for each individual
  for(int i=0;i<200000;i++)
  {
    //checks which total is wanted and takes said total an individual at a time
    if(A==0)
    {
      tot+=inhabs[i].getInf();
    }
    else if(A==1)
    {
      tot+=inhabs[i].getImn();
    }
    else
    {
      tot+=inhabs[i].getAlv();
    }
  }
  //returns total
  return tot;
}


int main()
{
  //sets random seed using time
  srand(time(NULL));
  
  //testing of individual class
  //Individual A; //defualt class
  //Individual B(0,1); //not infected, immune
  //A.show();
  //B.show();
  
  //testing set function
  //A.set(1,0,1); //infected, not immune, alive
  //A.show();
  //A.set(0,0,0); //not infected, not immune, not alive
  //A.show();

  //sets up a vector of 200000 individuals whom are all alive and well
  vector <Individual> Inhabitants;
  for(int i=0;i<200000;i++)
  {
    Inhabitants.push_back(Individual(0,0,1));
  }
  
  //then infects first 100 individuals in the vector
  for(int i=0;i<100;i++)
  {
    Inhabitants[i].set(1,0,1);
  }

  //testing that .get_ functions work as expected and Individuals are correctly setup for the model
  //Inhabitants[99].show(); //used for testing
  //Inhabitants[100].show(); //used for testing
  //Inhabitants[199999].show(); //used for testing
  //cout<<Inhabitants[99].getInf()<<endl; //used for testing
  //cout<<Inhabitants[99].getImn()<<endl; //used for testing
  //cout<<Inhabitants[99].getAlv()<<endl; //used for testing

  //sets up vectors to record each days total alive, infected and immune populations
  vector <int> Alive;
  Alive.push_back(200000);
  vector <int> Infected;
  Infected.push_back(100);
  vector <int> Immune;
  Immune.push_back(0);
  
  //runs for 365 days to simulate a year
  for(int i=0;i<365;i++)
  {
    //runs for 50000 meetings a day (of alive individuals)
    for(int j=0;j<50000;j++)
    {
      //uses check and while loop to loop until two different alive individuals meet
      bool check=0;
      //checks that two people are alive to meet, if not would loop forever (will still be very slow if even close to this though)
      if(Alive[i]<2)
      {
	check=1;
      }
      while(check==0)
      {
	//randomly generates invloved individuals 0 to 199999
	int rndI=rnd(200000);
        int rndII=rnd(200000);
	//cout<<rndII<<" "<<rndI<<endl; //used in testing

	//checks that the two individuals [rndI] and [rndII] are different and both are alive
	if(rndI != rndII and Inhabitants[rndI].getAlv()==1 and Inhabitants[rndII].getAlv()==1)
	{
	  //sets up a flag to see if an infection takes place
	  bool inf;
	  //uses the meeting function to determine if an infection from [rndI] to [rndII] has taken place
	  inf  = meeting(Inhabitants[rndI],Inhabitants[rndII]);
	  if(inf==1)
	  {
	    //if flag is set appropriately, infects [rndII]
	    Inhabitants[rndII].set(1,0,1);
	  }
	  //uses the meeting function to determine if an infection from [rndII] to [rndI] has taken place
	  inf=meeting(Inhabitants[rndII],Inhabitants[rndI]);
	  if(inf==1)
	  {
	    //if flag is set appropriately, infects [rndI]
	    Inhabitants[rndI].set(1,0,1);
	  }
	  //as two different individuals whom are alive were detected we set check to 1 breaking the while loop
	  //cout<<"checked"<<endl; //used in testing
	  check=1;
	}
      }
    }
    //runs a loop accessing all individuals
    for(int j=0;j<200000;j++)
    {
      //checks if individual j is infected and recording if so
      if(Inhabitants[j].getInf()==1)
      {
	//generates a number 0 to 99, if 0 the individual dies, if 87 or higher the individual recovers
	int imnalv=rnd(100);
	//cout<<imnalv<<endl; //used for testing
	
	//checks if number is 0 (99-99, meaning 1% become immune)
	if (imnalv<1)
	{
	  //kills individual off
	  //cout<<"dead "<<j<<" "<<imnalv<<" "<<Inhabitants[j].getAlv()<<" "<<Inhabitants[j].getInf()<<endl; //used for testing
	  Inhabitants[j].set(0,0,0);
	}
	//checks if number greater than 87 (99-12, meaning 12% become immune)
	else if (imnalv>87)
	{
	  //immunises individual
	  //cout<<"immune "<<j<<" "<<imnalv<<" "<<Inhabitants[j].getInf()<<" "<<Inhabitants[j].getAlv()<<" "<<Inhabitants[j].getImn()<<endl; //used for testing
	  Inhabitants[j].set(0,1,1);
	}
      }
    }
    //outputs and calculates (using total function) alive, infected and immune totals 'daily'
    //cout<<"Day :"<<i<<", Alive: "<<Alive[i]<<", Infected: "<<Infected[i]<<", Immune: "<<Immune[i]<<endl; //used in testing
    Infected.push_back(total(Inhabitants,0));
    Immune.push_back(total(Inhabitants,1));
    Alive.push_back(total(Inhabitants,2));
  }
  //outputs final day results
  cout<<"Day :"<<365<<", Alive: "<<Alive[365]<<", Infected: "<<Infected[365]<<", Immune: "<<Immune[365]<<endl;
  //sets 3 output files and then outputs all totals into them, day 0 to 365 (seperates them using ",")
  ofstream outAlive("Alive.csv");
  ofstream outInfected("Infected.csv");
  ofstream outImmune("Immune.csv");
  for(int i=0;i<366;i++)
  {
    outAlive<<Alive[i]<<",";
    outInfected<<Infected[i]<<",";
    outImmune<<Immune[i]<<",";
  }
  return 0;
}
