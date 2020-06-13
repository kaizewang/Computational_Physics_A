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
    int N=5;  //number of steps
    int d=1; //dimension
    double as=0;// counting step size in RMS, as=a^2 
    char s[30];// s is just used for the convenience of writing filename 
    sprintf(s,"rw_endpoints_%dsteps.txt",N);
    std::ofstream data(s);
    for(int i=1;i<=M;i++){//particles
	    double **arr;
	    arr=new double* [d];
	    gen(d,arr,N);
	    
		data<<"particle"<<i<<std::endl;
	    
		double* x=new double[d];// x[1]:x coordiante  x[2]:y coordinate ... 
		for(int i=0;i<d;i++)
	    {
		    x[i]=0;
		}
	    
		for(int k=0;k<d;k++)//dimension :i=0->x dimension i=1->y dimension...
		{   
		    for(int j=0;j<N;j++)//N steps
		    {   
		        x[k]+=arr[k][j];
		        as+=pow(arr[k][j],2)/N/M;
		    }
		    data<<std::setw(12)<<x[k]<<'\t';
			if (k==d-1)  data<<'\n'; 
	    }
	    delete x,arr;
	}
    data.close();
    std::cout<<"a^2="<<as<<std::endl;
}
