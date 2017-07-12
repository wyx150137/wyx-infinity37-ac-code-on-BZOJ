
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1e5+5;
const int Max = 1e5;
typedef long long LL;
LL n, prime[N], ans[N], tot, cnt;
bool F[N];

inline void init() {
	register int j; int i;
	for(i=2;i<=Max;++i) {
		if(!F[i]) prime[++cnt] = i;
		for(j=1;prime[j]*i<=Max;++j) {
			F[i*prime[j]] = 1;
			if(i%prime[j] == 0) break;
		}
	}
}

inline bool check(LL x) {
	if(x == 1) return false;
	for(int i=1;prime[i]*prime[i]<=x;++i) if(x%prime[i]==0) return false;
	return true;
}

void DFS(LL x,int pos,LL left) {
	if(left == 1) {
		ans[++ans[0]] = x;
		return;
	}
	if(left-1>=prime[pos] && check(left-1))  ans[++ans[0]] = (left-1)*x;
	for(int i=pos;prime[i]*prime[i]<=left;++i) {
		LL tmp1 = prime[i] + 1;
		LL tmp2 = prime[i];
		for(;tmp1<=left;tmp2*=prime[i],tmp1+=tmp2)  if(left%tmp1==0)  DFS(x*tmp2,i+1,left/tmp1);
	}
}

int main() {
	init();
	while(~scanf("%lld",&n)) {
		ans[0] = 0;
		DFS(1,1,n);
		sort(ans+1,ans+ans[0]+1);
		cout << ans[0] << endl;
		for(int i=1;i<=ans[0];++i)  
			printf("%lld%c",ans[i],i == ans[0]?'\n':' ');
	}
}
