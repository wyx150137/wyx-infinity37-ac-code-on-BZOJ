
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = 1e5+5;
const int M = N << 2;

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int n, m, l1, r1, l2, r2, cnt;
int a[N];
LL ans[N];
int stack[N], top;

struct query {
	int x, l, r, id, opt;
	query () {}
	query (int _x,int _l,int _r,int _id,int _opt) 
	:x(_x),l(_l),r(_r),id(_id),opt(_opt){}
	bool operator < (const query &z) const {
		return x < z.x;
	}
}q[N]; 

struct data {
	LL a, b, c, d;
	data () {
		a = 1, b = c = d = 0;
	}
	data (LL _a,LL _b,LL _c,LL _d)
	:a(_a),b(_b),c(_c),d(_d){}
	inline bool check() {
		return a != 1 || b || c || d;
	}
	data operator + (const data &z) const {
		return data(a*z.a,b*z.a+z.b,a*z.c+c,b*z.c+d+z.d);
	}
}tmp;

struct seg {
	LL val, sum;
	data lazy;
}tr[M];

inline void solve(int k,int l,int r,data p) {
	int len = r - l + 1;
	tr[k].sum += p.c *tr[k].val + p.d * len;
	tr[k].val = p.a * tr[k].val + p.b * len;
	tr[k].lazy = tr[k].lazy + p;
}

inline void down(int k,int l,int r) {
	if(l==r) return;
	data tt = tr[k].lazy;
	if(tt.a != 1 || tt.b || tt.c || tt.d) {
		int mid = (l+r) >> 1;
		solve(k<<1,l,mid,tt);
		solve(k<<1|1,mid+1,r,tt);
		tr[k].lazy = data();
	}
}

void build(int k,int l,int r) {
	tr[k].val = tr[k].sum = 0;
	tr[k].lazy = data();
	if(l==r) return;
	int mid = (l+r) >> 1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
}

inline void change(int k,int l,int r,int x,int y){
	if(l==x && r==y) {
		solve(k,l,r,tmp);
		return;
	}
	down(k,l,r);
	int mid = (l+r) >> 1;
	if(y <= mid) change(k<<1,l,mid,x,y);
	else if(x > mid) change(k<<1|1,mid+1,r,x,y);
	else change(k<<1,l,mid,x,mid), change(k<<1|1,mid+1,r,mid+1,y);
	tr[k].val = tr[k<<1].val + tr[k<<1|1].val;
	tr[k].sum = tr[k<<1].sum + tr[k<<1|1].sum;
}

inline LL ask(int k,int l,int r,int x,int y) {
	if(l==x && r==y) return tr[k].sum;
	down(k,l,r);
	int mid = (l+r) >> 1;
	if(y <= mid) return ask(k<<1,l,mid,x,y);
	else if(x > mid) return ask(k<<1|1,mid+1,r,x,y);
	else return ask(k<<1,l,mid,x,mid) + ask(k<<1|1,mid+1,r,mid+1,y);
}

int main() {
	n = read(), m = read();
	int L, R;
	for(int i=1;i<=n;++i) a[i] = read();
	for(int i=1;i<=m;++i) {
		L = read(), R = read();
		l1 = L, r1 = R;
		l2 = 1, r2 = R;
		if(l2 > 1) q[++cnt] = query(l2-1,l1,r1,i,-1);
		q[++cnt] = query(r2,l1,r1,i,1);
	}
	sort(q+1,q+cnt+1);
	build(1,1,n);
	data tmp1 = (data){1,1,1,1};
	data tmp2 = (data){2,2,2,2};
	tmp1 = tmp1 + tmp2;
	register int i, j;
	for(i=1,j=1;i<=n;stack[++top]=i++) {
		while(top && a[stack[top]]>a[i]) top --;
		tmp = data(0,a[i],0,0);
		change(1,1,n,stack[top]+1,i);
		solve (1,1,n,data(1,0,1,0));
		while(j <= cnt &&  q[j].x == i) 
			ans[q[j].id] += ask(1,1,n,q[j].l,q[j].r) * q[j].opt, j ++;
	}
	for(int i=1;i<=m;++i) printf("%lld\n",ans[i]);
}
