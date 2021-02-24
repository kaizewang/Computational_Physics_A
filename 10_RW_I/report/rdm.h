#include<stdio.h>
#include<time.h>

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
	time_t tmpcal_ptr;
	struct tm *tmp_ptr;
	time (&tmpcal_ptr);
	tmp_ptr = gmtime(&tmpcal_ptr);
    int iy=tmp_ptr->tm_year,im=tmp_ptr->tm_mon,id=tmp_ptr->tm_mday;
    int ih=tmp_ptr->tm_hour,in=tmp_ptr->tm_min,is=tmp_ptr->tm_sec;
    int I=iy+70*(im+12*(id+23*(in+59*is)));
	FILE* date=NULL;
	date=fopen("time_seed.txt","a");
	fprintf(date,"%d.%d.%d.\t%d:%d:%d\n",1900+tmp_ptr->tm_year,1+tmp_ptr->tm_mon,tmp_ptr->tm_mday,8+tmp_ptr->tm_hour,tmp_ptr->tm_min,tmp_ptr->tm_sec);
    return I;}
    else return 1;
    
}

void rdm(int N,double *x,int method)  //return random numbers in (0,1)  method=0 default method=1 timeseed
{   
    int a=16807,b=0,m=2147483647;
	int I=initial(method);// initial(0): default value I=1 initial(1): time seed 
	for(int i=0;i<N;i++){//attain random numbers in an array x
	    I=schrage(a,m,I)+b%m; 
	    x[i]=(double)I/m;
	}
}



