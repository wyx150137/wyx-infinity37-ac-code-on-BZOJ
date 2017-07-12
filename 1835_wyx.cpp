
#include <vector>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
#define pb push_back
typedef long long LL;
const int N = 1e5+5;
const int M = N << 2;
const int inf = 1e9;

LL read() {
	LL x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int n, K;
LL F[N], d[N], c[N], s[N], w[N];
int st[N], ed[N];

vector <LL> ep[N];
LL tr[M],lazy[M];
#define updata(k) tr[k] = min(tr[k<<1],tr[k<<1|1]) 

inline void build(int k,int l,int r) {
	if(l==r) {
		tr[k] = F[l];
		return;
	}
	lazy[k] = 0;
	tr[k] = inf;
	int mid = (l+r) >> 1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
	updata(k);
}

inline void down(int k,int l,int r) {
	if(!lazy[k] || l == r) return;
	LL tt = lazy[k]; lazy[k] = 0; 
	lazy[k<<1] += tt; lazy[k<<1|1] += tt;
	tr[k<<1] += tt, tr[k<<1|1] += tt;
}

inline void change(int k,int l,int r,int x,int y,LL val) {
	if(x>y)return;
	if(l==x && r==y) {
		tr[k] += val;
		lazy[k] += val;
		return;
	}
	down(k,l,r);
	int mid = (l+r) >> 1;
	if(y <= mid) change(k<<1,l,mid,x,y,val);
	else if(x > mid) change(k<<1|1,mid+1,r,x,y,val);
	else change(k<<1,l,mid,x,mid,val), change(k<<1|1,mid+1,r,mid+1,y,val);
	tr[k] = min(tr[k<<1],tr[k<<1|1]);
}

LL ask(int k,int l,int r,int x,int y) {
	if(x > y) return 0;
	if(l==x&& r==y) return tr[k];
	int mid = (l+r) >> 1;
	down(k,l,r);
	if(y <= mid)return ask(k<<1,l,mid,x,y);
	else if(x > mid)return ask(k<<1|1,mid+1,r,x,y);
	else return min(ask(k<<1,l,mid,x,mid),ask(k<<1|1,mid+1,r,mid+1,y));
}

int main() {
	n = read(), K = read();
	for(int i=2;i<=n;++i) d[i] = read();
	for(int i=1;i<=n;++i) c[i] = read();
	for(int i=1;i<=n;++i) s[i] = read();
	for(int i=1;i<=n;++i) w[i] = read();
	n ++, K ++; d[n] = inf, w[n] = inf;
	for(int i=1;i<=n;++i) {
		int l = d[i] - s[i], r = d[i] + s[i];
		l = lower_bound(d+1,d+n+1,l)-d;
		r = lower_bound(d+1,d+n+1,r)-d;
		if(d[i] + s[i] < d[r])  r--;
		st[i] = l, ed[i] = r;
		ep[ed[i]].pb(i);
	}
	LL ans , tmp = 0;
	vector <LL> :: iterator it;
	for(int i=1;i<=n;++i) {
		F[i] = tmp + c[i];
		for(it = ep[i].begin(); it != ep[i].end(); ++it) tmp += w[*it];
	}
	ans = F[n];
	for(int j=2;j<=K;++j) {
		build(1,1,n);
		for(int i=1;i<=n;++i) {
			F[i] = ask(1,1,n,1,i-1) + c[i];
			for(it = ep[i].begin(); it != ep[i].end(); ++it) change(1,1,n,1,st[(*it)]-1,w[(*it)]);
		}
		ans = min(ans,F[n]);
	}
	cout << ans << endl;
}
