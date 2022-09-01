#include <iostream>

using namespace std;

//defines a swapping function
void swapr(double *a,double *b)
{
//uses a temporary variable to hold overwritten value as the two inputted adresses are swapped
double temp=*a;
*a=*b;
*b=temp;
return;
}

//defines a transpose function
void transpose(double array[3][3])
{
//runs two integers from one 0 to 2 and the other 0 to the value of the other to only look at adresses one side of the top left, bottom right diagonal around which we transpose, then uses swapr(a,b) to swap wanted array adresses
for (int i=0; i<3; ++i)
  {
for (int j=0; j<i; j++)
  {
if (i!=j) //only runs positions once as j<=i and will not run if i==j i.e. the diagonal to save time and computer resources (no impact to outputted matrix as if i=j  &M[i,j]=&M[j,i])
  {
//below swaps given values within an array using swapr(a,b)

//cout<<array[i][j]<<" "; //used in testing to see original array value
swapr(&array[i][j],&array[j][i]); 
//cout<<array[i][j]<<endl; //used in testing to then see the new swapped value
  }
  }
  }
}

//defines a printing function for 3x3 arrays
void printm(double array[3][3])
{
//creates a new lines at begining and end to ensure the outputed matrix is well formatted and runs two integers from 0 to 2 using this to access all array positions for printing
cout<<endl;
for (int i=0; i<3; i++)
  {
for (int j=0; j<3; j++)
  {
//outputs each row and then creates a new line after this
cout<<array[i][j]<<"  ";
}
cout<< endl;
}
cout<< endl;
}
  
int main()
{
//defines array M, transposes it and prints the result
double M[3][3]={{ 0.36, 0.48, -0.8},{ -0.8, 0.6, 0.0},{ 0.48, 0.64, 0.6}};
//printm(M); //used in testing to ensure the matrix M is transposing through comparison to the original
transpose(M);
printm(M);
}
