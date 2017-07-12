
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef double db;
const int N = 4e5+5;
const db PI = 3.14159265358979323;
int ans[N];
struct cp
{
	db x,y;
	cp(){}
	cp(db x,db y):x(x),y(y){}
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
}x[N],y[N],z[N];
void FFT(cp *a,int len,int type)
{
	int t = 0;
	for(int i = 0;i<len;i++)
	{
		if(t<i)swap(a[i],a[t]);
		for(int j = len>>1;(t^=j)<j;j>>=1);
	}
	for(int i = 2;i<=len;i<<=1)
	{
		cp wn=cp(cos(2*PI*type/i),sin(2*PI*type/i));
		for(int j = 0;j<len;j+=i)
		{
			cp tmp,w(1,0);
			for(int k = 0;k<(i>>1);k++,w=w*wn)
			{
				tmp = w*a[j+k+(i>>1)];
				a[j+k+(i>>1)] = a[j+k]-tmp;
				a[j+k]=a[j+k]+tmp;
			}
		}
	}
	if(type==-1)
		for(int i = 0;i<len;i++)
			a[i].x/=len;
}
void conv(cp *a,cp *b,cp *c,int len)
{
	FFT(a,len,1);FFT(b,len,1);
	for(int i = 0;i<len;i++)c[i]=a[i]*b[i];
	FFT(c,len,-1);
	for(int i = 0;i<len;i++)
		ans[i]=(int)(c[i].x+0.1);
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i = 0;i< n;i++)scanf("%lf%lf",&x[i].x,&y[i].x);
	for(int i = 0;i<n/2;i++)swap(y[i],y[n-i-1]);
	int len = 1;
	while(len<=n)len<<=1;
	len<<=1;
	conv(x,y,z,len);
	for(int i = -1;i<n-1;i++)
		printf("%d\n",ans[i+n]);
	return 0;
}
