
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 1e5+5;
const int inf = 2e9+1;
typedef long long LL;
using namespace std;

bool F[N];
int mu[N],prime[N],cnt;

void init(){
	mu[1] = 1;
	register int i,j;
	for(i=2;i<N;++i){
		if(!F[i]) prime[++cnt] = i, mu[i] = -1;
		for(j=1;prime[j]*i<N;++j){
			F[i*prime[j]]=1;
			if(i%prime[j] == 0) break;
			mu[i*prime[j]] = -mu[i];
		}
	}
}

inline int calc(int x){
	int ans = 0;
	for(int i=1;i*i<=x;++i)
		ans += mu[i]*x/(i*i);
	return ans;
}

int main(){ init();
	int T;cin >> T; while(T--){
		LL l = 1, r = inf;
		int k; cin >> k;
		while(l < r){
			int mid = (l+r)>>1;
			if(calc(mid) >= k) r = mid;
			else l = mid + 1;
		}
		cout << l << endl;
	}
}
