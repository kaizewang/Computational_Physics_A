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
	date=fopen("time_seed.txt","w+");
	fprintf(date,"%d.%d.%d.\t%d:%d:%d",1900+tmp_ptr->tm_year,1+tmp_ptr->tm_mon,tmp_ptr->tm_mday,8+tmp_ptr->tm_hour,tmp_ptr->tm_min,tmp_ptr->tm_sec);
    return I;}
    else return 1;
    
}


int main()
{
    int a=7,b=2,m=2147483647;
    int N=1E4;//number of samples 
	
    //Task1: Attain N random numbers by other generators
    int I=initial(0);// initial(0): default value I=1; initial(1): use time seed;

	double *x;
    x=(double* )malloc(N*sizeof(double));
	for(int i=0;i<N;i++){//attain random numbers in an array x
	    I=schrage(a,m,I)+b%m; 
	    x[i]=(double)I/m;
	}
	
	
	//Wirte data into txt.
    FILE* Data1=NULL;
	char str[50];
	sprintf(str,"other(N=%d).txt",N);
    Data1= fopen(str, "w+");
    for(int i=0;i<N;i++)
	{   
        fprintf(Data1,"%f\t",x[i]);
		if(i%2==1)
    	fprintf(Data1,"\n");
	}
	fclose(Data1);
	

	
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
	    // correlation C(l)  from l=1 to 20
	double* c;
    c=(double*)malloc(21*sizeof(double));
	for(int l=0;l<21;l++)
	{
		sum=0;
	    for(int i=0;i<N-l;i++){
	    sum+=x[i]*x[i+l];
		}
	c[l]=(sum/(N-l)-average[0]*average[0])/(average[1]-average[0]*average[0]);
	}
	for(int i=0;i<21;i++)
	{   
		printf("c_%d:\t%f\n",i,c[i]);
	}
	/*
	//Wirte data into txt.
    FILE* File1;
	sprintf(str,"average(N=%d).txt",N);
    File1=fopen(str,"w+");
    for(int i=0;i<4;i++)
	{   
        fprintf(File1,"%d\t%f\t%f\n",i+1,average[i],average[i]-(double)1/(i+2));	
	}
	fclose(File1);
    FILE* File2;
	sprintf(str,"C(l)(N=%d).txt",N);
	File2=fopen(str,"w+");
    for(int i=0;i<21;i++)
	{   
		printf("c_%d:\t%f\n",i,c[i]);
        fprintf(File2,"%d\t%f\n",i,c[i]);
	}
	fclose(File2);
	free(average);
	free(c);
	//free two arrays
	*/
	
	
	//Task3: chi-square test of 2-dimension  (we will use array x get before)
	double K0=5; // divide the whole x-y plane by K0 x K0
	double d=1/K0,mij=N/2/K0/K0;//d:length of a unit mij:average number of points
	int nij=0;
	double chisq=0;	//chisq=chi_square
	double cnt=0;	//cnt=count 
	for(int i=0;i<K0;i++){//(i,j) loop for all small units; k loop for all (x,y)
	    for(int j=0;j<K0;j++){
	    	nij=0;
		    for(int k=0;k<N/2;k++){// coordinate (x,y)=(x[2*k],x[2*k+1])
			    if(i*d<=x[2*k]&&x[2*k]<(i+1)*d&&x[2*k+1]<(j+1)*d&&j*d<=x[2*k+1]) 
			        nij=nij+1;
			}
			chisq+=pow((nij-mij),2)/mij;
		}
    }
	printf("chi-square\t%f\n",chisq);
	
	
	free(x);
	getchar();
    return 0;
}