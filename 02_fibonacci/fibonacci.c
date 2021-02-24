#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<math.h>
//homework 1-2 

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
	fprintf(date,"%d.%d.%d.\t%d:%d:%d\tI:%d\n",1900+tmp_ptr->tm_year,1+tmp_ptr->tm_mon,tmp_ptr->tm_mday,8+tmp_ptr->tm_hour,tmp_ptr->tm_min,tmp_ptr->tm_sec);
    return I;}
    else return 1;
    
}


int main()
{	
	int a=16807;
	int b=0;
	int m=2147483647;
    int N=1E5;//number of samples 
    //Task1: Attain N random numbers by 16807 generator 
    int I=initial(0);// initial(0): default value I=1 initial(1): time seed;
	double *x;
    x=(double* )malloc(N*sizeof(double));
	for(int i=0;i<N;i++)
	{	//attain random numbers in an array x
	    I=schrage(a,m,I)+b%m; 
	    x[i]=(double)I/m;
	}
	
    //Task2: Attain N random numbers by fibonacci generator 
    double *f;
    f=(double* )malloc(N*sizeof(double));
	int p[6],q[6]; //Try 5 (q,p) values to see different results 
	//the following (p,q) are suggested on page 29 of volume 2 of The Art of Computer Programming
	p[0]=24,p[1]=38,p[2]=37,p[3]=30,p[4]=103;
	q[0]=55,q[1]=89,q[2]=100,q[3]=127,q[4]=250;
	//This (p,q) satisfies: p^2+q^2+1=prime
	p[5]=3,q[5]=31;
    int pv=0,qv=0; //pv=p-value qv=q-value 
	FILE* Ratio;// prepare a file to write the final result 
	Ratio=fopen("ratio.txt","w+");
	for (int j = 0; j < 6; j++)// j goes through all four (p,q)
	{
		pv=p[j],qv=q[j];
		I=initial(0);// use default initial value
		for (int i = 0; i < qv; i++)
		{	
			I=schrage(a,m,I)+b%m;
			f[i]=I;	//use 16807 generate the initial condition of fibonacci
		}
		for (int i = qv; i < N; i++)
		{
			f[i]=(double)(((int)f[i-qv]-(int)f[i-pv])%m);
		}
		for (int i = 0; i < N; i++)
		{
			f[i]=f[i]/m;
		}


		//Task3: counting the number of this kind of relation: X_n-1<X_n+1<X_n in fibonacci generator with different (p,q)
		int n2=0;
		double ratio2=0;
		for (int i=0;i<N-2;i++)
		{
		if(f[i]<f[i+2]&&f[i+2]<f[i+1]) n2++;
		}
		ratio2=(double) n2/N;
		printf("The ratio of relation X_n-1<X_n+1<X_n in fibonacci generator is: %f\n",ratio2);
		fprintf(Ratio,"The ratio of relation X_n-1<X_n+1<X_n in fibonacci generator with (q,p)=(%d,%d) is: %f\t%f\n",qv,pv,ratio2,ratio2-1./6);
	}
	//Task3: counting the number of this kind of relation: X_n-1<X_n+1<X_n in 16807 generator 
	int n1=0;
	double ratio1=0;
	for (int i=0;i<N-2;i++)
	{
		if (x[i]<x[i+2]&&x[i+2]<x[i+1])	n1++;
	}
	ratio1=(double) n1/N;
	printf("The ratio of relation X_n-1<X_n+1<X_n in 16807 generator is: %f\n",ratio1);
	fprintf(Ratio,"The ratio of relation X_n-1<X_n+1<X_n in 16807 generator is: %f\t%f\n",ratio1,ratio1-1./6);
	fclose(Ratio);
	free(x);
	free(f);
	getchar();
    return 0;
}