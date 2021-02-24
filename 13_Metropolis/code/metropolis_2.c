#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"rdm.h"

//This is the file to get err with different step N
double min(double x1, double x2)
{
    if(x1<x2) return x1;
    else return x2;
}

int main()
{   
    double alpha=2.0,beta=1.0;
    //this array is for generating result of different steps N
    int t[7]={1E1,1E2,1E3,1E4,1E5,1E6,1E7}; 
    double G[3]={.2,1.4,4};
    for (int p=0;p <=2; p++)
    {   
        double gamma;
        gamma=G[p];
            for ( int j=0; j< 7; j++)
        {
            int N;
            N=t[j];
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
        //computing error
        printf("gamma=%.2f,N=%d\n",gamma,N);
        printf("Integration:%f\n",I);
        printf("error is: %f\n",fabs(I-alpha*beta*beta));
        
        FILE* error1;//collecting different N for same gamma 
        char str[20];
        sprintf(str,"gamma=%.2f.txt",gamma);
        error1=fopen(str,"a");
        fprintf(error1,"%8d\t\t%f\n",N,fabs(I-alpha*beta*beta));

        
    }
    }
}