#include <stdio.h>
#include <math.h>
#define pi 3.1415926535897932384626433832795028841971
float lyambda=0.1;
double f(double omega,double korner)
{
    return (-2*omega*lyambda-sin(korner));
}
int main()
{
    FILE* file;
    file = fopen("out.txt","w");
    double tau=2*pi/1000;
    double tau1=tau/2;
    int n,nbw=0,nlw=1,N=9*2*pi/tau+1;
    double fi[2*N],w[2*N],t[2*N],bw=0,lw=10,Delta[N];
    fi[0]=-pi+pi/10000, w[0]=0, Delta[0]=0, t[0]=0, t[-1]=-tau;
    printf("N=%d Fi0=%lf\n",2*N,fi[0]);
    for(n=0;n<=N;n++)
    {
        if(bw<w[n]) {
            bw=w[n]; nbw=n;}
        if((lw>fabs(w[n]))&&(fi[n]>fi[nlw])&&(fi[n]>0)){
            lw=w[n]; nlw=n;}
        t[n]=t[n-1]+tau, t[n+1]=t[n]+tau;
        w[n+1]=w[n]+tau/2*(f(w[n],fi[n])+f(w[n]+tau*f(w[n],fi[n]),fi[n]+tau*w[n]));
        fi[n+1]=fi[n]+tau*w[n]+tau*tau/2*f(w[n],fi[n]);
    }
    printf("Point of extremum:\n MaxW=%lf\n fi=%lf\nPoint of spin:\n fi=%lf\n",bw,fi[nbw],fi[nlw]);
    double SavedFi=fi[N];
    bw=0,lw=10;
    t[-1]=-tau1;
    for(n=0;n<=N*2;n++)
    {
        if(bw<w[n]) {
            bw=w[n]; nbw=n;}
        if((lw>fabs(w[n]))&&(fi[n]>fi[nlw])&&(fi[n]>0)){
            lw=w[n]; nlw=n;}
        t[n]=t[n-1]+tau1, t[n+1]=t[n]+tau1;
        w[n+1]=w[n]+tau1/2*(f(w[n],fi[n])+f(w[n]+tau1*f(w[n],fi[n]),fi[n]+tau1*w[n]));
        fi[n+1]=fi[n]+tau1*w[n]+tau1*tau1/2*f(w[n],fi[n]);
        if(lyambda==0)
            Delta[n]=fabs(fabs(w[n])-sqrt(fabs(2*cos(fi[n])-2*cos(-pi+pi/10000))));
        fprintf(file,"%lf %lf %lf %lf\n",t[n],fi[n],w[n],Delta[n]);
    }
    printf("Point of extremum:\n MaxW=%lf\n fi=%lf\nPoint of spin:\n fi=%lf\n",bw,fi[nbw],fi[nlw]);
    fclose(file);
    return 0;
}
