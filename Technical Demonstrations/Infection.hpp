#include <iostream>
using namespace std;

class Individual
{
  //Defines private members of class
private:
  bool infected;
  bool immune;
  bool alive;
  //Defines public members of class
public:
  Individual(bool inf, bool imn, bool alv) {infected=inf;immune=imn;alive=alv;}
  Individual(bool inf, bool imn) {infected=inf;immune=imn;alive=1;}
  Individual(bool inf) {infected=inf;immune=0;alive=1;}
  Individual() {infected=0;immune=0;alive=1;}
  //Functions that act on or call parts of the private members
  bool getInf(); bool getImn(); bool getAlv();
  void show(); void set(bool, bool, bool);
};
bool Individual:: getInf(){return infected;}
bool Individual:: getImn(){return immune;}
bool Individual:: getAlv(){return alive;}
void Individual:: show(){cout<<"The individual has an alive status of "<<alive<<", an infection status of "<<infected<<", and an immune status of "<<immune<<endl;}
void Individual:: set(bool inf,bool imn, bool alv) {infected=inf; immune=imn;alive=alv;}
