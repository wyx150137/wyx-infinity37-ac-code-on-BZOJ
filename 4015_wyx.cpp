
#include <vector>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 200+5;
const int mod = 10007;
const int inf = 0x3f3f3f3f;

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0'; ch = getchar();}
	return x*f;
}

vector <int> V[N];
int size[N], root[N], cnt, fa[N], F[N], n, rt, g[N][N][N];

void DFS(int x) {
	size[x] = 1; F[x] = 0;
	for(int i=0;i<V[x].size();++i){
		if(V[x][i] != fa[x]) {
			fa[V[x][i]] = x;
			DFS(V[x][i]);
			size[x] += size[V[x][i]];
			F[x] = max(F[x], size[V[x][i]]);
		}
	}
	F[x] = max(F[x], n - size[x]);
	if(F[x] < F[rt]) 
		rt = root[cnt = 1] = x;
	else if(F[x] == F[rt]) 
		root[++cnt] = x;
}

int f[N][N];

void DFS2(int x) {
	size[x] = 1;
	f[x][1] = 1;
	f[x][0] = 1;
	for(int i = 0; i < V[x].size(); ++ i) {
		if(V[x][i] != fa[x]) {
			fa[V[x][i]] = x;
			DFS2(V[x][i]);
			size[x] += size[V[x][i]];
			for(int j = size[x]; j; -- j) {
				int sum = 0;
				for(int k = 0; k < j; ++ k) {
					(sum += f[x][j-k] * f[V[x][i]][k] % mod) %= mod;
				}
				f[x][j] = sum;
			}
		}
	}
}

bool cmp1(int x,int y) {
	return size[x] < size[y];
}

int main() {
	int Q = read();
	for(int testcases = 1; testcases <= Q; ++testcases) {
		n = read();
		for(int i=2;i<=n;++i) {
			int x = read(), y = read();
			V[x].push_back(y);
			V[y].push_back(x);
		}
		cnt = rt = 0;
		F[rt] = inf;
		memset(fa, 0, sizeof fa);
		DFS(1);
		if(cnt == 2) {
			int x = root[1], y = root[2];
			rt = ++ n;
			V[x].erase(find(V[x].begin(), V[x].end(), y));
			V[y].erase(find(V[y].begin(), V[y].end(), x));
			V[x].push_back(rt); V[rt].push_back(x);
			V[y].push_back(rt); V[rt].push_back(y);
		}
		memset(f, 0, sizeof f);
		memset(fa, 0, sizeof fa);
		DFS2(rt);
		sort(V[rt].begin(), V[rt].end(), cmp1);
		int all = V[rt].size(), sum = 1, last = 0;
		memset(g, 0, sizeof g);
		g[0][0][1] = 1;
		for(int i=1;i<=all;++i) {
			int to = V[rt][i-1]; sum += size[to];
			for(int j=0;j<=size[to];++j) 
				for(int k=0;k<=sum-size[to];++k) 
					for(int temp = 0; temp <= last; ++ temp) 
						(g[i][max(j,temp)][j+k] += g[i-1][temp][k]*f[to][j]%mod) %= mod;
			last = size[to];
		}
		int ans = 0;
		for(int i=0;i<=n;++i) 
			for(int j=i*2+1;j<=n;++j) 
				(ans += g[all][i][j]) %= mod;
		printf("Case %d: %d\n",testcases,ans + (cnt == 2 ? -1 : 0));
		for(int i=1;i<=n;++i) V[i].clear();
	}
}
