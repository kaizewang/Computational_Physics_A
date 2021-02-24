#include"rdm.h" //header file containing function rdm to generate random number
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<unistd.h>

//This rw1.c file is used to generate correlation function c(t)=<u(t)u(0)> with different initial angle theta0
#define pi 3.1415926
#define Dt  0.05  //standard variance of theta
#define N   10000 //number of systems to simulate the ensemble
#define M   10000 //total time step 

int generate(double x)// randomly decide moving direction +1:positive direction -1:negative direction
{
    if(x>=0.5) return 1;
    else return -1;
}

void normal(int n,double *x,double mu,double sigma)  //return standard normal distribution (method=0:default;method=1:timeseed)
//using box-miller method to generate normal distribution 
{   
    double *u;
    double* v;
    u=(double*)malloc(sizeof(double)*n);
    v=(double*)malloc(sizeof(double)*n);
    rdm(n,u,1);                         //u uses time seed
    rdm(n,v,0);                         //v uses  defult value 
    for (int i = 0; i < n; i++)
    {
        x[i]=sqrt(-2.0*log(u[i]))*cos(2.0*pi*v[i]);
        x[i]=sigma*(x[i]+mu);
    }
}



int main()
{   
    double theta=0;
    double t[N];
    double *randomt;
    randomt=(double*) malloc(N*M*sizeof(double));
    normal(N*M,randomt,0,Dt);
    rdm(N,t,0);// generate ensemble of initial theta0
    FILE* correlation;
    char str2[60];
    sprintf(str2,"theta(t)&c(t).txt");
    correlation=fopen(str2,"w+");
    double C[M];//correlation C(t)
    double T[M];//<theta(t)>
    for(int i=0;i<N;i++)//loop for ensemble average 
    {   
        double theta0=0;
        theta0=theta;
        for (int j = 0; j < M; j++)//loop for every step 1~M
        {   
            theta+=randomt[N*i+j];
            T[j]+=theta/N;
            C[j]+=cos(theta)*cos(theta0)/N;//computing ensemble average 
        }
    }
    for (int i = 0; i < M; i++)
    {
        fprintf(correlation,"%f\t%f\n",T[i],C[i]);//write data into txt
    }

    fclose(correlation);
    free(randomt);

}