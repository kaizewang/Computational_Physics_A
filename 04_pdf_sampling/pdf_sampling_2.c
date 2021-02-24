#include"rdm.h" //header file containing function rdm to generate random number
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define N 10000 //random numbers
#define pi 3.141592653589793
double F(double x)
{
    double temp=0;
    temp=1/sqrt(3-x*x);
    return temp;
}

double p(double x)
{
    double temp=0;
    temp=1.81915*exp(-x)/(2-x)/(2-x);
    return temp;
}

int main()
{	
    double I;
    I=2*asin(1./sqrt(3));//integral of F(x) in [-1,1]
    double *xi1;
    double* xi2;
    double *xi_x;
    double* xi_y;
    xi1=(double*) malloc(N*sizeof(double));//xi represents random number in [0,1]
    xi2=(double*) malloc(N*sizeof(double));
    xi_x=(double*) malloc(N*sizeof(double));
    xi_y=(double*) malloc(N*sizeof(double));
    rdm(N,xi1,1);
    rdm(N,xi2,0);  //use 16807 to generate N random number in [0,1]; 1:use time seed
    for (int i = 0; i < N; i++)
    {
        xi_x[i]=sqrt(3)*sin(I*(xi1[i]-1./2));
        xi_y[i]=F(xi_x[i])*xi2[i];
    }
	 //Write data into coordinate.txt
	FILE* Data=NULL;
    char str[20];
    sprintf(str,"p_2(x)_N=%d.txt",N);
    Data=fopen(str,"w+");
    int cnt=0;//counting the efficiency of this method
    for(int i=0;i<N;i++)
    {   
        if (xi_y[i]<p(xi_x[i]))
        {
             fprintf(Data,"%f\n",xi_x[i]);
             cnt++;
        }
	}
    printf("The efficiency is:%f",(double)cnt/N);
	fclose(Data);
	free(xi1); 
    free(xi2);
    free(xi_x);
    free(xi_y);
	return 0;
}
