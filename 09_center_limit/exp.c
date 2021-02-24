#include"rdm.h" //header file containing function rdm to generate random number
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<unistd.h>

#define M 100000 //random numbers
#define mu 1. //expectation
#define sigma 1. //standard deviation 
int main()
{	
    int N_array[5]={2,5,10,100,1000};
    for (int g=0;g<5;g++)
{   
    FILE* data=NULL;//prepare a file to write data 
    int N=N_array[g];
    char str[20];
    sprintf(str,"exp_(N=%d,M=1E4).txt",N);
    data=fopen(str,"w+");

    double *xi;//random number in [0,1]
    double *x;// final <x> that we want
    x=(double*) malloc(M*sizeof(double));
    xi=(double*) malloc(N*M*sizeof(double));//xi represents random number in [0,1]
    rdm(N*M,xi,1);//use 16807 to generate N*M random number in [0,1]; 1:use time seed
    sleep(1);//sleep to change time seed
    for (int i = 0; i < M; i++)
    {
        double temp=0;
        for (int j = 0; j < N; j++)
        {
            temp+=-log(xi[N*i+j])/N;//<x>=(x_1+x_2+...x_N)/N
        }
        x[i]=(temp-mu)/sigma*sqrt(N);//compute the value of Y=(<x>-mu)/sigma*sqrt(N)
        fprintf(data,"%f\n",x[i]);
    }
    fclose(data);
	free(xi);
    free(x);
}
	return 0;
}
