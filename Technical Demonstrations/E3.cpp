#include <iostream>
#include <vector>
#include "Infection.hpp"
#include <time.h>
#include <stdlib.h>
#include <cmath>
#include <fstream>

using namespace std;

//generates a random number between 0 and x-1
int rnd(int x)
{
  return (int(floor(x*(float(rand())/float(RAND_MAX)))));
}
int main()
{
  //sets random seed using time
  srand(time(NULL));
  
  //testing of individual class
  //Individual A; //defualt class
  //Individual B(0,1); //not infected,nimmune
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
  Alive.push_back(0);
  vector <int> Infected;
  Infected.push_back(100);
  Infected.push_back(100);
  vector <int> Immune;
  Immune.push_back(0);
  Immune.push_back(0);
  
  //runs for 365 days to simulate a year
  for(int i=0;i<365;i++)
  {
    //runs for 50000 meetings of alive individuals
    for(int j=0;j<50000;j++)
    {
      //uses check and while loop to loop until two different alive individuals meet
      int check=0;
      //checks that two people are alive to meet
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

	//the below section I attempted to functionise, but doing so makes the code inefficient
	//checks that two individuals are different and both are alive
	if(floor(rndI)!=floor(rndII) and Inhabitants[rndI].getAlv()==1 and Inhabitants[rndII].getAlv()==1)
	{
	  //if the first individual is infected and the second both isnt infected or immune, it checks to see if the infection of the second takes place due to this meeting (50%) and if so sets it as such
	  if((Inhabitants[rndI].getInf()==1 and Inhabitants[rndII].getInf()==0 and Inhabitants[rndII].getImn()==0))
	  {
	    int inf=rnd(100);
	    if(inf<50)
	    {
	      //cout<<"infected "<<rndII<<" "<<Inhabitants[rndII].getAlv()<<" "<<Inhabitants[rndII].getImn()<<endl; //used in testing
	      Inhabitants[rndII].set(1,0,1);
	    }
	  }
	  //else, if the second individual is infected and the first both isnt infected or immune, it checks to see if the infection of the second takes place due to this meeting (50%) and if so sets it as such
	  else if ((Inhabitants[rndII].getInf()==1 and Inhabitants[rndI].getInf()==0 and Inhabitants[rndI].getImn()==0))
	  {
	    int inf=floor(100*rand()/RAND_MAX);
	    if(inf<50)
	    {
	      //cout<<"infected "<<rndI<<" "<<Inhabitants[rndI].getAlv()<<" "<<Inhabitants[rndI].getImn()<<endl; //used in testing
	      Inhabitants[rndI].set(1,0,1);
	    }
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
	Infected[i+1]+=1;
	//generates a number 0 to 99, if 0 the individual dies, if 87 or higher the individual recovers
	int imnalv=rnd(100);
	//cout<<imnalv<<endl; //used for testing
	
	//checks if number is 0
	if (imnalv<1)
	{
	  //kills individual
	  //cout<<"dead "<<j<<" "<<imnalv<<" "<<Inhabitants[j].getAlv()<<" "<<Inhabitants[j].getInf()<<endl; //used for testing
	  Inhabitants[j].set(0,0,0);
	  Infected[i+1]+= -1;
	}
	//checks if number greater than 87 (99-12)
	else if (imnalv>87)
	{
	  //immunises individual
	  //cout<<"immune "<<j<<" "<<imnalv<<" "<<Inhabitants[j].getInf()<<" "<<Inhabitants[j].getAlv()<<" "<<Inhabitants[j].getImn()<<endl; //used for testing
	  Inhabitants[j].set(0,1,1);
	  Infected[i+1]+= -1;
	}
      }
      //records amount of people whom are alive and immune each day
      if(Inhabitants[j].getAlv()==1)
      {
        Alive[i+1]+=1;
      }
      if(Inhabitants[j].getImn()==1)
      {
        Immune[i+1]+=1;
      }
    }
    cout<<"Day :"<<i<<", Alive: "<<Alive[i]<<", Infected: "<<Infected[i]<<", Immune: "<<Immune[i]<<endl; //used in testing
    Alive.push_back(0);
    Infected.push_back(0);
    Immune.push_back(0);
  }
  cout<<"Day :"<<365<<", Alive: "<<Alive[365]<<", Infected: "<<Infected[365]<<", Immune: "<<Immune[365]<<endl;
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
