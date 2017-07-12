
#include <bits/stdc++.h>
using namespace std;
#define lowbit(x) ((x)&(-x))
const int N = 32768+5;
const int M = 32768+5;
const int mod = 1e9+7;
inline int calc(int x) {
	int ans = 0;
	while(x) {
		ans ++;
		x -= lowbit(x);
	}
	return ans;
}

int F[2][M], nxt[M][4], ans[N], a[100+5];
int f[20], g[20], n;

inline void init() {
	const int Max = (1 << n)- 1;
	for(int i=0;i<=Max;++i) {
		memset(f,0,sizeof f);
		memset(g,0,sizeof g);
		for(int j=1;j<=n;++j) f[j] = f[j-1] + ((i>>j-1)&1);
		for(int k=0;k<4;++k) {
			for(int j=1;j<=n;++j) {
				g[j] = max(g[j-1], f[j]);
				if(a[j] == k) g[j] = max(g[j], f[j-1]+1);
			}
			nxt[i][k] = 0;
			for(int j=1;j<=n;++j) {
				if(g[j]-g[j-1]) 
					nxt[i][k] |= 1<<((j-1));
			}
		}
	}
}

char str[100];

int main() {
//	freopen("tt.in","r",stdin);
	int T; cin >> T;
	while(T--) {
		scanf("%s", str+1);
		n = strlen(str+1);
		for(int j=1;j<=n;++j) {
			if(str[j] == 'A') a[j] = 0;
			else if(str[j] == 'T') a[j] = 1;
			else if(str[j] == 'G') a[j] = 2;
			else a[j] = 3;
		}
		init();
		int m; cin >> m;
		memset(F[0], 0, sizeof F[0]);
		memset(ans, 0, sizeof ans);
		F[0][0] = 1;  
		int Max = (1<<n) - 1;
		for(int i=1;i<=m;++i) {
			int o = i & 1, op = (i+1) & 1;
			memset(F[o], 0, sizeof F[o]);
			for(int j=0;j<=Max;++j) 
				for(int k=0;k<4;++k) {
					(F[o][nxt[j][k]] += F[op][j]) %= mod;
				}
		}
		for(int j=0;j<=Max;++j) 
			(ans[calc(j)] += F[m&1][j]) %= mod;
		for(int j=0;j<=n;++j) cout << ans[j] << '\n' ;
	}
}
