#include<stdio.h>
#include<time.h>
//This header file includes a function void rdm(int N,double*x,int method) N:length of array x 
static int I=46984;

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

double rdm()  //return random numbers in (0,1)  method=0 default method=1 timeseed
{   
    int a=16807,b=0,m=2147483647;
	double x;
	I=schrage(a,m,I)+b%m; 
	x=(double)I/m;
	return x;
}



