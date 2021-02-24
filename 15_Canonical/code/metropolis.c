#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"rdm.h"

double min(double x1, double x2)
{
    if(x1<x2) return x1;
    else return x2;
}

int main()
{   
    double a[1]={1};//array for step size A
    for (int j = 0;j<1; j++) //loop for different step size A
    {   
        //initial condition 
        double x0=8.0,y0=6.0;
        double x1=0.0,y1=0.0;
        //average 
        double x_s=0,y_s=0,x_p_y=0;//x_square、y_square、x_square+y_square 
        int N=1E6,M=1E4;
        double * dx,* dy,* r,* temp;
        dx=(double*)malloc(sizeof(double)*N);
        dy=(double*)malloc(sizeof(double)*N);
        temp=(double*)malloc(sizeof(double)*2*N);
        r=(double*)malloc(sizeof(double)*N);
        rdm(2*N,temp,1);
        rdm(N,r,0);
        double A;
        A=a[j];
        for (int i = 0; i <2*N; i++)
    {
        if(i<=N-1)
        dx[i]=temp[i]*2*A-A;
        else
        dy[i-N]=temp[i]*2*A-A;
    }
    free(temp);
    //prepare two files to write data
    FILE* steps;
    if((A==0.001)||(A==0.04)||(A==1))
    {
    char str[20];
    sprintf(str,"steps(A=%.4f).txt",A);
    steps=fopen(str,"w+");
    fprintf(steps,"%f\t%f\n",x0,y0);
    }
    FILE* avg;
    avg=fopen("avg.txt","a+");
    FILE* err; // this is an file for writing error of diffentent step sizes
    err=fopen("err.txt","a+");
    for (int i = 0; i < N; i++)
    {   
        x1=x0+dx[i];
        y1=y0+dy[i];
        if(exp(-(x1*x1+y1*y1)/2+(x0*x0+y0*y0)/2)>1.0)
        x0=x1,y0=y1;
        else
        {
            if(r[i]<exp(-(x1*x1+y1*y1)/2+(x0*x0+y0*y0)/2))
            {
                x0=x1,y0=y1;
            }
            else
            continue;
        }
        if(i>=M)
        {
            x_s+=x0*x0/(N-M);
            y_s+=y0*y0/(N-M);
            x_p_y+=x0*x0/(N-M)+y0*y0/(N-M);
        }
        if((A==0.001)||(A==0.04)||(A==1))
        fprintf(steps,"%f\t%f\n",x0,y0);
    }
    fprintf(avg,"<x^2>:\t%f\n<y^2>:\t%f\n<x^2+y^2>:\t%f\n\n",x_s,y_s,x_p_y);
    fprintf(err,"%f\t%.6f\n",a[j],fabs(2-x_p_y));
    printf("step size=%f\n<x^2>:\t%f\n<y^2>:\t%f\n<x^2+y^2>:\t%f\n\n",a[j],x_s,y_s,x_p_y);
    free(r);
    free(dx);
    free(dy);
    }
    return 0;
}
    
    