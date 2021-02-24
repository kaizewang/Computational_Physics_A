#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define pi 3.14159265358979

//This is a file to compute Feigenbaum constant 

int main()
{   
    long double lambda=0;
    long double x=0;
    //input the range and step size of lambda
    long double inf=0.71;
    long double sup=0.87;
    long double step=(sup-inf)/1000000;
    int N=2E3;//total iteration steps for each lambda 
    int M=1E3;//relaxation part size 
    
    

    FILE* d;
    char str[30];
    sprintf(str,"Feigenbaum.txt");
    d=fopen(str,"w+");

    long double epsilon=1E-3;// juging wether two x are equal 
    int re=1;//check wether lambda is the critical one to write into file 
    for(lambda=inf;lambda<=sup;lambda+=step)//loop for lambda 
    {   
        x=0.1;
        double temp[128];
        for (int i = 0; i < N; i++)
        {
            x=lambda*sin(pi*x);
            if(i>=M&&i<M+128)
            {   
                temp[i-M]=x;
            }
        }
        int cnt=1;
        for (int k = 1; k < 128; k++)//This is a loop for counting period 2,4,8,16,32,64,128... with every lambda
        {   
            //the following if else are used to control the error limitation for juding whether two x are equal
            if(cnt<=2)
            {
            if(fabs(temp[k]-temp[0])>epsilon*10) cnt+=1;
            else break;
            }
            else if(cnt>2&&cnt<=4)
            {
            if(fabs(temp[k]-temp[0])>epsilon) {cnt+=1;fprintf("%f\t")}
            else break;
            }
            else if(cnt>4&&cnt<=8)
            {
            if(fabs(temp[k]-temp[0])>epsilon/2) cnt+=1;
            else break;
            }
            else if(cnt>8&&cnt<=16)
            {
            if(fabs(temp[k]-temp[0])>epsilon/4) cnt+=1;
             else break;
            }
            else if(cnt>16&&cnt<=32)
            {
            if(fabs(temp[k]-temp[0])>epsilon/8) cnt+=1;
             else break;
            }
            else if(cnt>32&&cnt<=64)
            {
            if(fabs(temp[k]-temp[0])>epsilon/16) cnt+=1;
             else break;
            }
             else if(cnt>64&&cnt<=128)
            {
            if(fabs(temp[k]-temp[0])>epsilon/200) cnt+=1;
             else break;
            }
        }
        if(cnt>re&&(cnt==2||cnt==4||cnt==8||cnt==16||cnt==32||cnt==64||cnt==128))
        {
            fprintf(d,"%d\t%.10f\n",cnt,(double) lambda);  
            if(re<=64)
            re*=2;
            else break;
        }
    }




    return 0;
}