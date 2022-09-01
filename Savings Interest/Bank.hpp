#include <iostream>
#include <string>
#include <math.h>


using namespace std;

//function to convert string inputs into numerical ones
//note that "1a2a3a4" is invalid but "£ 123.12" is not as non-numerical chars are only allowed at begining and end of the string (except the '.')
double str_to_funds(string input)
{
  //defines initial variables including a flag
  double pound=0;
  double penny=0;
  int flag=0;
  for(int i=0; i<input.size();i++)
    {
      //checks to see if '.' seperating pound and pennies is present
      if (input[i]!='.')
	{
	  //if not checks input is numerical
	  if (int(input[i])>=48 and int(input[i])<=57)
	    {
	      //flag set to 1 when '.' reached, so if flag is 0 it adresses the pound variable
	      if(flag==0)
		{
		  //increases said variable
		  pound=pound*10+int(input[i])-48;
		}
	      //otherwise if flag is 1 it adresses the pennies variable
	      else if(flag==1)
		{
		  //increases said variable
		  penny=penny*10+int(input[i])-48;
		}
	    }
	  else
	    {
	      //if not numerical checks that it isn't at the begining ("£ ") or end ("%") to allow for a variation of input allowed to the user
	      if(i>2 and i<(input.size()-1))
		{
		  //sets flag to 2, so pounds and pennies cannot be added to and breaks the loop
		  flag=2;
		  break;
		}
	    }
	}
      else
	{
	  //if '.' detected raises flag to 1 to adress the pennies variable
	  flag=1;
	}
    }
      //checks flag is not valid
  if(flag>1)
    {
      //if so returns a message to the user and returns 0 as result as not to crash the code
      cout<<"invalid input"<<endl;
      return 0.0;
    }
  else
    {
      //returns the result to the closest penny 2 d.p.
      return((floor((pound+(penny/100))*100))/100);
    }
};


//defines class BanckAccount
class BankAccount
{
  //defines private (non-accessable) members of the class
private:
  double funds;
  double rates;
  //defines public (accessable) members of the class
public:
  //sets up inputs to create a new variable of this class using numerical inputs(assumes rates given as a percentage)
  BankAccount(double pounds, double pennies, double rate){funds=double (pounds)+double((pennies)/100); rates=rate;};
  BankAccount(double pounds,double rate){funds=double (pounds+0.00); rates=rate;};

  //sets up inputs to create a new variable of this class using string inputs(assumes rates given as a percentage)
  BankAccount(string balance, string rate){funds=str_to_funds(balance); rates=str_to_funds(rate);};

  //sets up new variable of this class given no inputs
  BankAccount(){funds=0.0; rates=0.0;};
  
  //Functions that use/ call parts of the privatemembers
  double get_funds(); double next_years_funds();
  //operator overloads

  //overloads << operator to allow the code 'cout<< BankAccount;' to function and output the details of said account
  friend ostream& operator <<
(ostream& os,const BankAccount& A)
  { os<<"Balance: £ "<<A.funds<<endl<<"Rate (%): "<<A.rates<<endl; return os;}
};
//defines function results outputs (note rates as a percentage must be divided by 100 to give a ratio)
double BankAccount:: get_funds(){return funds;}
double BankAccount:: next_years_funds(){return funds*pow(1+rates/100,12);}
