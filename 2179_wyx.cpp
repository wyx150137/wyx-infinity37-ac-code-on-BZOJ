
#include <cmath>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const double PI = M_PI;
using namespace std;
typedef long long LL;
const int N = 140000+5;
LL sum[N];

struct cp
{
	double a,b;
	cp (double _a=0,double _b=0) :a(_a),b(_b){}
	cp operator + (const cp &z) const {return cp(a+z.a,b+z.b);}
	cp operator - (const cp &z) const {return cp(a-z.a,b-z.b);}
	cp operator * (const cp &z) const {return cp(a*z.a-b*z.b,a*z.b+b*z.a);}
}a[N],b[N],c[N],A[N],x,y;

int n=1,l,rev[N];

void FFT(cp *a,int type)
{
	for(int i=0;i<n;++i) A[i] = a[rev[i]];
	for(int i=0;i<n;++i) a[i] = A[i];
	for(int i=2;i<=n;i<<=1) {
		cp wn(cos(2*PI/i),type*sin(2*PI/i));
		for(int k=0;k<n;k+=i) {
			cp w(1,0);
			for(int j=k;j<k+i/2;++j,w=w*wn) {
				x = a[j],y = a[j+i/2] * w;
				a[j] = x + y, a[j+i/2] = x - y;
			}
		}
	}
	if(type == -1) for(int i=0;i<n;++i) a[i].a /= n;
}

char str1[N],str2[N];
int dig[40];

int main()
{
	scanf("%*d%s%s",str1,str2);
	int len1 = strlen(str1),len2 = strlen(str2);
	int base = 1,s1 = 0,s2 = 0;
	if(str1[0]=='-') base *= -1,s1 ++;
	if(str2[0]=='-') base *= -1,s2 ++;
	int mx = max(len1-s1,len2-s2);
	for(;n<mx;n<<=1,l++); n<<=1,l++;
	for(int i=0,t,len=0;i<=n;++i,len=0)
	{
		for(t=i;t;t>>=1) dig[len++] = t&1;
		for(t=0;t<l;++t) rev[i] = (rev[i]<<1)|dig[t];
	}
	for(int i=s1;i<len1;++i) a[len1-i-1] = cp((double)(str1[i] - '0'));
	for(int i=s2;i<len2;++i) b[len2-i-1] = cp((double)(str2[i] - '0'));
	FFT(a,1); FFT(b,1); for(int i=0;i<n;++i) c[i] = a[i]*b[i]; FFT(c,-1);
	for(int i=0;i<n;++i) sum[i] = (int)(c[i].a + 0.1);
	for(int i=0;i<n;++i) sum[i+1] += sum[i]/10, sum[i] %= 10;
	int Len = len1 -s1 + 1+ len2  -s2 + 1;
	while(!sum[Len]&&Len) -- Len;
	if(sum[Len] == 0) {puts("0");return 0;}
	if(base == -1) putchar('-');
	while(~Len) putchar(sum[Len--]+'0');
}
