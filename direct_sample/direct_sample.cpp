#include"rdm.h"
#include<fstream>
#include<math.h>

#define N 10000 //random numbers 
#define pi 3.141592653589793

int main()
{
    double *xi1=new double[N];
    double *xi2=new double[N];
    double *phi=new double[N];
    double *c=new double[N];     // c represents cos(theta)
    rdm(N,xi1,1),rdm(N,xi2,1);    //1:use time seed
    
	 //Wirte data into coordinate.txt
	std::ofstream Data("coordinate.txt");
 	
    for(int i=1;i<N;i++)
    {
	    phi[i]=xi1[i]*2*pi;
	    c[i]=1-2*xi2[i];
	    Data<<sqrt(1-c[i]*c[i])*cos(phi[i])<<',';
	    Data<<sqrt(1-c[i]*c[i])*sin(phi[i])<<',';
	    Data<<c[i]<<'\n';
	}
	
	Data.close();
	delete xi1,xi2,phi,c;
	return 0;

}
