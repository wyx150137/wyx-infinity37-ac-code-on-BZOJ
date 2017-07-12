
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5+5;
int fa[N], depth[N], sz;
map <int,int> son[N];

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

inline int newnode(int _) {
	depth[++sz] = _;
	return sz;
}

long long ans;
int p, np, q, nq, root, last;

inline int calc(int x) {
	return depth[x] - depth[fa[x]];
}

inline void insert(int x) {
	p = last; np = last = newnode(depth[p]+1);
	while(p && !son[p][x]) {
		son[p][x] = np;
		p = fa[p];
	}
	if(!p) {
		fa[np] = root; 
		ans += calc(np);
	}
	else {
		q = son[p][x];
		if(depth[q] == depth[p]+1) {
			fa[np] = q;
			ans += calc(np);
		}
		else {
			nq = newnode(depth[p]+1);
			son[nq] = son[q];
			fa[nq] = fa[q];  ans += calc(nq) - calc(q);
			fa[q] = fa[np] = nq; ans += calc(q) + calc(np);
			while(p && son[p][x] == q) {
				son[p][x] = nq;
				p = fa[p];
			}
		}
	}
}

int main() {
	root = last = newnode(0);
	int n = read();
	for(int i=1;i<=n;++i) {
		int temp = read();
		insert(temp);
		printf("%lld\n", ans);
	}
}
