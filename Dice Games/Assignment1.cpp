//Compile with: g++ -sdt=c++0x Assignment1.cpp -o Assignment1
//This is to include all wanted functions from modules

#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <typeinfo>
#include <vector>
#include <math.h>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

double rnd () //function to generate a double with a random value between 1 and 0
{
  float rnd_float; //defines a variable as a float
  rnd_float  = float(rand()) / float( RAND_MAX ); //sets the variables value as that of a random number divided by the highest value of said random number
  return rnd_float; //returns said variable to where the function was called
}

int dice(int n) //function to simulate dice of n sides (n limited to approx 1000 due to code)
 {
   double rnd_result=rnd (); //sets a variable as a random float between 0 and 1
   int dice_result=(int(round(rnd_result*10000))%n)+1; //uses said variable to generate an integer between 0 and n-1 and adding one
   return dice_result; //returns said generated integer where ther function was called
}

int two_dice(int n) //function to simulate two dice of n sides
 {
   int result; //defines a integer variable
   result=dice(n); //sets value of that of the dice function for a n sided dice
   result+=dice(n); //adds another value of the dice function for an n sided dice
   return result; //returns result variable to where the function was intitially called
}


int main() //main body of the code
{
  srand(time(NULL)); //generates random seed from which to generate random numbers for the whole body of code
  
  //part A of the code which regards question 1, variables in this segment are notated with an _a to identify them as such
  vector <double> Ans_a; //defines a list of floats to append results to
  double lim_a; //defines a float variable as un upper limit 
  cout<< endl<<"Please input random float generator sample size in integer or float format"<< endl; //outputs a prerequisite to the input of the upper limit
  cin >> lim_a; //allows input of the upper limit
  double total_a=0; //sets a variable to total up the random floats generated
  for (int i=0; i<lim_a; i++) //sets up a for loop that repeats for a total amount of times upto the upper limit of generations
  {
    double random_a=rnd(); //uses the rnd() function to generate a float between 0 and 1
    Ans_a.push_back(random_a); //adds the generated float to a list of results
    total_a+=random_a; //adds the float to the total
  }
  double Mean_a=total_a/lim_a; //calculates the mean of the generated results
  double Var_a; //sets up a variable to hold the variance
  //cout<<total_a<<endl<<Mean_a<<endl; //print to see the results from part a code during testing
  for (int i=0; i<lim_a; i++) //an aditional loop that repeats upto the upper limit to access each generated value in the list of results
  {
    Var_a += ((Ans_a.at(i)-Mean_a)*(Ans_a.at(i)-Mean_a)); //sums the (x-mean(x))^2 part of the variance within the loop
  }
  Var_a=Var_a/lim_a; //divides the variance sum by the upper limit to find the true variance
  cout<<"The caclulated variance for a sample size of "<< lim_a << " is " << Var_a << endl; //outputs the results to question 1 /part a of the code
  cout<<"The predicted variance as the sample size increases towards infinity is "<< double(1.0/12.0)<<endl; //outputs the expected results to question 1 /part a of the code

  cout<<endl<<endl; //adds a break in the output
  
  //part B of the code which regards question 2, variables in this segment are notated with an _b to identify them as such
  vector <int> Ans_b; //defines a list of integers in which we can tally results in
  for(int i=0; i<=10;i++) //loops 11 times to give the amount of possible outcomes of adding two six sided dice
    {
      Ans_b.push_back(0); //sets all tally inputs as the intial value of zero
    }
  vector <int> NV_b; //sets up a vector to hold the wanted iterations to be ran which is N giving NV_b the N vector in part b
  NV_b.push_back(100); //adds a wanted iteration which will be ran (100)
  NV_b.push_back(500); //adds a wanted iteration which will be ran (500)
  NV_b.push_back(1000); //adds a wanted iteration which will be ran (1000)
  NV_b.push_back(10000); //adds a wanted iteration which will be ran (10000)
  NV_b.push_back(50000); //adds a wanted iteration which will be ran (50000)
  //cout<<NV_b.size()<<endl; //used to test .size() function to use in a for loop and see if all values added to the vector during testing
  for(int N=0; N<NV_b.size(); N++) //runs a loop to allow access using Sample_Vector.at(N) by running an integer from 0 to Sample_Vector.size()
    {
      for (int iterations=0; iterations<= NV_b.at(N);iterations++) //runs for the number of iterations as specified in the iteration vector
      {
	int result_b=two_dice(6); //runs the two dice function for a six sided die
	Ans_b.at(result_b-2)+=1; //adds result to the result tally vector
      
      }
      for(int i=0; i<=10;i++) //loops 11 times to give the amount of possible outcomes of adding two six sided dice
	{
	  string Ns=to_string(NV_b.at(N)); //creates a string of the number of iterations
	  string filename = "dice_" + Ns  + ".dat"; //sets filename to be used when writing to .DAT file
	  //cout<<filename<<endl; //used to diagnose issues with to_string() function, had to compile using g++ -std=c++0x filename.cpp -o filename
	  ofstream outfile (filename); //creates or sets file to output to using the defined output filename
	  outfile << Ans_b.at(i) <<"\n"; //writes the result tally to the output file
	  cout<<Ans_b.at(i)<<" rolls of "<< i+2 << " in a sample of "<<NV_b.at(N)<<endl; //outputs values of all results for each iteration
	  Ans_b.at(i)=0; //sets all tally inputs as the intial value of zero
	}
    }
  
  cout<<endl<<endl; //adds a break in the output
  
  //part C of the code which regards question 3, variables in this segment are notated with _c to identify them as such
  vector <int>  Wins_c; //defines a vector to hold the rounds where wins take place
  vector <int>  Losses_c; //defines a vector to hold the rounds where losses take place
  vector <double>  WLRatio_c; //defines a vector to hold the ratio of wins to losses in each round
  for(int i=0;i<=20;i++) //loop to set up empty values in each vector to add a tally to
    {
      Wins_c.push_back(0); //sets empty value as stated
      Losses_c.push_back(0); //sets empty value as stated
      WLRatio_c.push_back(0); //sets empty value as stated
    }
  for(int iterations_c=0;iterations_c<10000;iterations_c++) //loops for 10000 iterations as the problem asks
    {
      int check_c=0; //sets up a variable to later allow the breaking of a while loop
      int counter_c=0; //sets or resets a counting variable (upto 20) for placing values in the previously defined vectors
      int result_c=two_dice(6); //runs the two_dice function to define the initial result
      if (result_c==7 or result_c==11) //checks if the initial result is a winning result
	{
	  Wins_c.at(0)+=1; //adds a tally to the win vector at position 0 (round 1)
	}
      else if(result_c==2 or result_c==3 or result_c==12) //checks if the initial result is a losing result
	{
	  Losses_c.at(0)+=1; //adds a tally to the losses vector at possition 0 (round 1)
	}
      else //if the initial reult was neither a loss or win the following code takes place
	while(check_c==0) //loops while check_c is zero and will break when changed by a win or loss
	  {
	    if (counter_c<20) //checks check_c is bellow 20 to make sure that the vectors aren't exceeded in length when called
	      {
		counter_c+=1; //adds one to the counter variable to correctly add to the vector tally position
	      }
	    int last_result_c=result_c; //sets up the "point" for this round as the previous rounds result
	    result_c=two_dice(6); //runs the two_dice function to define this rounds result
	    if(result_c==(last_result_c)) //checks if this round result equals the point (last rounds result) and if so is a win
	      {
		Wins_c.at(counter_c)+=1;  //adds 1 to the appropriate win tally using the counter variable to reference position within the vector
		check_c=1; //sets check to 1 and breaks the while loop due to the win
	      }
	    else if(result_c==7) //checks if this rounds result is equal to 7 which is a loss
	      {
		Losses_c.at(counter_c)+=1; //adds 1 to the appropriate loss tally using the counter variable to reference position within the vector
		check_c=1; //sets check to 1 and breaks the while loop due top the loss
	      }
	  }
    }
  int Total_Wins_c=0; //sets a variable to total all wins to
  for(int i=0;i<20;i++) //loop to access all points on the vectors
    {
      WLRatio_c.at(i)=float(Wins_c.at(i))/float(Losses_c.at(i)); //defines win to loss ratio for each round
      cout<<"Wins at round "<<i+1<<": "<<Wins_c.at(i)<<", Losses at said round : "<< Losses_c.at(i)<<" giving a ratio of : "<< WLRatio_c.at(i)<< endl; //appropriately outputs results of wins, losses and their ratio for each round
      Total_Wins_c+=Wins_c.at(i); //adds each round to the total variable
    }
  Total_Wins_c+=Wins_c.at(20); //adds all rounds above 20 to total wins
  WLRatio_c.at(20)=float(Wins_c.at(20))/float(Losses_c.at(20)); //finds win loss ratio for rounds above 20
  cout<<"Wins at rounds above 20: "<<Wins_c.at(20)<<", Losses at said rounds : "<< Losses_c.at(20)<<" giving a ratio of : "<< WLRatio_c.at(20)<<endl; //outputs results of all round above 209 for wins, losses and their ratio
  cout<<"Total Wins : "<< Total_Wins_c << " Total Losses : "<<(10000-Total_Wins_c)<< endl; //outputs total wins and total losses
  
  return 0;
}
