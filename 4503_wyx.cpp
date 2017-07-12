
#include <cmath>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const double PI = M_PI;
const int N = 100005 *4;
const double eps = 1e-7;
using namespace std;

struct cp
{
	double a,b;
	cp (double _a=0,double _b=0) :a(_a),b(_b){}
	cp operator+(const cp &z) const {return cp(a+z.a,b+z.b);}
	cp operator-(const cp &z) const {return cp(a-z.a,b-z.b);}
	cp operator*(const cp &z) const {return cp(a*z.a-b*z.b,a*z.b+b*z.a);}
}a[N],b[N],A[N],c1[N],c2[N],c3[N],x,y;

int n=1, rev[N], dig[40];

void FFT(cp *a,int type)
{
	for(int i=0;i<n;++i) A[i] = a[rev[i]];
	for(int i=0;i<n;++i) a[i] = A[i];
	for(int i=2;i<=n;i<<=1) {
		cp wn(cos(2*PI/i),type*sin(2*PI/i));
		for(int k=0;k<n;k+=i) {
			cp w(1,0);
			for(int j=k;j<k+i/2;++j,w=w*wn) {
				x = a[j], y = a[j+i/2]*w;
				a[j] = x + y, a[j+i/2] = x - y;
			}
		}
	}
	if(type == -1) for(int i=0;i<n;++i) a[i].a /= n;
}

char str1[N],str2[N];
int tmp1[N],tmp2[N];
int ans[N];

int main()
{
	scanf("%s%s",str1,str2);
	int len1 = strlen(str1), len2 = strlen(str2), mx = max(len1,len2),l=0;
	for(;n<=mx<<1;n<<=1,l++);
	for(int i=0,t=0,len=0;i<n;++i,len=0) {
		for(t=i;t;t>>=1) dig[len++] = t & 1;
		for(t=0;t<l;++t) rev[i] = (rev[i]<<1)|dig[t];
	}
	for(int i=0;i<len1;++i) tmp1[i] = str1[i] - 'a'+1;
	for(int i=0;i<len2;++i) tmp2[i] = str2[len2-i-1] - 'a'+1;
	for(int i=0;i<len2;++i) if(str2[i] == '?') tmp2[len2-i-1] = 0;
	for(int i=0;i<len1;++i) a[i] = cp((double)tmp1[i]*tmp1[i]*tmp1[i]);
	for(int i=0;i<len2;++i) b[i] = cp((double)tmp2[i]);
	FFT(a,1); FFT(b,1); for(int i=0;i<n;++i) c1[i] = a[i] * b[i]; FFT(c1,-1);
	memset(a,0,sizeof a); memset(b,0,sizeof b);
	for(int i=0;i<len1;++i) a[i] = cp((double)tmp1[i]);
	for(int i=0;i<len2;++i) b[i] = cp((double)tmp2[i]*tmp2[i]*tmp2[i]);
	FFT(a,1); FFT(b,1); for(int i=0;i<n;++i) c2[i] = a[i] * b[i]; FFT(c2,-1);
	memset(a,0,sizeof a); memset(b,0,sizeof b);
	for(int i=0;i<len1;++i) a[i] = cp((double)tmp1[i]*tmp1[i]);
	for(int i=0;i<len2;++i) b[i] = cp((double)tmp2[i]*tmp2[i]);
	FFT(a,1); FFT(b,1); for(int i=0;i<n;++i) c3[i] = a[i] * b[i]; FFT(c3,-1);
	for(int i=len2-1;i<len1;++i) if(c1[i].a + c2[i].a - 2*c3[i].a < eps) ans[++ans[0]] = i;
	cout << ans[0] << endl; for(int i=1;i<=ans[0];++i) printf("%d\n",ans[i]-len2+1);
}
