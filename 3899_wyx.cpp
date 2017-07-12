
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = 2e3+5;
const int M = N << 3;
const int mod = 1000000003;

int n, m, fac[N] = {1}, head[N];

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9') {if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9') {x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

struct graph {
	int next,to,flag;
	graph () {}
	graph (int _next,int _to)
	:next(_next),to(_to){}
}edge[M];

inline void add(int x,int y) { static int cnt = 1;edge[++cnt] = graph(head[x],y); head[x] = cnt;}
int fa[N], cnt, size[N], from[N], vis[N];

void DFS1(int x,int F) {
	vis[x] = 1; fa[x] = F;
	for(int i=head[x];i;i=edge[i].next) {
		if(edge[i].to != F) {
			if(vis[edge[i].to]) {
				if(from[edge[i].to]) continue;
				size[++cnt] = 1;
				from[edge[i].to] = cnt;
				fa[edge[i].to] = x;
				for(int y = x; y != edge[i].to; y = fa[y]) size[cnt] ++, from[y] = cnt;
			}
			else DFS1(edge[i].to,x);
		}
	}
}

LL f[N], num[N], stack[N], T[N];

void calc(int x,int dep){
    f[x] = num[x] = 1;
	for(int i=head[x];i;i=edge[i].next) {
		if(edge[i].flag == 0) {
			if(from[edge[i].to] != from[x]) {
				edge[i].flag = edge[i^1].flag = 1;
				calc(edge[i].to,dep+1);
				f[x] = (LL) f[x] * f[edge[i].to] % mod;
				edge[i].flag = edge[i^1].flag = 0;
			}
		}
	}
   
    int top = 0, sum = 1;
	if(vis[from[x]] != 2 && size[from[x]] != 1) {
		vis[from[x]] = 2;
		for(int y = fa[x]; y != x; y = fa[y]) 
		calc(y,dep+1), f[x] = (LL)f[x] * f[y] % mod;
		for(int y = fa[x]; y != x; y = fa[y]) stack[++top] = y;
		for(int i=1,j=top;i<=j;i++,j--) if(num[stack[i]] != num[stack[j]]) sum = 0;
		if(sum) f[x] = (LL)f[x] *2 % mod;
		vis[from[x]] = 0;
	}
	int t = 0,last = 1;
	for(int i=head[x];i;i=edge[i].next) if(from[edge[i].to] != from[x]) T[++t] = num[edge[i].to];
	sort(T+1,T+t+1);
	for(int i=2;i<=t;++i) if(T[i] == T[i-1]) last ++; else f[x] = (LL)f[x] * fac[last] % mod, last = 1;
	f[x] = (LL) f[x] * fac[last] % mod;
	for(int i=1;i<=top;++i) T[++t] = num[stack[i]] * (233+size[from[x]]) + min(i,top-i+1);
	sort(T+1,T+t+1);
	for(int i=1;i<=t;++i) num[x] = num[x] * 131 + T[i];
	num[x] = num[x] * dep;
} 

int main() {// freopen("tmp1.in","r",stdin);freopen("tmp1.out","w",stdout);
	n = read(), m = read();
	for(int i=1;i<=n;++i) fac[i] = (LL) fac[i-1] * i % mod;
	for(int i=1;i<=m;++i) {
		int x = read(), y = read();
		add(x,y); add(y,x);
	}
	DFS1(1,0);
	for(int i=1;i<=n;++i) if(!from[i]) from[i] = ++ cnt, size[cnt] = 1;
	calc(1,1);
	LL ans = f[1], same = num[1], cnt0 = 1;
	for(int i=2;i<=n;++i) {
		memset(num,0,sizeof num);
		calc(i,1);
		if(same == num[i]) cnt0 ++;
	}
	cout << (LL) ans * cnt0 % mod << endl;
}
