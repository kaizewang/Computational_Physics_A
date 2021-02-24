#include"rdm.h" //header file containing function rdm to generate random number
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<unistd.h>

#define pi 3.1415926
#define D1  1.00  //standard variance of x'
#define D2  0.01   //standard variance of y'
#define Dt  0.008  //standard variance of theta
//#define Dt  0.08
//#define Dt  0.10
#define N   100000 //number of systems to simulate the ensemble
#define M   1000 //total time step 

void normal(int n,double *x,double mu,double sigma)  //return standard normal distribution (method=0:default;method=1:timeseed)
//using box-miller method to generate normal distribution 
{   
    double *u;
    double* v;
    u=(double*)malloc(sizeof(double)*n);
    v=(double*)malloc(sizeof(double)*n);
    rdm(n,u,1);                         //use time seed
    sleep(1);
    rdm(n,v,1);                          
    for (int i = 0; i < n; i++)
    {   
        x[i]=sqrt(-2.0*log(u[i]))*cos(2.0*pi*v[i]);
        x[i]=sigma*(x[i]+mu);
    }
}



int main()
{   
    double x=0;
    double y=0;
    double theta=0;
    double *randomx;//prepare random normal distribution array for further use 
    double *randomy;
    double *randomt;
    double *p;// normalized cumulant
    double *x_4;//<x^4>
    double* x_2;//<x^2> 
    randomx=(double*) malloc(N*M*sizeof(double));
    randomy=(double*) malloc(N*M*sizeof(double));
    randomt=(double*) malloc(N*M*sizeof(double));
    x_2=(double*) malloc(M*sizeof(double));
    x_4=(double*) malloc(M*sizeof(double));
    p=(double*) malloc(M*sizeof(double));
    normal(N*M,randomx,0,D1);
    sleep(1);
    normal(N*M,randomy,0,D2);
    sleep(1);
    normal(N*M,randomt,0,Dt);
    FILE* cumulant;
    char str2[60];
    sprintf(str2,"cumulant(Dt=%f).txt",Dt);
    cumulant=fopen(str2,"w+");
    for(int i=0;i<N;i++)//loop for ensemble average 
    {   
        x=0;
        y=0;
        theta=0;
        for (int j = 0; j < M; j++)//loop for every step 1~M
        {   
            theta+=randomt[M*i+j];
            double temp=theta;
            x+=randomx[M*i+j]*cos(temp)-randomy[M*i+j]*sin(temp);
            y+=randomx[M*i+j]*sin(temp)+randomy[M*i+j]*cos(temp);
            x_4[j]+=pow(x,4.0)/N;
            x_2[j]+=pow(x,2.0)/N ;
        }
    }
    for (int i = 0; i < M; i++)
    {   
        p[i]=(x_4[i]-3*x_2[i]*x_2[i])/(3*x_2[i]*x_2[i]);//write data into txt
        fprintf(cumulant,"%f\n",p[i]);
    }

    free(randomt);
    free(randomx);
    free(randomy);
    free(x_2);
    free(x_4);
    free(p);
    fclose(cumulant);

}