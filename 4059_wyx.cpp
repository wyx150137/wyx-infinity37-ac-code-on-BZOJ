
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5+5;
int n;

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

struct data {
	int v, x, p;
	data (int _v=0,int _x=0,int _p=0)
	:v(_v),x(_x),p(_p) {}
} a[N];

bool cmp1(const data &x, const data &y) {
	return x.v < y.v;
}

bool cmp2(const data &x, const data &y) {
	return x.p < y.p;
}

int T[N];
int be[N], nxt[N], last[N];

bool check(int l,int r) {
	if(l > r) return true;
	int L = l, R = r;
	while(L <= R) {
		if(be[L] < l && nxt[L] > r) return check(l,L-1)&check(L+1,r);
		if(be[R] < l && nxt[R] > r) return check(l,R-1)&check(R+1,r);
		L ++, R --;
	}
	return false;
}

int main() {
	int T = read();
	while(T --) {
		int n = read();
		for(int i=1;i<=n;++i) {
			a[i].v = read();
			a[i].p = i;            
		}
		sort(a+1,a+n+1,cmp1);
		for(int i=1;i<=n;++i) ::T[i] = a[i].v;
		for(int i=1;i<=n;++i) a[i].x = lower_bound((::T)+1,(::T)+n+1,a[i].v)-(::T);
		sort(a+1,a+n+1,cmp2);
		for(int i=1;i<=n;++i) last[i] = n + 1;
		for(int i=n;i>=1;--i) {
			nxt[i] = last[a[i].x];
			last[a[i].x] = i;
		}
		for(int i=1;i<=n;++i) last[i] = 0;
		for(int i=1;i<=n;++i) {
			be[i] = last[a[i].x];
			last[a[i].x] = i;
		}
		printf("%s\n", check(1,n) ? "non-boring" : "boring");
	}
}
