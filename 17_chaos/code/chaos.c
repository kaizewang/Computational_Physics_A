#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define pi 3.14159265358979

//This is a file to generate chaos figures 

int main()
{   
    double lambda=0;
    double x=0;
    //input the range and step size of lambda
    double inf=0.715;
    double sup=0.725;
    double step=(sup-inf)/1000;
    int N=1E3;//total iteration steps for each lambda 
    int M=1E2;//relaxation part size 
    
    

    FILE* d;
    char str[30];
    sprintf(str,"lambda(%.2f-%.2f).txt",inf,sup);
    d=fopen(str,"w+");

    for(lambda=inf;lambda<=sup;lambda+=step)//loop for lambda 
    {   
        x=0.1;
        for (int i = 0; i < N; i++)
        {
            x=lambda*sin(pi*x);
            if(i>M)
            {
            fprintf(d,"%f\t%f\n",lambda,x);
            }
        }  
    }




    return 0;
}