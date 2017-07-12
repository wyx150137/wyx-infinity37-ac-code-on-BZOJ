
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 1e7+5;
using namespace std;

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int prime[N], cnt, mu[N], q[N], from[N], tot;
bool f[N];

inline void init(int Max) {
	mu[1] = 1;
	bool *F = f;
	for(int i=2;i<=Max;++i) {
		if(!F[i]) {
			prime[++cnt] = i;
			mu[i] = -1;
			from[i] = i;
		}
		for(int j=1;prime[j]*i<=Max;++j) {
			F[prime[j]*i] = 1;
			if(i%prime[j]==0) break;
			from[i*prime[j]] = prime[j];
			mu[i*prime[j]] = -mu[i];
		}
	}
}

int F[N], A, B, p[26];

inline void DFS(int x,int y) {
	if(x == tot) {
		F[y] += A;
		if(mu[y] > 0) B += F[y];
		else B -= F[y];
		return;
	}
	DFS(x+1, y*p[x]);
	DFS(x+1, y);
}

int s[N];

int main() {
	int T = read();
	int Max = 0;
	for(int i=1;i<=T;++i) {
		q[i] = read();
		Max = max(Max, q[i]);
	}
	init(Max);
	int j;
	for(int i=1;i<=Max;++i) {
		s[i] = s[i-1];
		if(mu[i]) {
			for(tot = 0, j = i; j > 1; j /= from[j]) p[tot ++] = from[j];
			A = mu[i];
			B = 0;
			DFS(0, 1);
			s[i] += mu[i] * B;
		}
	}
	for(int i=1;i<=T;++i) printf("%d\n", s[q[i]]);
}
