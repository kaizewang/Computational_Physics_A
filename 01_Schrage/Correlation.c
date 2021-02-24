#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<math.h>
//16807 generator

int schrage(int a,int m,int In)
{
	//using Schrage method to get module
	int  q,r,zmodq,zdq;//zmodq: In mod q, zdq: [z/q]
	q=m/a,r=m%a;
	zmodq=In%q,zdq=In/q;
	int t;
	t=a*zmodq-r*zdq;
	if (t<0) t+=m;
	return t;
}



int initial(int n)
{
	if (n==1){
	time_t tmpcal_ptr;
	struct tm *tmp_ptr;
	time (&tmpcal_ptr);
	tmp_ptr = gmtime(&tmpcal_ptr);
    int iy=tmp_ptr->tm_year,im=tmp_ptr->tm_mon,id=tmp_ptr->tm_mday;
    int ih=tmp_ptr->tm_hour,in=tmp_ptr->tm_min,is=tmp_ptr->tm_sec;
    int I=iy+70*(im+12*(id+23*(in+59*is)));
	FILE* date=NULL;
	date=fopen("time_seed.txt","a");
	fprintf(date,"%d.%d.%d.\t%d:%d:%d\tI%d\n",1900+tmp_ptr->tm_year,1+tmp_ptr->tm_mon,tmp_ptr->tm_mday,8+tmp_ptr->tm_hour,tmp_ptr->tm_min,tmp_ptr->tm_sec);
    return I;}
    else return 1;
    
}


int main()
{
    int a=16807,b=0,m=2147483647;
    int N=1E7;//number of samples 
    int max=1E4;//number of correlation coefficients c(1)--c(max)

    //Task1: Attain N random numbers by 16807
    int I=initial(1);// initial(0): default value I=1; initial(1): use time seed;

	double *x;
    x=(double* )malloc(N*sizeof(double));
	for(int i=0;i<N;i++){//attain random numbers in an array x
	    I=schrage(a,m,I)+b%m; 
	    x[i]=(double)I/m;
	}

    //Task2:Compute average of x^k and correlation coefficient 
	    // average of x^k 
	double sum=0;
	double* average;//average is the array of elements [<x^1>,<x^2>,<x^3>,<x^4>]
    average=(double*)malloc(4*sizeof(double));

	for(int k=1;k<5;k++)
	{ 
		sum=0;
	    	for(int i=1;i<N;i++){
	        sum+=pow(x[i],k);
	    }
	    average[k-1]=sum/N;
		printf("The average <x_%d> is:%f\n",k,average[k-1]);
	}
	sum=0;

    // correlation C(l)  from l=1 to max
	double* c;
    c=(double*)malloc(max*sizeof(double));
	for(int l=0;l<max;l++)
	{
		sum=0;
	    for(int i=0;i<N-l;i++){
	    sum+=x[i]*x[i+l];
		}
	c[l]=(sum/(N-l)-average[0]*average[0])/(average[1]-average[0]*average[0]);
	}
	
	//Write data into txt.
    char str[30];
    FILE* File2;
	sprintf(str,"C(l)(l=1-%d,N=%d).txt",max,N);
	File2=fopen(str,"w+");
    for(int i=1;i<max;i++)
	{   
        fprintf(File2,"%d\t%f\n",i,c[i]);
	}
	fclose(File2);
    free(average);
	free(c);
	//free two arrays
	free(x);
    return 0;
}