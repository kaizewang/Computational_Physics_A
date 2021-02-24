#include"rdm.h" //header file containing function rdm to generate random number
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<unistd.h>

#define pi 3.1415926
#define D1  1.00  //standard variance of x'
#define D2  0.01   //standard variance of y'
#define Dt  0.1  //standard variance of theta
//#define Dt  0.08
//#define Dt  0.10
#define N   1000 //number of systems to simulate the ensemble
#define M   10000 //total time step 

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
    double x=0;//location of center of mass 
    double y=0;
    double theta=0;
    double *randomx;//prepare random normal distribution array for further use 
    double *randomy;
    double *randomt;
    randomx=(double*) malloc(N*M*sizeof(double));
    randomy=(double*) malloc(N*M*sizeof(double));
    randomt=(double*) malloc(N*M*sizeof(double));
    normal(N*M,randomx,0,D1);
    sleep(1);
    normal(N*M,randomy,0,D2);
    sleep(1);
    normal(N*M,randomt,0,Dt);
    FILE* single;//prepare a file to write the motion of an ellipsoid in M steps
    char str1[60];
    sprintf(str1,"one_ellipsoid(step=%d,systems=%d,D1=%.2f,D2=%.2f,Dt=%.2f).txt",M,N,D1,D2,Dt);
    single=fopen(str1,"w+");
    fprintf(single,"%f\t%f\t%f\n",x,y,theta);
    FILE* ensemble;//prepare a file to write the motion of ensemble average 
    char str2[60];
    sprintf(str2,"ensemble(step=%d,systems=%d,D1=%.2f,D2=%.2f,Dt=%.2f).txt",M,N,D1,D2,Dt);
    ensemble=fopen(str2,"w+");
    double* Dx;//Dx=<x^2(t)>/t
    Dx=(double*) malloc(M*sizeof(double));
    double* Dy;//Dy=<y^2(t)>/t
    Dy=(double*) malloc(M*sizeof(double));
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
            if(i==0)
            fprintf(single,"%f\t%f\t%f\n",x,y,theta);
            Dx[j]+=x*x/N/(j+1);//add up the value of Dx/Dy for every time step j
            Dy[j]+=y*y/N/(j+1);
        }
    }
    for (int i = 0; i < M; i++)
    {
        fprintf(ensemble,"%f\t%f\n",Dx[i],Dy[i]);//write data into txt
    }

    free(randomt);
    free(randomx);
    free(randomy);
    fclose(ensemble);
    fclose(single);

}