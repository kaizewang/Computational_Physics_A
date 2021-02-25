#include<math.h>
#include<fstream>
#include<iomanip>
#include"rdm.h"
#define I 1.045301308139

//compute integral of sqrt(x+sqrt(x))
double f(double x)
{
    return sqrt(x+sqrt(x)); 
}

int main()
{   
    std::ofstream in("integral.txt");
    in<<"N"<<'\t'<<"Integral"<<'\t'<<"Err"<<'\n';
  
    int N=0;
    double sum=0;
    for(int i=1;i<=8;i++){
    	sum=0;
    	N=(int) pow(10,i);
        double *xi=new double[N];
        rdm(N,xi,1);
        for(int j=0;j<N;j++)
        {
		    sum+=f(xi[j]);
		}
    std::cout<<std::setprecision(15)<<N<<" Integral="<<sum/N<<std::endl;
	in<<std::setprecision(15)<<N<<"\t\t"<<sum/N<<"\t\t"<<fabs(sum/N-I)<<std::endl;
	}  
}
