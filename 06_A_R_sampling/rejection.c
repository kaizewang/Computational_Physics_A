#include"rdm.h"// header file containing 16807 generator function 
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define N 1000000 //initial random numbers
#define pi 3.141592653589793



double p(double x)  
{
    double temp;
    temp=1./sqrt(pi)*exp(-x*x);
    return temp;
}

double F(double x)
{
    double temp;
    temp=1./(1+x*x*x*x)*1./sqrt(pi);
    return temp;
}

double H(double x)
{
    double temp;
    temp=1./4/pi*(2*atan(1+sqrt(2)*x)-2*atan(1-sqrt(2)*x)+log((x*x+sqrt(2)*x+1)/(x*x-sqrt(2)*x+1)))+0.5;
    return temp;
}

double root(double xi)
{   
    double I1=-10.;
    double I2=10.;
    double erf=1E-4;
    double r=0;
    if(xi<0.00015) return -10;
    else if (xi>0.99985) return 10;
    else 
    {   
        while (fabs(H((I1+I2)/2)-xi)>=erf)
        {
            if(H((I1+I2)/2)-xi>0)
            {
                I2=(I1+I2)/2;
            }
            else
            {
                I1=(I1+I2)/2;
            } 
        }
        r=(I1+I2)/2;
        return r;
    }  
}

int main()
{   
    int cnt=0;//computing efficiency
    //initialize xi1,xi2,xi_x,xi_y array
	double *xi1;
    xi1=(double*)malloc(N*sizeof(double));
	double *xi2;
    xi2=(double*)malloc(N*sizeof(double));
    double *xi_x;
    xi_x=(double*)malloc(N*sizeof(double));
    double *xi_y;
    xi_y=(double*)malloc(N*sizeof(double));
    
    //use diffenrent initial value to generate independent xi1,xi2 
    rdm(N,xi1,0);
    rdm(N,xi2,1);
    //generate xi_x,xi_y
    for (int i=0;i<N;i++)
    {
	  xi_x[i]=root(xi1[i]);
      xi_y[i]=xi2[i]*F(xi_x[i]);
	}
	
	//Write data into x_p.txt
	FILE* Data=NULL;
    char str[40];
    sprintf(str,"N=%d.txt",N);
    Data=fopen(str,"w+");
	
	for (int i=0;i<N;i++)
	{
	    if(xi_y[i]<p(xi_x[i]))
	    {   
	        cnt+=1;
            fprintf(Data,"%f\n",xi_x[i]);
	    }
	}
	
	fclose(Data);

	//output some results
    printf("Total random numbers: %d\n",N);
    printf("Effective random numbers: %d\n",cnt);
    printf("The efficiency of this method is: %f\n",(double)cnt/N);

	free(xi1),free(xi2),free(xi_x),free(xi_y);
	return 0;
}