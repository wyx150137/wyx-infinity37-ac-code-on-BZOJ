
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
typedef unsigned long long LL;
const int N = 1e5+5;
const int M = N << 3;
LL lazy[M], tr[M];

inline int pow(int a,int b) {
	static int mod = 1e9;
	LL res = 1;
	for(;b;b>>=1,a=(LL)a*a%mod)
		if(b&1) res = res * a % mod;
	return res;
}

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

inline void add(int k,int l,int r,LL val) {
	tr[k] += val * (r-l+1);
	lazy[k] += val;
}

inline void down(int k,int l,int r) {
	if(!lazy[k]) return;
	int mid = (l+r) >> 1;
	add(k<<1,l,mid,lazy[k]);
	add(k<<1|1,mid+1,r,lazy[k]);
	lazy[k] = 0;
}

inline void updata(int k) {
	tr[k] = tr[k<<1] + tr[k<<1|1];
}

inline void change(int k,int l,int r,int x,int y,int val) {
	if(x <= l && r <= y) {
		add(k,l,r,val);
		return;
	}
	down(k,l,r);
	int mid = (l+r) >> 1;
	if(x <= mid) change(k<<1,l,mid,x,y,val);
	if(y > mid) change(k<<1|1,mid+1,r,x,y,val);
	updata(k);
}

inline LL ask(int k,int l,int r,int x,int y) {
	if(x <= l && r <= y) return tr[k];
	int mid = (l+r) >> 1;
	down(k,l,r);
	return ((x <= mid) ? ask(k<<1,l,mid,x,y) : 0) + 
			((y > mid) ? ask(k<<1|1,mid+1,r,x,y) : 0);
}

int stack[N];

struct data{
	int l, r, x, type, id;
	bool operator < (const data &z) const {
		return x < z.x;
	}
} q[N];

LL ans[N];
int a[N];

inline int init(int x) {
	return pow(1023,x) ^ pow(1025,x);
}

int main() {
	int Q = read();
	int cnt = 0, n = 0;
	for(int i=1;i<=Q;++i)  {
		int l1 = read(), r1 = read(), l2 = read(), r2 = read();
		q[++cnt] = (data) {l1, r1, l2-1, 0, i};
		q[++cnt] = (data) {l1, r1, r2, 1, i};
		n = max(n, r2);
	}
	sort(q+1,q+cnt+1);
	for(int i=1;i<=n;++i) a[i] = init(i);
	int top = 0, now = 0;
	while(now < cnt && q[now+1].x == 0) now ++;
	for(int i=1;i<=n;++i) {
		while(top && a[stack[top]] <= a[i]) top --;
		stack[++top] = i;
		for(int j=1;j<=top;++j) change(1,1,n,stack[j-1]+1, stack[j], a[stack[j]]);
		while(now < cnt && q[now+1].x == i) {
			now ++;
			LL sum = ask(1,1,n,q[now].l, q[now].r);
			if(q[now].type) ans[q[now].id] += sum;
			else ans[q[now].id] -= sum;
		}
	}	
	memset(tr, 0, sizeof tr);
	memset(lazy, 0, sizeof lazy);
	top = 0, now = 0;
	while(now < cnt && q[now+1].x == 0) now ++;
	for(int i=1;i<=n;++i) {
		while(top && a[stack[top]] >= a[i]) top --;
		stack[++top] = i;
		for(int j=1;j<=top;++j) change(1,1,n,stack[j-1]+1,stack[j],a[stack[j]]);
		while(now < cnt && q[now+1].x == i) {
			now ++;
			LL sum = ask(1,1,n,q[now].l,q[now].r);
			if(q[now].type) ans[q[now].id] -= sum;
			else ans[q[now].id] += sum;
		}
	}
	for(int i=1;i<=Q;++i) printf("%llu\n", ans[i]);
}
