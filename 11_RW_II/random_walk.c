#include"rdm.h" //header file containing function rdm to generate random number
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<unistd.h>

#define N 1000 //total steps
#define M 200000 //total number of systems in the ensemble 

int main()
{      
    //some preparations
    double *a;
    double *b;
    double *c;
    a=(double*)malloc(sizeof(double)*N*M);//random numbers for >=1d random walk in an array
    b=(double*)malloc(sizeof(double)*M*N);//random numbers for >=2d ramdom walk in an array
    c=(double*)malloc(sizeof(double)*N*M);//random numbers for 3d random walk in an array 
    rdm(N*M,a,1);
    sleep(1);
    rdm(N*M,b,1);
    sleep(1);
    rdm(N*M,c,1);
    sleep(1);
    double x=0,y=0,z=0;//coordinates
    double* P1;
    P1=(double*)malloc(sizeof(double)*N);//probability distribution for 1d
    double* P2;
    P2=(double*)malloc(sizeof(double)*N);//probability distribution for 2d
    double* P3;
    P3=(double*)malloc(sizeof(double)*N);//probability distribution for 3d
    double nu1=0;//scaling coefficient for 1d
    double nu2=0;//scaling coefficient for 2d
    double nu3=0;//scaling coefficient for 3d
    /*
    //Task1: 1D random walk
    for (int i = 0; i < M; i++)//loop for ensembles 
    {   
        int cnt=0;//coordinate counter 
        for(int j=0;j<N;j++)//loop for steps
        {
            if(a[i*N+j]<0.5) cnt+=1;//moving decision
            else cnt+=-1;
            if (cnt==0) P1[j]+=1.0/M;
        }
    }
    //write data into txt
    FILE* rw1;
    rw1=fopen("1d_random_walk_P1.txt","w+");
    for (int i = 0; i < N; i++)
    {
        fprintf(rw1,"%d\t%f\n",i+1,P1[i]);
    }
    fclose(rw1);
    free(P1);
    */
    //Task2:2D random walk
    FILE* coordinate2;//prepare a file to write (x,y,z) of a particle as an example of 3d random walk
    coordinate2=fopen("coordinate2.txt","w+");
    fprintf(coordinate2,"0\t 0\n");
     for (int i = 0; i < M; i++)//loop for ensembles 
    {   
        int x_cnt=0;//coordinate counter 
        int y_cnt=0;
        for(int j=0;j<N;j++)//loop for steps
        {
            if(b[i*N+j]<1./4) x_cnt+=-1;
            else if(b[i*N+j]<2./4) x_cnt+=1;
            else if(b[i*N+j]<3./4) y_cnt+=-1;
            else y_cnt+=1;
            if(i==0)
            fprintf(coordinate2,"%d\t%d\n",x_cnt,y_cnt);
            if (x_cnt==0&&y_cnt==0) P2[j]+=1.0/M;
        }
    }
    //write data into txt
    FILE* rw2;
    rw2=fopen("2d_random_walk_P2.txt","w+");
    for (int i = 0; i < N; i++)
    {
        fprintf(rw2,"%d\t%f\n",i+1,P2[i]);
    }
    fclose(rw2);
    fclose(coordinate2);
    free(P2);
    /*
    //Task3:3D random walk
    FILE* coordinate3;//prepare a file to write (x,y,z) of a particle as an example of 3d random walk
    coordinate3=fopen("coordinate3.txt","w+");
    fprintf(coordinate3,"0\t 0\t 0\n");

     for (int i = 0; i < M; i++)//loop for ensembles 
    {   
        int x_cnt=0;//coordinate counter 
        int y_cnt=0;
        int z_cnt=0;
        for(int j=0;j<N;j++)//loop for steps
        {   
            if(c[i*N+j]<1./6) x_cnt+=-1;
            else if(c[i*N+j]<2./6) x_cnt+=1;
            else if(c[i*N+j]<3./6) y_cnt+=-1;
            else if(c[i*N+j]<4./6) y_cnt+=1;
            else if(c[i*N+j]<5./6) z_cnt+=-1;
            else z_cnt+=1;
            if(i==0)
            fprintf(coordinate3,"%d\t%d\t%d\n",x_cnt,y_cnt,z_cnt);
            if (x_cnt==0&&y_cnt==0&&z_cnt==0) P3[j]+=1.0/M;
        }
    }
    //write data into txt
    FILE* rw3;
    rw3=fopen("3d_random_walk_P3.txt","w+");
    for (int i = 0; i < N; i++)
    {
        fprintf(rw3,"%d\t%f\n",i+1,P3[i]);
    }
    fclose(rw3);
    fclose(coordinate3);
    free(P3);
    */

}