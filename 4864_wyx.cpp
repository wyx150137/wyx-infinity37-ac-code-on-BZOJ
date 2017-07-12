
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;
const int N = 2e5+5;
const int inf = 0x3f3f3f3f;
inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1; ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int sz, fa[N];
int ch[N][2], val[N], Min[N], Max[N], ans[N], size[N], root, a[N], val2[N];

inline void updata(int k) {
	size[k] = 1;
	Min[k] = Max[k] = val[k];
	ans[k] = val2[k];
	if(ch[k][0]) {
		int p = ch[k][0];
		Min[k] = min(Min[k], Min[p]);
		Max[k] = max(Max[k], Max[p]);
		ans[k] = min(ans[k], ans[p]);
		size[k] += size[p];
	}
	if(ch[k][1]) {
		int p = ch[k][1];
		Min[k] = min(Min[k], Min[p]);
		Max[k] = max(Max[k], Max[p]);
		ans[k] = min(ans[k], ans[p]);
		size[k] += size[p];
	}
}

inline void rotate(int x) {
	int y = fa[x], z = (ch[y][1] == x);
	ch[y][z] = ch[x][!z], fa[ch[y][z]] = y;
	ch[x][!z] = y; fa[x] = fa[y]; fa[y] = x;
	ch[fa[x]][ch[fa[x]][1] == y] = x;
	updata(y); updata(x);
}

inline void splay(int x,int w) {
	while(fa[x] != w) {
		int y = fa[x], z = fa[y];
		if(z == w) rotate(x);
		else if((ch[y][1] == x) == (ch[z][1] == y)) rotate(y), rotate(x);
		else rotate(x), rotate(x);
	}
	if(!w) root = x;
}

inline int find(int x,int kth) {
	int tmp = size[ch[x][0]];
	if(tmp >= kth) return find(ch[x][0], kth);
	else if(tmp+1 == kth) return x;
	else return find(ch[x][1], kth-tmp-1);
}

inline void newnode(int &k,int V,int F) {
	k = ++sz;
	size[k] = 1;
	val[k] = Min[k] = Max[k] = V;
	fa[k] = F;
}

inline void build(int &k,int L,int R,int F) {
	if(L > R) return;
	int mid = (L+R) >> 1;
	newnode(k, a[mid], F);
	val2[k] = ans[k] = abs(a[mid] - a[mid-1]);
	build(ch[k][0], L, mid-1, k);
	build(ch[k][1], mid+1, R, k);
	updata(k);
} 

char str[10];

int main() {
//f	freopen("tt.in","r",stdin);
	int n = read(), m = read();
	for(int i=1;i<=n;++i) a[i] = read();
	newnode(root, inf, 0);
	newnode(ch[root][1], inf, root);
	int tmp = ch[root][1];
	build(ch[tmp][0], 1, n, tmp);
	updata(tmp);
	updata(root);
	for(int i=1;i<=m;++i) {
		scanf("%s",str+1);
		if(str[1] == 'i') {
			int x = read(), val = read();
			splay(find(root, x+1), 0);
			splay(find(root, x+2), root);
			int tmp = ch[root][1];
			newnode(ch[tmp][0], val, tmp);
			val2[ch[tmp][0]] = ans[ch[tmp][0]] = abs(val - ::val[root]);
			val2[ch[root][1]] = ans[ch[root][1]] = abs(::val[ch[root][1]] - val);
			updata(ch[root][1]);
			updata(root);
		}
		else if(str[2] == 'e') {
			int x = read(), val = read();
			splay(find(root,x), 0);
			splay(find(root,x+3), root);
			int tmp = ch[root][1];
			newnode(ch[tmp][0], val, tmp);
			val2[ch[tmp][0]] = ans[ch[tmp][0]] = abs(val - ::val[root]);
			val2[ch[root][1]] = ans[ch[root][1]] = abs(::val[ch[root][1]] - val);
			updata(ch[root][1]);
			updata(root);
		}
		else if(str[2] == 'a') {
			int x = read(), y = read();
			splay(find(root,x),0);
			splay(find(root,y+2), root);
			int tmp = ch[root][1];
			tmp = ch[tmp][0];
			printf("%d\n", Max[tmp]-Min[tmp]);
		}
		else {
			int x = read(), y = read();
			splay(find(root, x+1), 0);
			splay(find(root, y+2), root);
			int tmp = ch[root][1]; tmp = ch[tmp][0];
			printf("%d\n", ans[tmp]);
		}
	}
}
