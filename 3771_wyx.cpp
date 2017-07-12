
#include <cmath>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 262144+50;
const double PI = M_PI;
typedef long long LL;
typedef double f2;

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

struct cp{
	f2 a, b;
	cp (f2 _x = 0,f2 _y = 0) :a(_x), b(_y){}
	cp operator + (const cp &z) const {return cp(a+z.a,b+z.b);}
	cp operator - (const cp &z) const {return cp(a-z.a,b-z.b);}
	cp operator * (const cp &z) const {return cp(a*z.a-b*z.b,a*z.b+b*z.a);}
} a[N], b[N], c[N], A[N], d[N], x, y;

int dig[35], rev[N], n, l;

inline void FFT(cp *a,int type) {
	for(int i=0;i<n;++i) A[i] = a[rev[i]];
	for(int i=0;i<n;++i) a[i] = A[i];
	for(int i=2;i<=n;i<<=1) {
		cp wn(cos(2*PI/i),type*sin(2*PI/i));
		for(int k=0;k<=n;k+=i) {
			cp w(1,0);
			for(int j=k;j<k+i/2;++j,w=w*wn) {
				x = a[j], y = a[j+i/2] * w;
				a[j] = x + y, a[j+i/2] = x - y;
			}
		}
	}
	if(type == -1) for(int i=0;i<n;++i) a[i].a /= n;
}

int main() {
	cin >> n;
	int len = 0;
	for(int i=1;i<=n;++i) {
		int tmp = read();
		a[tmp].a = 1;
		b[2*tmp].a = 1;
		c[3*tmp].a = 1;
		len = max(len,3*tmp);
	}
	for(n=1,l=0;n<=len;n<<=1,l++);
	for(int i=0;i<n;++i) {
        int len = 0;
        for(int t=i;t;t>>=1) dig[len++] = t & 1;
        for(int j=0;j<l;j++) rev[i] = (rev[i]<<1)|dig[j];
    }
	FFT(a,1); FFT(b,1); FFT(c,1);
	cp tmp3(3,0),  tmp2(2,0), tmp6(1.0/6.0,0), t2 (1.0/2.0);
	for(int i=0;i<n;++i) 
		d[i] = (a[i] * a[i] * a[i] - tmp3 * a[i] * b[i] + tmp2 * c[i]) * tmp6 + (a[i] * a[i] - b[i]) * t2 + a[i];
	FFT(d,-1);
	for(int i=1;i<=len;++i) {
		LL tmp = (LL)(d[i].a + 0.5);
		if(tmp != 0) printf("%d %lld\n", i, tmp);
	}
	return 0;
}
