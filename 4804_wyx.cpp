
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1e7+5;
const int Max = 1e7;
typedef long long LL;

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int prime[N], cnt;
LL phi[N];
bool F[N];

inline void init() {
	phi[1] = 1;
	register int j;
	int temp;
	for(int i=2;i<=Max;++i) {
		if(!F[i]) {
			prime[++cnt] = i;
			phi[i] = i-1;
		}
		for(j=1;prime[j]*i<=Max;++j) {
			F[temp = (i*prime[j])] = true;
			if(i%prime[j]==0) {
				phi[temp] = phi[i] * prime[j];
				break;
			}
			phi[temp] = phi[i] * (prime[j]-1);
		}
	}
	for(int i=2;i<=Max;++i) phi[i] += phi[i-1];
}

int main() {
	init();
	int T = read(), n ;
	LL ans;
	while(T--) {
		n = read();
		ans = 0;
		for(int i=1,last=0;i<=n;i=last+1) {
			last = n/(n/i);
			ans += (phi[last]-phi[i-1])*(phi[n/i]*2-1);
		}
		printf("%lld\n", ans);
	}
}
