//imports needed modules including the custom BankAccount class from my file
#include <iostream>
#include "Bank.hpp"
#include <fstream>
#include <iomanip>

//uses namespace to simplify code (no [std::] at the start)
using namespace std;

//starts main body of the program
int main()
{
  //sets output to 2 d.p.
  cout<<fixed<<setprecision(2);
  cout<<endl;
  
  //defines a list of BankAccount variables, sets them as similar to test against for a range of inputs both string and numerical
  //this includes "£ pounds.pennies","rates" as well as " £ pound.00","rates" or "pound.00","rates%" ect..
  BankAccount Accounts [5];
  Accounts[0]=BankAccount("£ 159.29","0");
  Accounts[1]=BankAccount(159,29,1);
  Accounts[2]=BankAccount("£ 159.00","2.0%");
  Accounts[3]=BankAccount(159,2);
  Accounts[4]=BankAccount();

  //both prints, and saves to a file (Bank.txt), each BankAccount and its funds after interest
  //opens file
  ofstream bankfile ("Bank.txt");
  for(int i=0;i<5;i++)
    {
      //calculates next years funds to be printed and saved 
      double nyf=Accounts[i].next_years_funds();
      
      //outputs here
      cout<<Accounts[i];
      cout<<"Next Years Funds (£): "<<nyf<<endl<<endl;

      //saves here
      bankfile<<Accounts[i];
      bankfile<<"Next Years Funds (£): "<<nyf<<endl<<endl;
    }
  //closes file
  bankfile.close();

  //ends main()
  return 0;
}
