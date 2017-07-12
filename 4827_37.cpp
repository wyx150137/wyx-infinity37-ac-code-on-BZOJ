
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const double PI = 3.14159265358979323;
const int N = 4e5+5;
typedef long long ll;
struct cp
{
	double x,y;
	cp(double _x=0,double _y=0):x(_x),y(_y){}
	friend cp operator +(const cp &a,const cp &b)
	{
		return cp(a.x+b.x,a.y+b.y);
	}
	friend cp operator -(const cp &a,const cp &b)
	{
		return cp(a.x-b.x,a.y-b.y);
	}
	friend cp operator *(const cp &a,const cp &b)
	{
		return cp(a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x);
	}
}a[N],b[N],c[N];
void FFT(cp *a,int len,int type)
{
	int t = 0;
	for(int i = 0;i<len;i++)
	{
		if(t<i)swap(a[t],a[i]);
		for(int j = len>>1;(t^=j)<j;j>>=1);
	}
	for(int i = 2;i<= len;i<<=1)
	{
		cp wn = cp(cos(PI*2*type/i),sin(PI*2*type/i));
		for(int j = 0;j<len;j+=i)
		{
			cp t,w(1,0);
			for(int k = 0;k<(i>>1);k++,w=w*wn)
			{
				t = a[j+k+(i>>1)]*w;
				a[j+k+(i>>1)] = a[j+k]-t;
				a[j+k] = a[j+k]+t;
			}
		}
	}
	if(type==-1)
		for(int i = 0;i<len;i++)
			a[i].x/=len;
}
ll ans[N];
void conv(cp *a,cp *b,cp *c,int len)
{
	FFT(a,len,1),FFT(b,len,1);
	for(int i = 0;i<len;i++)c[i] = a[i]*b[i];
	FFT(c,len,-1);
	for(int i = 0;i<len;i++)ans[i]=(ll)(c[i].x+0.5);
}
int main()
{
	int n,m,x;
	scanf("%d%d",&n,&m);
	ll c2 = 0;
	ll c11 = 0,c12 = 0;
	for(int i = 0;i< n;i++)
	{
		scanf("%d",&x);
		c2 += x*x;
		c11+=x;
		c12-=x;
		a[i].x = x;
	}
	for(int i = 0;i< n;i++)
	{
		scanf("%d",&x);
		c2 += x*x;
		c11-=x;
		c12+=x;
		b[i].x = x;
	}
	for(int i = 0;i<n;i++)
	{
		a[i+n] = a[i];
		if(i<n-i-1)swap(b[n-i-1],b[i]);
	}
	int l = 1;
	for(l=1;l<=n*4;l<<=1);
	conv(a,b,c,l);
	ll Ans = 1e18;
	for(int i = 0;i<n;i++)
		for(int j = 0;j<=m;j++)
		{
			Ans = min(Ans,c2+c11*j*2-ans[n+i-1]*2+n*j*j);
			Ans = min(Ans,c2+c12*j*2-ans[n+i-1]*2+n*j*j);
		}
	printf("%lld\n",Ans);
	return 0;
}
