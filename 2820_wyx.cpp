
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 1e7;
typedef long long LL;
using namespace std;

LL mu[N+5],F[N+5],g[N+5],prime[N],cnt;

void init(){
	mu[1] = 1;
	register int i,j;
	for(i=2;i<=N;++i){
		if(!F[i]){
			prime[++cnt] = i;
			mu[i] = -1;
		}
		for(j=1;prime[j]*i<=N;++j){
			F[prime[j]*i] = 1;
			if(i%prime[j] == 0) break;
			mu[i*prime[j]] = -mu[i];
		}
	}
	for(i=1;i<=cnt;++i)
		for(j=1;prime[i]*j<=N;++j)
			g[prime[i]*j] += mu[j];
	for(i=1;i<=N;++i)
		g[i] += g[i-1];
}

inline LL calc(LL x,LL y){
	int last = 1;
	LL ans = 0;
	register int i;
	for(i=1;i<=x&&i<=y;i=last+1){
		last = min(x/(x/i),y/(y/i));
		ans += (x/i)*(y/i)*(g[last]-g[i-1]);
	}
	return ans;
}

inline int read(){
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int main(){
	init();
	int T = read();
	for(int i=1;i<=T;++i){
		int x = read(), y = read();
		printf("%lld\n",calc(x,y));
	}
}
