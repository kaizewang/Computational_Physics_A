#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"rdm.h"//This is a header file for generating random numbers

#define N 400 //Setting the number of meshes (N+1) x (N+1)


int main()
{   
    //coordinate of particle 
    int x=0;
    int y=0;
    int temp_x=0;
    int temp_y=0;

    int num=0;

    

    FILE* test;
    test=fopen("test.txt","w+");


    int cnt[N+1][N+1]={};
   
    
    int d=1;
    for (int j = N/2-10-d; j <= N/2-10+d; j++)
    {
        for (int k = N/2-d; k <= N/2+d; k++)
            cnt[j][k]=1;    
    }

    //Two center DLA 

    for (int j = N/2+10-d; j <= N/2+10+d; j++)
    {
        for (int k = N/2-d; k <= N/2+d; k++)
        cnt[j][k]=1;    
    }

    //int NP=3E6;//optimal number of particles in the simulation of 1 center 
    int NP=3E6;//optimal number of particles in the simulation of 2 center 
    double * config;
    config=(double*)malloc(sizeof(double)*NP);//initialize the position of particles 
    for (int i = 0; i <NP; i++)
    {
        config[i]=rdm()*N-N/2;
    }
    
    for (int i = 0; i < NP; i++)//start simulation 
    {   
        double a=rdm();
        if(a<=0.25) 
        {
            x=(int) config[i];
            y=N/2;
        }
        else if(a<=0.5)
        {
            x=(int) config[i];
            y=-N/2;
        }
        else if(a<=0.75)
        {
            y=(int) config[i];
            x=N/2;
        }
        else if(a<1)
        {
            y=(int) config[i];
            x=-N/2;
        }
        if(cnt[x+N/2][y+N/2]==1) continue;
        int flag=1;
        while(flag==1)
        {   
        double g=rdm();
        if(g<=0.25) {temp_x=1;temp_y=0;}
        else if(g<=0.5) {temp_x=-1;temp_y=0;}
        else if(g<=0.75) {temp_y=1;temp_x=0;}
        else {temp_y=-1;temp_x=0;}
        if((x+temp_x>N/2)||(x+temp_x<-N/2)||(y+temp_y<-N/2)||(y+temp_y>N/2))
        {
            flag=0;
        }
        else if (cnt[x+temp_x+N/2][y+temp_y+N/2]==1)//new point 
        {
            cnt[x+N/2][y+N/2]=1;
            num++;
            flag=0;
        }
        else// moving forward 
        {
            x+=temp_x;
            y+=temp_y;
        }       
        }
    }
    
    free(config);
    

    //writinf the cnt matrix into file 
    FILE* DLA;
    char str[20];
    sprintf(str,"size_%d_%d.txt",N+1,num);
    DLA=fopen(str,"w+");
        for (int j = 0; j < N+1; j++)
        {
            for (int k = 0; k < N+1; k++)
            {   
                if(k!=N)
                fprintf(DLA,"%d\t",cnt[j][k]);
                if(k==N) fprintf(DLA,"%d\n",cnt[j][k]);
            }
            
        }

       printf("%d",num);

    int p=0; //counting the number of particles with in sandbox

    /*FILE* sandbox;
    sandbox=fopen("sandbox.txt","w+");
    
    for(int m=0;m<=N/2;m++)
    {   
        p=0;
        for(int l=N/2-m;l<=N/2+m;l++)//counting the m x m sandbox
        {
            for(int q=N/2-m;q<=N/2+m;q++)
            {
                if(cnt[l][q]==1) p++;
            }
        }
        if(p==num+(d+1)*(d+1)) break;
        fprintf(sandbox,"%d\t%d\n",m,p);
    }*/

   FILE* Rg;
    p=0;
    Rg=fopen("Rg.txt","w+");
    double R=0;
    for(int m=0;m<N/2;m++)
    {   
        p=0;
        for (int i =N/2-m; i <=N/2+m; i++)
        {
            for (int j =N/2-m; j <=N/2+m; j++)
            {
                if(cnt[i][j]==1)
                {
                    p++;
                     R+=(double) ((i-N/2)*(i-N/2)+(j-N/2)*(j-N/2));
                }
            }
           
         }
        if(p==0) continue;
        R=sqrt(R/(double) p);
        if(p>0.8*num) break;
        fprintf(Rg,"%d\t%f\n",p,R);
    }
   
    return 0;
}