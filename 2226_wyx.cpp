
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1e6+5;
const int Max = 1e6;
typedef long long LL;
int phi[N],prime[N],cnt;
bool F[N];

void init() {
	register int j; int i;
	phi[1] = 1;
	for(i=2;i<=Max;++i) {
		if(!F[i]) prime[++cnt] = i, phi[i] = i - 1;
		for(j=1;prime[j]*i<=Max;++j) {
			F[prime[j]*i] = 1;
			if(i % prime[j] == 0) {
				phi[i*prime[j]] = phi[i] * prime[j];
				break;
			}		
			phi[prime[j]*i] = phi[i] * (prime[j]-1);
		}
	}
}

inline LL calc(int x) {
	if(x == 1)  return 1ll;
	return (LL) x * phi[x] >> 1;
}

LL solve(int x) {
	int i; LL ans = 0;
	for(i=1;i*i<x;++i)  if(x%i==0) ans += calc(i), ans += calc(x/i);
	if(i*i==x) ans += calc(i); return ans;
}

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int main() {
	int n, q = read(); init();
	while(q--) {
		n = read();
		printf("%lld\n",solve(n)*n);
	}
}
