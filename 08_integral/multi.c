#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include"rdm.h"

#define I 5.644079999999997

//compute integral of 6-x^2-y^2-z^2-u^2-v^2
double f(double x,double y,double z,double u,double v)
{   
    return 6.-x*x-y*y-z*z-u*u-v*v; 
}

int main()
{    
    //prepare a file to write data  
    FILE* integral=NULL;
    integral=fopen("multi_variable.txt","w+");
    fprintf(integral,"N\tIntegral\tErr\t1/sqrt(N)\n");
    int N=0;
    double sum=0;//sum over f(xi)
    double x[5]={9/10.0, 4/5.0, 9/10.0, 2.0, 13/10.0};//generate  random numbers in  [0,x[i]]
    for(int i=1;i<=7;i++){
    	sum=0;
    	N=(int) pow(10,i); //N=10,100,1000,..,10^7
        double* xi;
        xi=(double*)malloc(sizeof(double)*5*N);
        rdm(5*N,xi,1);
        for(int j=0;j<5*N;j+=5)
        {
		    sum+=f(x[j%5]*xi[j],x[(j+1)%5]*xi[j+1],x[(j+2)%5]*xi[j+2],x[(j+3)%5]*xi[j+3],
		    x[(j+4)%5]*xi[j+4])*x[0]*x[1]*x[2]*x[3]*x[4];
		}
        fprintf(integral,"%8d\t%.8e\t%.8e\t%.8e\n",N,sum/N,fabs(sum/N-I),1/sqrt(N));
	    free(xi);
	}  
	fclose(integral);
	return 0;
}