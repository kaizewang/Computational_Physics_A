#include"rdm.h" //header file containing function rdm to generate random number
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define N 10000 //random numbers
#define pi 3.141592653589793

int main()
{	
    double *xi1;
    double *xi_x;
    xi1=(double*) malloc(N*sizeof(double));//xi represents random number in [0,1]
    xi_x=(double*) malloc(N*sizeof(double));
    rdm(N,xi1,1);  //use 16807 to generate N random number in [0,1]; 1:use time seed
    for (int i = 0; i < N; i++)
    {
        xi_x[i]=sin(2*pi*xi1[i]);
    }
	 //Write data into coordinate.txt
	FILE* Data=NULL;
    Data=fopen("p_1(x).txt","w+");
    for(int i=0;i<N;i++)
    {
        fprintf(Data,"%f\n",xi_x[i]);
	}
	fclose(Data);
	free(xi1); 
    free(xi_x);
	return 0;
}
