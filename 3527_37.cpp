
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 6e5+5;
const double PI = 3.14159265358979323;
struct cp
{
	double x,y;
	cp(double x=0,double y=0):x(x),y(y){}
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
}x[N],y[N],z[N];
void FFT(cp *a,int len,int type)
{
	int t=0;
	for(int i = 0;i<len;i++)
	{
		if(t<i)swap(a[i],a[t]);
		for(int j = len>>1;(t^=j)<j;j>>=1);
	}
	for(int i = 2;i<= len;i<<=1)
	{
		cp wn = cp(cos(PI*type*2/i),sin(PI*type*2/i));
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
double ans[N];
void conv(cp *a,cp *b,cp *c,int len)
{
	FFT(a,len,1),FFT(b,len,1);
	for(int i = 0;i<=len;i++)
		c[i]=a[i]*b[i];
	FFT(c,len,-1);
	for(int i = 0;i<=len;i++)
		ans[i]=c[i].x;
}
int main()
{
	int n;
	scanf("%d",&n);
	n--;
	for(int i = 0;i<= n;i++)scanf("%lf",&x[i].x);
	for(int i = 0;i<n;i++)
		y[i].x = (-1.0)/((double)(n-i)*(n-i));
	for(int i = n+1;i<=2*n;i++)
		y[i].x = -y[2*n-i].x;
	int m = 4*n,L = 1,nn = n;
	for(n=1;n<=m;n=n<<1)L++;
	conv(x,y,z,n);
	//for(int i = 0;i<= m;i++)ans[i] = c[i].x;
	for(int i = nn;i<= 2*nn;i++)printf("%.5lf\n",ans[i]);
	return 0;
}
