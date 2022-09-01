//imports needed modules including circle class
#include <iostream>
#include "Circle.hpp"

//specifies using std format
using namespace std;

//defines a funtion using the overloaded > operator to determine if two circles are equal
bool equal(Circle X, Circle Y)
{
  
  //sees if radius of X is greater than that of Y, if so they are not equal
  if(X>Y)
    {
	  cout<<"These two circles do no have equal areas (0)"<< endl;
	  return 0;
    }
  else
    {
      
      //sees if radius of Y is greater than that of X, if so they are not equal, if not then X!<Y and X!>Y meaning X==Y
      if(Y>X)
	{
	  cout<<"These two circles do no have equal areas (0)"<< endl;
	  return 0;
	}
      else
	{
	  cout<<"These two circles have equal areas (1)"<<endl;
	  return 1;
	}
    }
}

//starts main bodyt of the program
int main()
{
  
//defines circle A & B, creating a third from their addition using the overloaded '+' between the two original circles A & B
Circle A(3,2,1);
Circle B(4,5,6);
Circle C = A+B;
 
//demonstrates the .get_ functions by finding them for C and outputting them
double Crad=C.getRadius();
double Cx= C.getX();
double Cy= C.getY();
double Ca= C.getArea();
cout<<"For C, Radius = "<<Crad<<", with coordinates (x,y) =  ("<<Cx<<","<<Cy<<"), with Area = "<<Ca<<endl;
 
//outputs each circle using the overloaded '<<', allowing for C's variables to be compared to those taken by the .get_ functions and vice versa
cout<<endl<<"For Circle A: "<<A<<endl<<"For Circle B: "<<B<<endl << "For Circle C: "<<C<<endl;
 
//runs equal function to see if overloaded > operator works for r1<r2, r1=r1 and r1>r2 by using A, B and C being r1 and B being r2
 cout<<"For A,B, equal status is: ";
 bool AB=equal(A,B);
 cout<<"For B,B, equal status is: ";
 bool BB=equal(B,B);
 cout<<"For C,B, equal status is: ";
 bool CB=equal(C,B);
 cout<<"As bools for B this can be displayed as follows: "<<AB<<", "<<BB<<", "<<CB<< endl;
 
//ends program
return 0;
}
