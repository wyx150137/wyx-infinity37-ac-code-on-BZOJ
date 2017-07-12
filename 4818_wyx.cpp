
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 100+5;
const int M = 2e7+5;
const int mod = 20170408;
#define IL __inline__ __attribute__((always_inline))
IL int modmul(const int &a, const int &b,const int &M) {
    int ret;
    __asm__ __volatile__("\tmull %%ebx\n\tdivl %%ecx\n" : "=d"(ret) : "a"(a), "b"(b), "c"(M));
    return ret;
}

int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9') {if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9') {x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

struct Matrix {
	int a[N][N], n;

	Matrix () {
		memset(a,0,sizeof a);
	}

	inline void init() {
		a[0][0] = 1;
	}
} a,  mulres;

Matrix& operator * (Matrix a,Matrix b) {
	Matrix&res = mulres;
	memset(res.a,0,sizeof res);
	res.n = a.n;
	for(int i=0;i<a.n;++i) 
		for(int j=0;j<a.n;++j)
			for(int k=0;k<a.n;++k) 
				if((res.a[i][j] += modmul(a.a[i][k],b.a[k][j],mod))>=mod) res.a[i][j] -= mod;
	return res;
}

Matrix pow(Matrix a,int b) {Matrix res; res.init(); res.n = a.n;for(;b;b>>=1,a=a*a)if(b&1) res=res*a;return res;}

int prime[M], cnt;
bool isp[M];

inline void init(int Max) {
	bool *F = isp;
	F[1] = 1;
	for(int i=2;i<=Max;++i) {
		if(!F[i]) prime[++cnt] = i;
		for(int j=1;prime[j]*i<=Max;++j) {
			F[i*prime[j]] = 1;
			if(i%prime[j]==0) break;
		}
	}
}

int F[N];

int main() {
	int n, m, p;
	cin >> n >> m >> p;
	init(m);
	a.n = p;
	for(int i=1;i<=m;++i) F[i%p] ++;
	for(int i=0;i<p;++i) for(int j=0;j<p;++j) a.a[i][(i+j)%p] = F[j]%mod;
	a = pow(a, n); 
 	int ans1 = a.a[0][0];
	memset(a.a,0,sizeof a.a);
	memset(F,0,sizeof F);
	for(int i=1;i<=m;++i)if(isp[i]) F[i%p] ++;
	for(int i=0;i<p;++i) for(int j=0;j<p;++j) a.a[i][(i+j)%p] = F[j] % mod;
	a = pow(a,n);
	int ans2 = a.a[0][0];
	cout << (ans1 - ans2 + mod) % mod << endl;
}
