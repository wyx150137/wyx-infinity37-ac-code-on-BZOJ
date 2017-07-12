
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 200+5;
const int mod = 9999973;
typedef long long LL;
int F[N][N][N];

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9') {if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9') {x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int C[N][N];

inline void init() {
	for(int i=0;i<=200;++i) {
		C[i][0] = 1;
		for(int j=1;j<=i;++j) {
			C[i][j] = C[i-1][j] + C[i-1][j-1];
			if(C[i][j] > mod) C[i][j] -= mod;
		}
	}
}

const int I2 = 4999987;

int main() {
	init();
	int n = read(), m = read();
	F[0][m][0] = 1;
	for(int i=0;i<n;++i) {
		for(int j=0;j<=m;++j) {
			for(int k=0;k<=m;++k) {
				(F[i+1][j][k] += F[i][j][k]) %= mod;
				if(j>=1)(F[i+1][j-1][k+1] += (LL)F[i][j][k] * j % mod) %= mod;
				if(k>=1)(F[i+1][j][k-1] += (LL)F[i][j][k] * k % mod) %= mod;
				if(j>=2)(F[i+1][j-2][k+2] += (LL) F[i][j][k]*j%mod*(j-1)%mod*I2 % mod) %= mod;
				if(j>=1)(F[i+1][j-1][k] += (LL) F[i][j][k] * j % mod * k % mod) %= mod;
				if(k>=2)(F[i+1][j][k-2] += (LL) F[i][j][k] * C[k][2] % mod) %= mod;
			}
		}
	}
	LL ans = 0;
	for(int i=0;i<=m;++i) {
		for(int j=0;j<=m;++j) {
			(ans += F[n][i][j]) %= mod;
		}
	}
	cout << ans << endl;
}
