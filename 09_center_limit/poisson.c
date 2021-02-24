#include"rdm.h" //header file containing function rdm to generate random number
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<unistd.h>

#define M 10000 //random numbers
#define mu 1. //expectation
#define sigma 1. //standard deviation 

int factorial(int n)
{   
    int t=1;
    if(n>0)
    {
         for (int i = 1; i <=n; i++)
        {
            t*=i;
        }
    }
    return t;
}

double p(int k)
{
    return 1./factorial(k)*exp(-1);
}

double P(int k)
{
    double temp=0;
    for (int i = 0; i <=k; i++)
    {
        temp+=p(i);
    }
    return temp;
}

int invP(double xi)// return the sampling number k related to xi in [0,1], i.e. inverse of P
{
    if(0<=xi&&xi<P(0)) return 0;
    else if(P(0)<=xi&&xi<P(1)) return 1;
    else if(P(1)<=xi&&xi<P(2)) return 2;
    else if(P(2)<=xi&&xi<P(3)) return 3;
    else if(P(3)<=xi&&xi<P(4)) return 4;
    else if(P(4)<=xi&&xi<P(5)) return 5;
    else if(P(5)<=xi&&xi<P(6)) return 6;
    else if(P(6)<=xi&&xi<P(7)) return 7;
    else if(P(7)<=xi&&xi<P(8)) return 8;
    else if(P(8)<=xi&&xi<P(9)) return 9;
    else if(P(9)<=xi&&xi<P(10)) return 10;
    else return 11;//truncate at k=11
}

int main()
{	
    int N_array[5]={2,5,10,1000,1E4};
    for (int g=0;g<5;g++)
{   
    FILE* data=NULL;//prepare a file to write data 
    int N=N_array[g];
    char str[20];
    sprintf(str,"poisson_(N=%d,M=1E4).txt",N);
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
            temp+=(double)invP(xi[N*i+j])/N;
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