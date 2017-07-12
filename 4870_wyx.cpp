
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;

LL n, k, mod, r;

inline LL read() {
	LL x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

struct Matrix {
	LL n, m;
	LL a[50+5][50+5];
	Matrix (LL _n=0,LL _m=0) {
		n = _n, m = _m;
		memset( a, 0, sizeof a);
	} 
	inline void init() {
		for(LL i=0;i<=n;++i) a[i][i] = 1;
	}
	inline void out() {
		for(LL i=0;i<n;++i) {
			for(LL j=0;j<n;++j) cout << a[i][j] << " " ;
			puts("");
		}
	}
} a, b;

Matrix operator * (const Matrix &a,const Matrix &b) {
	Matrix res(a.n, b.m);
	for(LL i=0;i<a.n;++i) 
		for(LL j=0;j<b.m;++j) 
			for(LL k=0;k<a.m;++k) 
				(res.a[i][j] += (LL) a.a[i][k] * b.a[k][j] % mod) %= mod;
	return res;
}

Matrix pow(Matrix a,LL b) {
	Matrix res(a.n,a.m);
	res.init();
	for(;b;b>>=1,a=a*a)
		if(b&1)
			res = res * a;
	return res;
}

int main() {
//	freopen("problem.in","r",stdin);
//	freopen("problem.out","w",stdout);
	n = read(), mod = read(), k = read(), r = read();
	a.n = a.m = k;
	for(LL i=0;i<k;++i) a.a[i][i] ++, a.a[i][(i+1)%k] ++;
	a = pow(a, (LL)n*k);
	for(LL i=0;i<k;++i) b.a[i][i] = 1;
	b.n = b.m = k;
	a = a * b;
	cout << a.a[0][r] << endl;
}
	
