
#include <bits/stdc++.h>
using namespace std;
const int Maxn = 1e7 + 5;
int p[Maxn*2];
int seed, N, K, S;

int randint(){seed = ((seed * 12321) ^ 9999) & 32767;return seed;}
void input(){scanf("%d%d%d", &K, &seed, &S); int t = 0; N = K * 2 + 1; for(int i = 1;i <= N; ++i){p[i] = (randint() >> 7) & 1; t += p[i];}int i = 1; while(t > K){while(!p[i]) i++;p[i] = 0; t--;} while(t < K){while(p[i]) i++;p[i] = 1; t++;}}

int cnt[Maxn<<1], ans[3];

void solve() {

	for(int i=1;i<=N;++i) p[i] = p[i] ? -1 : 1;
	for(int i=2, sum=0;i<=N;++i) {
		sum += p[i];
		if(p[i] < 0) cnt[sum + Maxn] ++; 
	}
	int all = 0, temp = Maxn - 1;
	for(int i=0;i<=temp;++i) all += cnt[i];
	for(int i=1;i<=N;++i) {
		if(p[i] > 0) {
			if(all == 0) ans[0] = i;
			if(all == S) ans[1] = i;
			if(all == K - S) ans[2] = i;
		}
		if(p[i+1] < 0) {
			-- cnt[temp];
			-- all;
		} 
		if(p[i] < 0) ++ cnt[temp + 2];
		if(p[i+1] < 0) all -= cnt[temp], temp --;
		else ++temp, all += cnt[temp];
	}
	for(int i=0;i<3;++i) cout << ans[i] << endl;
}

int main() {
	input();
	solve();
}
