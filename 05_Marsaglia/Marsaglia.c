#include"rdm.h"
#include<stdio.h>
#include<math.h>
#define N 10000 //number of samples

//Marsaglia.cpp generates random numbers uniformly on sphere surface

 int main()
 {    
	 
     double *u;
	 u=(double*) malloc(N*sizeof(double));
     double *v;
	 v=(double*) malloc(N*sizeof(double));
     double *r;
	 r=(double*) malloc(N*sizeof(double));
     rdm(N,u,0);
	 rdm(N,v,1);
     for (int i=0;i<N;i++)
     {   u[i]=u[i]*2-1,v[i]=v[i]*2-1;
	     r[i]=sqrt(u[i]*u[i]+v[i]*v[i]);
	 }
     
	//Task: Sphere Surface
	
	FILE* sphere3=NULL;
	sphere3=fopen("sphere_surface.txt","w+");
	for(int i=0;i<N;i++)
	{
		if(r[i]<=1)
		{
			fprintf(sphere3,"%f,%f,%f\n",2*u[i]*sqrt(1-r[i]*r[i]),2*v[i]*sqrt(1-r[i]*r[i]),1-2*r[i]*r[i]);
		}
	
	}
	fclose(sphere3);
	free(u);
	free(v);
	free(r);
	return 0;
  
 }
