
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 4e5+5;
const double PI = 3.14159265358979323;
struct cp
{
	double x,y;
	cp(){}
	cp(double x,double y):x(x),y(y){}
	friend cp operator+(const cp &a,const cp &b)
	{
		return cp(a.x+b.x,a.y+b.y); 
	}
	friend cp operator-(const cp &a,const cp &b)
	{
		return cp(a.x-b.x,a.y-b.y);
	}
	friend cp operator*(const cp &a,const cp&b)
	{
		return cp(a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x);
	}
}x[N],y[N],z[N];
void FFT(cp *a,int type,int len)
{
	int t=0;
	for(int i = 0;i<len;i++)
	{
		if(t<i)swap(a[i],a[t]);
		for(int j = len>>1;(t^=j)<j;j>>=1);
	}
	for(int i = 2;i<=len;i<<=1)
	{
		cp wn = cp(cos(2*PI*type/i),sin(2*PI*type/i));
		for(int j = 0;j<len;j+=i)
		{
			cp tmp,w = cp(1,0);
			for(int k = 0;k<(i>>1);k++,w=w*wn)
			{
				tmp = w*a[j+k+(i>>1)];
				a[j+k+(i>>1)] = a[j+k]-tmp;
				a[j+k] = a[j+k]+tmp;
			}
		}
	}
	if(type==-1)
		for(int i = 0;i<len;i++)
			a[i].x/=len;
}
int ans[N];
void conv(cp *a,cp *b,cp *c,int len)
{
	FFT(a,1,len);FFT(b,1,len);
	for(int i = 0;i<len;i++)
		c[i] = a[i]*b[i];
	FFT(c,-1,len);
	for(int i = 0;i<len;i++)
		ans[i] = (int)(c[i].x+0.1);
}
int Ans[N];
char s[N],A[N],B[N];
int main()
{
	int n;
	scanf("%d",&n);
	scanf("%s",s);
	for(int i = n-1;i>=0;i--)
		x[n-i-1]=cp(s[i]-'0',0);
	scanf("%s",s);
	for(int i = n-1;i>=0;i--)
		y[n-i-1]=cp(s[i]-'0',0);
	int l;
	for(l=1;l<=n;l=l<<1);
	l =l<<1;
	conv(x,y,z,l);
	long long x = 0;
	for(int i = 0;i<l;i++)
	{
		x = x+ans[i];
		Ans[i] = x%10,x/=10;
	}
	for(;l&&!Ans[l];l--);
	printf("%d",Ans[l--]);
	for(int i = l;i>=0;i--)
		printf("%01d",Ans[i]);
	printf("\n");
	return 0;
}
