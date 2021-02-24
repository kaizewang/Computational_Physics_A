#include"rdm.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <unistd.h>
#define N 100000 //number of samples

//Marsaglia.cpp generates random numbers uniformly on sphere surface

 int main()
 {    
	 
     double *u;
	 u=(double*) malloc(N*sizeof(double));
     double *v;
	 v=(double*) malloc(N*sizeof(double));
     double *w;
	 w=(double*) malloc(N*sizeof(double));
     double *x;
	 x=(double*) malloc(N*sizeof(double));
     double *r1;
	 r1=(double*) malloc(N*sizeof(double));
     double *r2;
	 r2=(double*) malloc(N*sizeof(double));
     rdm(N,u,1);
     sleep(2);
	 rdm(N,v,1);
     sleep(2);
     rdm(N,w,1);
     sleep(2);
     rdm(N,x,1);
     sleep(2);

     for (int i=0;i<N;i++)
     {  
        u[i]=u[i]*2-1,v[i]=v[i]*2-1,w[i]=w[i]*2-1,x[i]=x[i]*2-1;
	    r1[i]=sqrt(u[i]*u[i]+v[i]*v[i]);
        r2[i]=sqrt(w[i]*w[i]+x[i]*x[i]);
	 }
     
	//Task1: generate random numbers uniformly on a ring
     
     //write data into ring.txt
     FILE* ring=NULL;
     ring=fopen("ring.txt","w+");
     for (int i=0;i<N;i++)
     {   
	     if(r1[i]<=1)
	     {  
             fprintf(ring,"%f,%f\n",u[i]/r1[i],v[i]/r1[i]);
		 }
	 
	 }
    fclose(ring);
	
    //Task2: generate random numbers uniformly on a 4d sphere

    //write data into 4_sphere.txt
    FILE* four=NULL;
     four=fopen("4-sphere.txt","w+");
     int cnt=0;//counting efficiency
     for (int i=0;i<N;i++)
     {   
	     if(r1[i]<=1&&r2[i]<=1)
	     {  
             fprintf(four,"%f,%f,%f,%f\n",u[i],v[i],w[i]/r2[i]*sqrt(1-r1[i]*r1[i]),x[i]/r2[i]*sqrt(1-r1[i]*r1[i]));
             cnt++;
         }
	 
	 }
     printf("Efficiency of 4-dimension:%f",(double)cnt/N);
    fclose(four);

    free(u);
	free(v);
    free(w);
    free(x);
	free(r1);
    free(r2);
	return 0;
  
 }
