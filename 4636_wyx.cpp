
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
typedef long long LL;
using namespace std;
const int N = (4e4+5)*15;
const int M = N << 2;
const int inf = 1e9;
int tr[M], ls[M], rs[M], sz;

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

inline void change(int &k,int l,int r,int x,int y,int val) {
	if(!k) k = ++sz; 
	if(x <= l && r <= y) {
		tr[k] = max(tr[k], val);
		return;
	}
	int mid = (l+r) >> 1;
	if(x <= mid) change(ls[k], l, mid, x, y, val);
	if(y > mid) change(rs[k], mid+1, r, x, y, val); 
}

LL ans;

inline void get(int k,int l,int r,int val) {
	if(!k) return;
	tr[k] = max(tr[k], val);
	int mid = (l+r) >> 1;
	if(ls[k]) get(ls[k],l,mid,tr[k]); 
	else ans += (LL)(mid-l+1) * tr[k];
	if(rs[k]) get(rs[k],mid+1,r,tr[k]); 
	else ans += (LL)(r-mid) * tr[k];
}

int root;

int main() {
	int n = read();
	for(int i=1;i<=n;++i) {
		int a = read(), b = read() - 1, lmt = read();
		if(a <= b) change(root,1,inf,a,b,lmt);
	}
	get(root,1,inf,0);
	cout << ans << endl;
}
