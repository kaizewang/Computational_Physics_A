#include"rdm.h" //header file containing function rdm to generate random number
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define N 10000 //random numbers
#define pi 3.141592653589793

int main()
{	
    double *xi1,*xi2,*phi,*c;
    xi1=(double*) malloc(N*sizeof(double));//xi represents random number in [0,1]
    xi2=(double*) malloc(N*sizeof(double));
    phi=(double*) malloc(N*sizeof(double));
    c=(double*) malloc(N*sizeof(double));  // c represents cos(theta)
    rdm(N,xi1,1);
    rdm(N,xi2,0);    //use 16807 to generate N random number in [0,1]; 1:use time seed

	 //Write data into coordinate.txt
	FILE* Data=NULL;
    Data=fopen("coordinate.txt","w+");
    for(int i=0;i<N;i++)
    {
        phi[i]=xi1[i]*2*pi;
	    c[i]=1-2*xi2[i];
        fprintf(Data,"%f,%f,%f\n",sqrt(1-c[i]*c[i])*cos(phi[i]),sqrt(1-c[i]*c[i])*sin(phi[i]),c[i]);
	}
	fclose(Data);
	free(xi1); 
    free(xi2);
    free(phi);
    free(c);
	return 0;

}
