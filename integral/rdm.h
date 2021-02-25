#include<iostream>
#include<fstream>
#include<ctime>

//This header file includes a function void rdm(int N,double*x,int method) N:length of array x 


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
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int iy=ltm->tm_year,im=ltm->tm_mon,id=ltm->tm_mday;
    int ih=ltm->tm_hour,in=ltm->tm_min,is=ltm->tm_sec;
    int I=iy+70*(im+12*(id+23*(in+59*is)));
    return I;}
    else return 1;
    
}

void rdm(int N,double *x,int method=0)  //return random numbers in (0,1)  method=0 default method=1 timeseed
{   
    int a=16807,b=0,m=2147483647;
	static int I=initial(method);// initial(0): default value I=1 initial(1): time seed 
	for(int i=0;i<N;i++){//attain random numbers in an array x
	    I=schrage(a,m,I)+b%m; 
	    x[i]=(double)I/m;
	}
}



