
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 2000+5;
const int M = N * N / 2;
typedef long long LL;
int n;

struct data{
	int from,to,val;
	bool operator < (const data &z)const{
		return val < z.val;
	}
}edge[M];

int fa[N];

inline int find(int x) {
	return fa[x] ^ x ? fa[x] = find(fa[x]) : fa[x];
}

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9') {if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9') {x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int main() {
	int n = read(), tot = 0;
	register int i,j;
	for(i=1;i<=n;++i)
		for(j=i;j<=n;++j) 
			edge[++tot].from = i, edge[tot].to = j+1, edge[tot].val = read();
	sort(edge+1,edge+tot+1);
	LL ans = 0;
	for(int i=1;i<=n+1;++i) fa[i] = i;
	for(int i=1;i<=tot;++i) {
		if(find(edge[i].from) != find(edge[i].to)) {
			fa[find(edge[i].to)] = find(edge[i].from);
			ans += edge[i].val;
		}
	}
	cout << ans << endl;		
}
