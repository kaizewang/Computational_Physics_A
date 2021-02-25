#include<math.h>
#include<fstream>
#include"rdm.h"
#define pi 3.1415926536

//use MC & significant sampling to compute integral

double f(double x)
{
    return 1/(pow(x,2)+pow(cos(x),2));	
}

double g(double x, double a)
{
    return exp(-a*x);
}

int main()
{   
    int N=1000; //number of samples
    double *x=new double[N];
    double sum,ssum;    // sum: summation of f/g,ssum:summation of f/g square 
    double amin=0.6;	//amin: the value of a when sigma_f reaches minimun
    double mu,sigma,sig_min=1E4;	
	// mu: average of f/g,sigma:sigma_f,sig_min:a cretirion
    
    //Task1: compute integral with different a value, find a_min
    std::ofstream var("var_diff_a.txt");
    
	for (double a=0.6;a<=0.9;a+=0.01)
	{	
	    sum=0,ssum=0;
    	double *y=new double[N];
    	rdm(N,y,1);
        for(int i=0;i<N;i++)
        {
	        y[i]=(1-exp(-a*pi))*y[i]/a;
	        x[i]=log(1-a*y[i])/(-a);
	        sum+=f(x[i])/g(x[i],a); 
	        ssum+=pow(f(x[i])/g(x[i],a),2);
	    }
	    mu=sum/N;
	    sigma=sqrt(ssum/N-mu*mu);
	    var<<a<<','<<sigma<<'\n';
	    if(sig_min>sigma) {amin=a,sig_min=sigma;}
    }
    std::cout<<"a_min="<<amin<<std::endl;
    var.close();
    delete x;
    
    //Task2: use a_min to compute integral with different sample numbers N
    std::ofstream In("Integral.txt");
    for (int j=2;j<=6;j++)// N: 100 1000 10000 100000
	{	
	    N=(int) (pow(10,j));
	    sum=0,ssum=0;
    	double *y=new double[N];
    	double temp;
    	rdm(N,y,1);
        for(int i=0;i<N;i++)
        {
	        y[i]=(1-exp(-amin*pi))*y[i]/amin;
	        temp=log(1-amin*y[i])/(-amin);
	        sum+=f(temp)/g(temp,amin); 
	        ssum+=pow(f(temp)/g(temp,amin),2);
	    }
	    mu=sum/N;
	    sigma=sqrt(ssum/N-mu*mu);
	    In<<N<<'\t'<<mu*(1-exp(-amin*pi))/amin<<'\t'<<
		sigma/sqrt(N)*(1-exp(-amin*pi)/amin)<<'\n';
	    delete y;
	// output the results
	/*std::cout<<"a_min="<<amin<<std::endl;
	std::cout<<"The average of the integral is:"<<mu*(1-exp(-amin*pi))/amin<<std::endl;
    std::cout<<"The standard variance of the integral is:"<<sigma<<std::endl;
    std::cout<<'\n';*/
    
	}
	
    return 0;
}
	
	
	
