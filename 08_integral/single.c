#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include"rdm.h"
#define I 2.689521304816752 //exact solution 

//compute integral of sqrt(x+sqrt(x))
double f(double x)
{
    return sqrt(x+sqrt(x)); 
}

int main()
{   
    FILE* integral=NULL;
    integral=fopen("single_variable.txt","w+");
    fprintf(integral,"N\tIntegral\tErr\t1/sqrt(N)\n");
  
    int N=0;
    double sum=0;
    for(int i=1;i<=8;i++){
    	sum=0;
    	N=(int) pow(10,i);
        double *xi;
        xi=(double*) malloc (sizeof(double)*N);
        rdm(N,xi,1);
        for(int j=0;j<N;j++)
        {   
            xi[j]=2*xi[j];
		    sum+=f(xi[j]);
		}
    fprintf(integral,"%10d\t%.8e\t%.8e\t%.8e\n",N,2*sum/N,fabs(2*sum/N-I),1/sqrt(N));
        free(xi);
        sleep(1);
	}  
	fclose(integral);
	return 0;
}
