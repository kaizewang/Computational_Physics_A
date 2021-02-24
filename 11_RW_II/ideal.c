#include<stdio.h>
#include<stdlib.h>
#include<math.h>

//This is a file to generate ideal probability distribution for N=2,4,6,...,50

#define M 100  


double factorial (int n)
{   
    double t=1;
    if(n>=1)
    for (int i=1;i<=n;i++) t*=(double)i;
    return t;
}

int main()
{
    //1d output ideal result 
    FILE* one_d;
    one_d=fopen("1d_ideal.txt","w+");
    for (int i = 0; i <=M;i=i+2)
    {
        fprintf(one_d,"%d\t%f\n",i,factorial(i)/factorial(i/2)/factorial(i/2)*pow(0.5,i));
    }
    fclose(one_d);

    //2d output ideal result 
    FILE* two_d;
    two_d=fopen("2d_ideal.txt","w+");
    for (int i = 0; i <=M;i=i+2)
    {   
        double temp=0;
        for (int j = 0; j <=i/2; j++)
        {
            temp+=factorial(i)/factorial(j)/factorial(i/2-j)/factorial(j)/factorial(i/2-j)*pow(0.25,i);
        }
        fprintf(two_d,"%d\t%f\n",i,temp);
    }
    fclose(two_d);

    //3d output ideal result 
    FILE* three_d;
    three_d=fopen("3d_ideal.txt","w+");
    for (int i = 0; i <=M;i=i+2)
    {   
        double temp=0;
        for (int j = 0; j <=i/2; j++)
        {   
            for(int k=0;k<=i/2-j;k++)
            temp+=factorial(i)/pow(factorial(j),2)/pow(factorial(k),2)/pow(factorial(i/2-j-k),2)*pow(1./6,i);
        }
        fprintf(three_d,"%d\t%f\n",i,temp);
    }
    fclose(three_d);



}