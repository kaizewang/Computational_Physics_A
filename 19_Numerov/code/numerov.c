#include<stdio.h>
#include<math.h>

#define epsilon 0.01
#define mesh 1000

//Numerically solving shrodinger equation by Numerov method
double F(double x, double EG)// compute fn
{
    return 0.25*x*x+epsilon*pow(x,4)-EG;
}

double Y(double x, double EG, double phi, double h)// compute y(xn)
{
    return (1-pow(h,2)*F(x,EG)/12)*phi;
}

double Integrate(double* phi, int n, double h)// computing the integration for normalization 
{
    double t=0;
    for (int i = 1; i < n; i++)
    {
        t+=phi[i]*phi[i]*h;
    }
    return t;
}


int main()
{
    double x0=6;
    double h=2.0*6/mesh;
    double Delta=0.001;
    double phi[mesh]={};
    phi[1]=1E-4;
    //double EG=0.50;//grpund state energy (guess value)
    double EG=1.50;//exitied state energy (guess value)
    for(int i=1;i<mesh-1;i++)
    {
            double x1=-x0+h*(i-1);
            double x2=-x0+h*i;
            double y1=Y(x1,EG,phi[i-1],h);
            double y2=Y(x2,EG,phi[i],h);
            phi[i+1]=(2*y2-y1+h*h*F(x2,EG)*phi[i])/(1-h*h*F(x2,EG)/12);
    }
    //while(fabs(phi[mesh-1])>1E-4) //ground state computing
    while(fabs(phi[mesh-1])>5E-4) //excited state computing
    {   
        EG+=Delta;
        double temp=phi[mesh-1];
        for (int i = 0; i < mesh; i++)
        {
            phi[i]=0;
        }
        phi[1]=1E-4;
        for(int i=1;i<mesh-1;i++)
        {
            double x1=-x0+h*(i-1);
            double x2=-x0+h*i;
            double y1=Y(x1,EG,phi[i-1],h);
            double y2=Y(x2,EG,phi[i],h);
            phi[i+1]=(2*y2-y1+h*h*F(x2,EG)*phi[i])/(1-h*h*F(x2,EG)/12);
        }
        if(phi[mesh-1]*temp<0)
        {
            EG-=Delta;
            Delta=Delta/10;// smaller Delta to find a more accurate energy
        }
    }
    printf("%f\t%f",phi[mesh-1],EG);
    //computing ground state
    /*FILE* ground;
    ground=fopen("ground_state_1.txt","w+");
    for (int i = 0; i < mesh; i++)
    {
        if(i==0) fprintf(ground,"E0=%f\tepsilon=%f\n",EG,epsilon);
        fprintf(ground,"%f\t%f\n",-x0+h*i,phi[i]/sqrt(Integrate(phi,mesh,h)));
    }
    fclose(ground);*/
    //computing excited state
    FILE* excited;
    excited=fopen("excited_state_4.txt","w+");
    for (int i = 0; i < mesh; i++)
    {
        if(i==0) fprintf(excited,"E0=%f\tepsilon=%f\n",EG,epsilon);
        fprintf(excited,"%f\t%f\n",-x0+h*i,phi[i]/sqrt(Integrate(phi,mesh,h)));
    }
    fclose(excited);
    
}