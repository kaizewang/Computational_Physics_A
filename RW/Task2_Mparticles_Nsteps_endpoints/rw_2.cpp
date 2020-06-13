#include<math.h>
#include<string>
#include<fstream>
#include<iomanip>
#include"rdm.h"

//generate data of ensemble of random walks

//input dimension d 1,2,3 and the number of steps N
void gen(int d,double ** arr,int N)// generate data of one particle
{
    
    for(int i=0;i<d;i++)
    {
	    arr[i]=new double[N];
	    rdm(N,arr[i],1);
	    for(int j=0;j<N;j++)
	    {
		    arr[i][j]=arr[i][j]-1./2;
		}
	}
}

int main()
{   
    int M=10000;//number of particles
    int N=1;  //number of steps
    int d=2; //dimension
    char s[30];
    sprintf(s,"rw_endpoints_%dsteps.txt",N);
    std::ofstream data(s);
    for(int i=1;i<=M;i++){//particles
	    double **arr;
	    arr=new double* [d];
	    gen(d,arr,N);
	    
		data<<"particle"<<i<<std::endl;
	    
		double* x=new double[d];
		for(int i=0;i<d;i++)
	    {
		    x[i]=0;
		}
	    
		for(int k=0;k<d;k++)//steps
		{   
		    for(int j=0;j<N;j++)
		    {   
		        x[k]+=arr[k][j];
		    }
		    data<<std::setw(12)<<x[k]<<'\t';
			if (k==d-1)  data<<'\n'; 
	    }
	    delete x,arr;
	}
    data.close();
}
