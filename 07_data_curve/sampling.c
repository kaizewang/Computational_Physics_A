#include"rdm.h" //header file containing function rdm to generate random number
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<math.h>

#define N 10000 //initial random numbers
#define L (3013-2900+1) //number of data points 

double F(double x) //F(x) is the step function for comparison 
{
    double temp=0;
    if(2900<=x&&x<2994)
    temp=0.0143;
    else if(2994<=x&&x<3005)
    temp=0.0950;
    else temp=0.0033;
    return temp;
}

int main()
{	
   //Task1: direct sampling 
   //initialize array
    double *xi;//[0,1] random number
    int C[L]; //data: normalized counting 
    int E[L];//date: energy 
    double p[L];//normalized density
    double P[L];//cumulative distribution function  
    xi=(double*) malloc(N*sizeof(double));//xi represents random number in [0,1]
    rdm(N,xi,1); //use 16807 to generate N random number in [0,1]; 1:use time seed

    //read data
    FILE* Data=NULL;
    Data=fopen("data_np.txt","r");
    double cnt=0;
    for (int i=0; i<L; i++) {
		fscanf(Data,"%d",&E[i]);
		fscanf(Data,"%d",&C[i]);
		cnt += C[i];
	}
    fclose(Data);
    for (int i = 0; i < L; i++)
    {
        p[i]=C[i]/cnt; //normalized p
    }
	 
    //write sampling into sampling.txt

    FILE* sampling;
    sampling=fopen("direct_sampling.txt","w+");
    double temp;
    for (int i = 0; i < L; i++)
    {   
        if(i==0)
        P[0]=p[0];
        else P[i]=p[i]+P[i-1];
    }
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < L; j++)
        {
            if(xi[i]>P[j]) continue;
            else 
            {
                fprintf(sampling,"%d\n",E[j]);
                break;
            }
        }   
    }
    fclose(sampling);
    free(xi);

    //Task2: accept_reject_sampling 
    double *xi1;//[0,1] random number
    double *xi2;//[0,1] random number
    double *xix;//xix number
    double *xiy;//xiy random number
    cnt=0; //counting efficiency 
    xi1=(double*) malloc(N*sizeof(double));
    xi2=(double*) malloc(N*sizeof(double));
    xix=(double*) malloc(N*sizeof(double));
    xiy=(double*) malloc(N*sizeof(double));
    rdm(N,xi1,1);
    sleep(1);
    rdm(N,xi2,1);

    for (int i = 0; i < N; i++)
    {
        if(0<=xi1[i]&&xi1[i]<0.556466)
        xix[i]=168.923*xi1[i]+2900;
        else if(xi1[i]>=0.556466&&xi1[i]<0.988799)
        xix[i]=25.4274*xi1[i]+2979.86;
        else xix[i]=732.00*xi1[i]+2281.00;
    }
    
    //write data into reject_sampling.txt
    FILE* r=NULL;
    r=fopen("reject_sampling.txt","w+");
    for (int i = 0; i < N; i++)
    {   
        //linear interpolation 
        int m1=floor(xix[i]);
        int m2=ceill(xix[i]);
        double fx=p[m1-2900]*(xix[i]-m2)/(m1-m2)+p[m2-2900]*(xix[i]-m1)/(m2-m1);
        if(xi2[i]*F(xix[i])<fx)
        {
            fprintf(r,"%f\n",xix[i]);
            cnt+=1;
        }      
    }
    printf("Efficiency is :%f ",(double)cnt/N);
	return 0;
}
