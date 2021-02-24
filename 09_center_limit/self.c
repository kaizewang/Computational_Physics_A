#include"rdm.h" //header file containing function rdm to generate random number
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<unistd.h>

#define M 1E4 //random numbers
#define pi 3.141592653589793
#define mu 0.021
#define sigma 0.60
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
    int N_array[5]={2,5,10,1000,10000};
    for (int g = 0; g < 5; g++)
    {   
        int N=N_array[g];
        double I;
        I=2*asin(1./sqrt(3));//integral of F(x) in [-1,1]
        double *xi1;
        double* xi2;
        double *xi_x;
        double* xi_y;
        double* x; //final result 
        xi1=(double*) malloc(M*N*sizeof(double));//xi represents random number in [0,1]
        xi2=(double*) malloc(M*N*sizeof(double));
        xi_x=(double*) malloc(M*N*sizeof(double));
        xi_y=(double*) malloc(M*N*sizeof(double));
       
        rdm(M*N,xi1,1);
        rdm(M*N,xi2,0);  //use 16807 to generate N random number in [0,1]; 1:use time seed
        sleep(1);//sleep to change time seed
        for (int i = 0; i < N*M; i++)
        {
            xi_x[i]=sqrt(3)*sin(I*(xi1[i]-1./2));
            xi_y[i]=F(xi_x[i])*xi2[i];
        }
        free(xi1);
        free(xi2);
	    //Write data into coordinate.txt
	    FILE* Data=NULL;
        char str[20];
        sprintf(str,"p_self_(x)(N=%d).txt",N);
        Data=fopen(str,"w+");
        int cnt=0;//counting the total x_i of this method 
        for(int k=0;k<M*N;k++)
        {   
            if (xi_y[k]<p(xi_x[k]))
            {   
                fprintf(Data,"%f\n",xi_x[k]);
                cnt++;
            }
	    }//generate x_i for next step 
        //printf("Total number is:%d\n",cnt); this is only for me to check wether the efficiency is correct
        rewind(Data);


        int K=cnt/N;//total number of <X> 
        x=(double*) malloc (K*N*sizeof(double));
        for (int k = 0; k < K*N; k++)
        {   
            fscanf(Data,"%lf",x+k);
        }

        FILE* result=NULL;
        char s[40];
        sprintf(s,"self_(N=%d,M=1E4).txt",N);
        result=fopen(s,"w+");
        for(int k=0;k<K;k++)
        {   
            double temp=0;
            for (int j=0; j < N; j++)
            {
                temp+=x[N*k+j]/N;
            }
            temp=(temp-mu)/sigma*sqrt(N);//compute the value of Y=(<x>-mu)/sigma*sqrt(N)
            fprintf(result,"%f\n",temp);
        }
	    fclose(Data);
        fclose(result);
        free(xi_x);
        free(xi_y);
        free(x);
    }
	return 0;
}
