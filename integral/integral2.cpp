#include<math.h>
#include<fstream>
#include<iomanip>
#include"rdm.h"
#define I 1.045301308139

//compute integral of sqrt(x+sqrt(x))
double f(double x,double y,double z,double u,double v)
{   
    return 6.-x*x-y*y-z*z-u*u-v*v; 
}

int main()
{   
    std::ofstream in("integral.txt");
    in<<"N"<<'\t'<<"Integral"<<'\t'<<"Err"<<'\n';
  
    int N=0;
    double sum=0;
    double x[5]={7/10.0, 4/5.0, 9/10.0, 1.0, 11/10.0};
    for(int i=1;i<=7;i++){
    	sum=0;
    	N=(int) pow(10,i);
        double *xi=new double[5*N];
        rdm(5*N,xi,1);
        for(int j=0;j<5*N;j+=5)
        {
		    sum+=f(x[j%5]*xi[j],x[(j+1)%5]*xi[j+1],x[(j+2)%5]*xi[j+2],x[(j+3)%5]*xi[j+3],
		    x[(j+4)%5]*xi[j+4])*x[0]*x[1]*x[2]*x[3]*x[4];
		}
        std::cout<<std::setprecision(15)<<N<<" Integral="<<sum/N<<std::endl;
	    in<<std::setprecision(15)<<N<<"\t\t"<<sum/N<<"\t\t"<<fabs(sum/N-I)<<std::endl;
	    
	}  
	return 0;
}
