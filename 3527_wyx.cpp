
#include <cmath>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = (100000+5) << 2;
const double PI = M_PI;
using namespace std;

struct cp
{
	double a,b;
	cp (double _a=0,double _b=0) :a(_a),b(_b){}
	cp operator + (const cp &z) const {return cp(a+z.a,b+z.b);}
	cp operator - (const cp &z) const {return cp(a-z.a,b-z.b);}
	cp operator * (const cp &z) const {return cp(a*z.a-b*z.b,a*z.b+b*z.a);}
}a[N],b[N],c[N],A[N],x,y;

int n=1,l,rev[N],dig[40];

void FFT(cp *a,int type)
{
	for(int i=0;i<n;++i) A[i] = a[rev[i]];
	for(int i=0;i<n;++i) a[i] = A[i];
	for(int i=2;i<=n;i<<=1) {
		cp wn(cos(2*PI/i),type*sin(2*PI/i));
		for(int k=0;k<n;k+=i) {
			cp w(1,0);
			for(int j=k;j<k+i/2;j++,w=w*wn) {
				x = a[j], y = a[j+i/2]*w; a[j] = x + y,  a[j+i/2] = x - y;
			}
		}
	}
	if(type == -1) for(int i=0;i<n;++i) a[i].a /= n;
}

double q[N],ans[N];

int main()
{
	int tmp ; cin >> tmp;
	for(int i=0;i<tmp;++i) scanf("%lf",&q[i]);
	for(;n<=tmp<<1;n<<=1,l++);
	for(int i=0,t,len=0;i<n;++i,len=0)
	{
		for(t=i;t;t>>=1) dig[len++] = t & 1;
		for(t=0;t<l;++t) rev[i] = (rev[i]<<1) |  dig[t];
	}
	for(int i=0;i<tmp;++i) a[i] = cp(q[i]);
	for(int i=1;i<tmp;++i) b[i] = cp(1.0/i/i);
	FFT(a,1); FFT(b,1); for(int i=0;i<n;++i) c[i] = a[i] * b[i]; FFT(c,-1);
	for(int i=0;i<tmp;++i) ans[i] = c[i].a;
	memset(a,0,sizeof a); memset(b,0,sizeof b);
	for(int i=0;i<tmp;++i) a[i] = cp(q[tmp-i-1]);
	for(int i=1;i<tmp;++i) b[i] = cp(1.0/i/i);
	FFT(a,1); FFT(b,1); for(int i=0;i<n;++i) c[i] = a[i] * b[i]; FFT(c,-1);
	for(int i=0;i<tmp;++i) ans[i] -= c[tmp-i-1].a;
	for(int i=0;i<tmp;++i) printf("%lf\n",ans[i]);
}
