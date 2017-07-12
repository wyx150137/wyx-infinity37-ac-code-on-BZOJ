
#include <vector>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int mod = 10007;
const int Maxm = 256+5;
const int N = 3e4+5;
const int M = 70000+5;

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int head[N];

struct graph {
	int next, to;
	graph () {}
	graph (int _next,int _to)
	:next(_next), to(_to) {}
}edge[M];

inline void add(int x,int y) {
	static int cnt = 0;
	edge[++cnt] = graph(head[x], y); head[x] = cnt;
	edge[++cnt] = graph(head[y], x); head[y] = cnt;
}

int root[N], ls[M], rs[M], Par[M], inv[N], size[N], fa[N], depth[N], has[N];
int sum[M][Maxm], vall[M][Maxm], valr[M][Maxm], val[M][Maxm], top[N], w[N], K;

vector <int> V[N];

inline void DFS1(int x) {
	size[x] = 1;
	for(int i=head[x];i;i=edge[i].next) {
		if(edge[i].to != fa[x]) {
			fa[edge[i].to] = x;
			depth[edge[i].to] = depth[x] + 1;
			DFS1(edge[i].to);
			size[x] += size[edge[i].to];
		}
	}
}

inline void DFS2(int x,int chain) {
	static int cnt = 0;
	w[x] = ++ cnt; top[x] = chain; int k = 0;
	V[chain].push_back(x);
	for(int i=head[x];i;i=edge[i].next) {
		if(edge[i].to != fa[x] && size[k] < size[edge[i].to]) {
			k = edge[i].to;
		}
	}
	if(!k) return;
	DFS2(k,chain);
	for(int i=head[x];i;i=edge[i].next) {
		if(edge[i].to != fa[x] && edge[i].to != k) {
			DFS2(edge[i].to, edge[i].to);
		}
	}
}

struct data {
	int x, y;
	data () {}
	data (int _x) {
		if(_x) x = _x, y = 0;
		else x = 1, y = 1;
	}
	inline void operator *= (int _x) {
		if(_x == 0) y ++;
		else x = x * _x % mod;
	}

	inline void operator /= (int _x) {
		if(_x == 0) y --;
		else x = x * inv[_x] % mod;
	}

	inline int val() {
		if(y) return 0;
		return x;
	}
} temp[N][Maxm];

inline void updata(int k) {
	int L = ls[k], R = rs[k];
	for(int i=0;i<K;++i) {
		val[k][i] = (val[L][i] + val[R][i] + valr[L][i]*vall[R][i]%mod) % mod;
		vall[k][i] = (vall[L][i] + sum[L][i]*vall[R][i] % mod) % mod;
		valr[k][i] = (valr[R][i] + sum[R][i]*valr[L][i] % mod) % mod;
		sum[k][i] = (sum[L][i] * sum[R][i]) % mod;
	}
} 

int sz;

inline void build(int &k,int l,int r,int bl) {
	k = ++ sz;
	if(l==r) {
		int tt = V[bl][l-1];
		has[tt] = k;
		for(int i=0;i<K;++i) {
			val[k][i] = vall[k][i] = valr[k][i] = sum[k][i] = temp[tt][i].val();
		}
		return;
	}
	int mid = (l+r) >> 1;
	build(ls[k], l, mid, bl);
	build(rs[k], mid+1, r, bl);
	updata(k);
	Par[ls[k]] = Par[rs[k]] = k;
}

int table[Maxm][Maxm], ans[Maxm];

inline void change(int x) {
	int tt = top[x];
	if(fa[tt]) {
		for(int i=0;i<K;++i) 
			temp[fa[tt]][i] /= (vall[root[tt]][i]+table[0][i])%mod;
	}
	for(int i=0;i<K;++i) 
		ans[i] = (ans[i] + mod - val[root[tt]][i]) % mod;
	int pos = has[x];
	for(int i=0;i<K;++i) 
		vall[pos][i] = valr[pos][i] = val[pos][i] = sum[pos][i] = temp[x][i].val();
	pos = Par[pos];
	while(pos) {
		updata(pos);
		pos = Par[pos];
	}
	if(fa[tt]) {
		for(int i=0;i<K;++i) 
			temp[fa[tt]][i] *= (vall[root[tt]][i]+table[0][i]) % mod;
	}
	for(int i=0;i<K;++i) 
		ans[i] = (ans[i] + val[root[tt]][i]) % mod;
}

void FWT(int *a,int n = K) {
    for(int d=1;d<n;d<<=1)
        for(int m=d<<1,i=0;i<n;i+=m)
            for(int j=0;j<d;j++) {
                int x=a[i+j],y=a[i+j+d];
                a[i+j]=(x+y)%mod,a[i+j+d]=(x-y+mod)%mod;
            }
}

void iFWT(int *a,int n = K) {
    for(int d=1;d<n;d<<=1)
        for(int m=d<<1,i=0;i<n;i+=m)
            for(int j=0;j<d;j++) {
                int x=a[i+j],y=a[i+j+d];
                a[i+j]=1LL*(x+y)*inv[2]%mod,a[i+j+d]=(1LL*(x-y)*inv[2]%mod+mod)%mod;
            }
}


inline void init() {
	inv[1] = 1;
	for(int i=2;i<mod;++i) inv[i] = mod - mod/i*inv[mod%i]%mod;
	for(int i=0;i<K;++i) table[i][i] = 1;
	for(int i=0;i<K;++i) FWT(table[i]);
}

int Val[N];

int stack[N], all;

bool cmp(int x,int y) {
	return depth[x] > depth[y];
}

int tempans[Maxm];

int main() {
	int n = read(), k = read();
	K = k;
	init();
	for(int i=1;i<=n;++i) {
		Val[i] = read();
		for(int j=0;j<K;++j) 
			temp[i][j] = data(table[Val[i]][j]);
	}
	for(int i=2;i<=n;++i) {
		int x = read(), y = read();
		add(x, y); 
	}
	DFS1(1);
	DFS2(1,1);
	for(int i=1;i<=n;++i) if(top[i] == i) stack[++all] = i;
	sort(stack+1,stack+all+1,cmp);
	
	for(int i=1;i<=all;++i) {
		build(root[stack[i]], 1, V[stack[i]].size(), stack[i]);
		int x = stack[i];
		if(fa[x])
			for(int j=0;j<K;++j) {
				temp[fa[x]][j] *= (vall[root[x]][j] + table[0][j]) % mod;
			}
		for(int j=0;j<K;++j) ans[j] = (ans[j] + val[root[x]][j]) % mod;
	} 
	
	int Q = read();
	char str[10];
	while(Q--) {
		scanf("%s", str);
		if(str[0] == 'Q') {
			int y = read();
			for(int i=0;i<K;++i) tempans[i] = ans[i];
			iFWT(tempans);
			printf("%d\n", tempans[y]);
		}
		else {
			int x = read(), y = read();
			for(int i=0;i<K;++i) 
				temp[x][i] /= table[Val[x]][i];
			Val[x] = y;
			for(int i=0;i<K;++i) 
				temp[x][i] *= table[Val[x]][i];
			
			while(x) {
				change(x);
				x = fa[top[x]];
			}
			
		}
	}
}
