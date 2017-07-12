
#include <set>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
const LL N = 2e5+5;
const LL M = N << 2;
LL tr[M], lazy[M];

inline LL read() {
	LL x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

inline void down(LL k,LL l,LL r) {
	if(l==r||!lazy[k]) return;
	LL mid = (l+r) >> 1, tmp = lazy[k]; lazy[k] = 0;
	tr[k<<1] += (mid-l+1) * tmp;
	tr[k<<1|1] += (r-mid) * tmp;
	lazy[k<<1] += tmp;
	lazy[k<<1|1] += tmp;
	return;
}

inline void change(LL k,LL l,LL r,LL x,LL y,LL val) {
	if(l==x && r==y) {
		tr[k] += (r-l+1)*val;
		lazy[k] += val;
		return;
	}
	down(k,l,r);
	LL mid = (l+r) >> 1;
	if(y <= mid) change(k<<1,l,mid,x,y,val);
	else if(x > mid) change(k<<1|1,mid+1,r,x,y,val);
	else change(k<<1,l,mid,x,mid,val), change(k<<1|1,mid+1,r,mid+1,y,val);
	tr[k] = tr[k<<1] + tr[k<<1|1];
}

inline LL ask(LL k,LL l,LL r,LL x,LL y) {
	if(l==x && r==y) return tr[k];
	down(k,l,r);
	LL mid = (l+r) >> 1;
	if(y <= mid) return ask(k<<1,l,mid,x,y);
	else if(x > mid) return ask(k<<1|1,mid+1,r,x,y);
	else return ask(k<<1,l,mid,x,mid) + ask(k<<1|1,mid+1,r,mid+1,y);
}

struct line {
	LL x1,x2,y,val,opt,id;
	bool operator < (const line &z) const {
		if(y != z.y) return y < z.y;
		return opt < z.opt;
	}
} l[N<<4];

set <LL> s;

struct data {
	LL pos,val;
	bool operator < (const data &z) const {
		return val > z.val;
	}
} a[N];
    
LL L[N], R[N], X[N], Y[N], ans[N], top;

int main() {
//	freopen("tt.in","r",stdin);
	LL n = read(); LL m = read(), p1 = read(), p2 = read();
	for(LL i=1;i<=n;++i) a[i].pos = i, a[i].val = read();
	s.insert(0); s.insert(n+1);
	set <LL> :: iterator it;
	sort(a+1,a+n+1);
	for(LL i=1;i<=n;++i) {
		LL j=i+1;
		while(a[j].val == a[i].val) j ++; 
		j --;
		for(LL k=i;k<=j;++k) s.insert(a[k].pos);
		for(LL k=i;k<=j;++k) {
			it = s.upper_bound(a[k].pos); R[a[k].pos] = *it;
			it = --s.lower_bound(a[k].pos);L[a[k].pos] = *it;
		}
		for(LL k=i;k<=j;++k) {
			bool flag = false;
			if(L[a[k].pos] == 0 && R[a[k].pos] == n+1) continue;
			if(L[a[k].pos] == 0) flag = true;
			if(R[a[k].pos] == n+1) flag = true;
			if(!flag) l[++top] = (line){L[a[k].pos],L[a[k].pos], R[a[k].pos],p1,0,0};
			if(L[a[k].pos]+1<=a[k].pos-1 && R[a[k].pos] != n+1) l[++top] = (line){L[a[k].pos]+1, a[k].pos-1, R[a[k].pos], p2, 0, 0};
		}
	}
	for(LL i=1;i<=m;++i) X[i] = read(), Y[i] = read();
	for(LL i=1;i<=m;++i) {
		l[++top] = (line){X[i], Y[i], X[i]-1,0,1,i};
		l[++top] = (line){X[i], Y[i], Y[i] , 0,2,i};
	}
	for(LL i=1;i<n;++i) l[++top] = (line){i,i,i+1,p1,0,0};
	sort(l+1,l+top+1);
	for(LL i=1;i<=top;++i) {
		if(l[i].opt==0) change(1,0,n+1,l[i].x1,l[i].x2,l[i].val);
		else if(l[i].opt==1) ans[l[i].id] -= ask(1,0,n+1,l[i].x1,l[i].x2);
		else ans[l[i].id] += ask(1,0,n+1,l[i].x1,l[i].x2);
	}

	top = 0;
	memset(tr,0,sizeof tr);
	memset(lazy,0,sizeof lazy);
	for(LL i=1;i<=m;++i) {
		l[++top] = (line){X[i], Y[i],X[i]-1, 0, 1, i};
		l[++top] = (line){X[i], Y[i],  Y[i], 0, 2, i};
	}
	for(LL i=1;i<=n;++i) 
		if(a[i].pos+1<=R[a[i].pos]-1 && L[a[i].pos] != 0) l[++top] = (line){a[i].pos+1,R[a[i].pos]-1,L[a[i].pos],p2,0,0};
	sort(l+1,l+top+1);
//	for(LL i=1;i<=top;++i) cout << l[i].x1 << " " << l[i].x2 << " " << l[i].y  << " " << l[i].id << endl; 
	for(LL i=1;i<=top;++i) {
		if(l[i].opt==0) change(1,0,n+1,l[i].x1,l[i].x2,l[i].val);
		else if(l[i].opt==1) ans[l[i].id] -= ask(1,0,n+1,l[i].x1,l[i].x2);
		else ans[l[i].id] += ask(1,0,n+1,l[i].x1,l[i].x2);
	}
	for(LL i=1;i<=m;++i) printf("%lld\n", ans[i]);
}

