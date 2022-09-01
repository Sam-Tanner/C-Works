#include <iostream>
#include <cmath>
using namespace std;

//defines pi when used to find area
float pi=3.14159265;

//defines class circle
class Circle
{
  //defines private (non-accessable) members of the circle class
private:
  double rad;
  double xvalue;
  double yvalue;
  //defines public (accessable) members of the circle class
public:
  //allows for multiple entries of Circles with default values set to zero (except radius as then it wouldn't technically exist)
  //note rad=abs(r) so that r automatically takes the magnitude of the radius so that A+B gives the 'correct' resultant C with a positive radius
  Circle(double r, double x, double y) {rad=abs(r);xvalue=x;yvalue=y;}
  Circle(double r, double x) {rad=abs(r);xvalue=x;yvalue=0.0;}
  Circle(double r) {rad=abs(r);xvalue=0.0;yvalue=0.0;}
  Circle() {rad=1.0;xvalue=0.0;yvalue=0.0;}
  //Functions that call parts of the private members
  double getRadius(); double getX(); double getY(); double getArea();
  void show();
  //operator overloads

  //overloads + to create a third circle from the addition of two others radius place directly between the two original circles
  friend Circle operator +
(const Circle& A, const Circle& B)
{ return Circle(sqrt(A.rad*A.rad+B.rad*B.rad),(A.xvalue+B.xvalue)/2,(A.yvalue+B.yvalue)/2);}

  //overloads > operator to compare two circles radius's and return a bool (yes or no, 1 or 0)
  friend bool operator >
(const Circle& A, const Circle& B)
  { return bool (A.rad>B.rad);}

  //overloads << operator to allow the code 'cout<< Circle;' to function and output the details of said circle
  friend ostream& operator <<
(ostream& os,const Circle& A)
{ os<<"Radius = "<<A.rad<<", at (x,y) = ("<<A.xvalue<<","<<A.yvalue<<")"<<endl; return os;}
};
//defines function results outputs
double Circle:: getRadius(){return rad;}
double Circle:: getX(){return xvalue;}
double Circle:: getY(){return yvalue;}
double Circle::getArea(){return (rad*rad*pi);}
void Circle::show(){cout<<"Radius of:"<<rad<<", X position:"<<xvalue<<", Y position:"<<yvalue<<endl;}
