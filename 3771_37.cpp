
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 5e5+5;
const double PI = 3.14159265358979323;
struct cp
{
	double x,y;
	cp(double x = 0,double y = 0):x(x),y(y){}
	friend cp operator+(const cp &a,const cp &b)
	{
		return cp(a.x+b.x,a.y+b.y);
	}
	friend cp operator-(const cp &a,const cp &b)
	{
		return cp(a.x-b.x,a.y-b.y);
	}
	friend cp operator*(const cp &a,const cp &b)
	{
		return cp(a.x*b.x-a.y*b.y,a.x*b.y+b.x*a.y);
	}
}a[N],b[N],c[N],d[N];
void FFT(cp *a,int len,int type)
{
	int t = 0;
	for(int i = 0;i<len;i++)
	{
		if(t<i)swap(a[i],a[t]);
		for(int j = len>>1;(t^=j)<j;j>>=1);
	}
	for(int i=2;i<=len;i=i<<1)
	{
		cp wn = cp(cos(2*PI*type/i),sin(2*PI*type/i));
		for(int j = 0;j<len;j+=i)
		{
			cp w = cp(1,0),t;
			for(int k = 0;k<(i>>1);k++,w=w*wn)
			{
				t = w*a[j+k+(i>>1)];
				a[j+k+(i>>1)] = a[j+k]-t;
				a[j+k] = a[j+k]+t;
			}
		}
	}
	if(type==-1)
		for(int i = 0;i<len;i++)
			a[i].x/=len;
}
int A[N];
int main()
{
	int maxa = -1,n;
	scanf("%d",&n);
	n--;
	for(int i = 0;i<= n;i++)
	{
		scanf("%d",&A[i]);
		a[A[i]].x=1,b[2*A[i]].x=1,c[3*A[i]].x=1;
		maxa = max(maxa,3*A[i]);
	}
	int m=maxa,L=0;
    for(n=1;n<=m;n<<=1)L++;
    FFT(a,n,1),FFT(b,n,1),FFT(c,n,1);
	for(int i = 0;i<=n;i++)
	{
		cp tmp = cp(1.0/6.0,0),tmp2 = cp(3.0,0),tmp3 = cp(2.0,0),tmp4 = cp(1.0/2.0,0);
		d[i]=d[i]+(a[i]*a[i]*a[i]-tmp2*a[i]*b[i]+tmp3*c[i])*tmp;
        d[i]=d[i]+(a[i]*a[i]-b[i])*tmp4;
        d[i]=d[i]+a[i];
	}
	FFT(d,n,-1);
	for(int i = 0;i<= maxa;i++)
	{
		int ans = (int)(d[i].x+0.1);
		if(ans!=0)printf("%d %d\n",i,ans);
	}
	return 0;
}
