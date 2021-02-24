#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"rdm.h"

//This is the file to get different err from different gamma 
double min(double x1, double x2)
{
    if(x1<x2) return x1;
    else return x2;
}

int main()
{   
    double alpha=2.0,beta=1.0;
    for (double gamma =10.0; gamma <=10000.0; gamma*=3)//adjust the range of gamma manually to get the err we want 
    {
            int N;
            N=1E6;
        double * R;//R1 is a random array within [0,1]
        double * x; //x is an array for recording every step
        double * x1; // x1 stands for x'
        int m;
        m=N/10;//m is the lower cut-off
        double r=0;
        double I=0;// I is the final integration we need 
        R=(double*) malloc(sizeof(double)*N);
        x=(double*) malloc(sizeof(double)*N);
        x1=(double*) malloc(sizeof(double)*N);
        rdm(N,x1,0);
        rdm(N,R,1);
        for (int i = 0; i < N; i++)
        {
            x1[i]=-gamma*log(R[i]);
        }
        x[0]=1;
        for (int i = 0; i < N-1; i++)
        {      
            r=pow(x1[i]/x[i],alpha-1)*exp(-(x1[i]-x[i])/beta)*exp((x1[i]-x[i])/gamma);
            if(R[i]<min(1.0,r)) x[i+1]=x1[i];
            else x[i+1]=x[i];
        }
        for(int k=m;k<N;k++)
        {
            I+=pow((x[k]-alpha*beta),2)/(N-m);
        }


        FILE* error2 ;
        char str2[20];
        sprintf(str2,"error_2,N=%d.txt",N);
        error2=fopen(str2,"a");
        fprintf(error2,"%2f\t%f\n",gamma,fabs(I-alpha*beta*beta));
    }
}
