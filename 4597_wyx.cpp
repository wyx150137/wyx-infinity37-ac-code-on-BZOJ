
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int mod = 1e9+7;
typedef long long LL;
const int N = 100000+5;
const int M = N << 2;
int tr[M], pwn[N], a[N], lazy[M], n;

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

inline int pow(int a,int b) {
	int res = 1;
	for(;b;b>>=1,a=(LL)a*a%mod)
		if(b&1)
			res = (LL) res * a % mod;
	return res;
}

inline void build(int k,int l,int r) {
	lazy[k] = 1;
	if(l==r) {
		if(r == n) tr[k] = 1;
		else tr[k] = pwn[n-l-1];
		return;
	}
	int mid = (l+r) >> 1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
	tr[k] = (tr[k<<1] + tr[k<<1|1]) % mod;
}

inline void down(int k,int l,int r) {
	if(lazy[k] == 1) return;
	int temp = lazy[k]; lazy[k] = 1; 
	lazy[k<<1] = (LL) lazy[k<<1] * temp % mod;
	lazy[k<<1|1] = (LL) lazy[k<<1|1] * temp % mod;
	tr[k<<1] = (LL) tr[k<<1] * temp % mod;
	tr[k<<1|1] = (LL) tr[k<<1|1] * temp % mod;
}

inline void change(int k,int l,int r,int x,int y,int val) {
	if(l==x && r==y) {
		lazy[k] = (LL)lazy[k]*val%mod;
		tr[k] = (LL)tr[k]*val%mod;
		return;
	}
	down(k,l,r);
	int mid = (l+r) >> 1;
	if(y <= mid) change(k<<1,l,mid,x,y,val);
	else if(x > mid) change(k<<1|1,mid+1,r,x,y,val);
	else change(k<<1,l,mid,x,mid,val), change(k<<1|1,mid+1,r,mid+1,y,val);
	tr[k] = (tr[k<<1] + tr[k<<1|1]) % mod;
}

int main() {
	n = read();
	int q = read();
	for(int i=1;i<=n;++i) a[i] = read();
	pwn[0] = 1;
	for(int i=1;i<=n;++i) pwn[i] = (LL)pwn[i-1] * 3 % mod;
	build(1,1,n);
	int all = 1;
	for(int i=1;i<=n;++i) all = (LL)all * a[i] % mod;
	for(int i=1;i<=n;++i) change(1,1,n,i,n,a[i]);
	for(int i=1;i<=q;++i) {
		int pos = read(), val = read();
		change(1,1,n,pos,n,pow(a[pos],mod-2));
		all = (LL)all * pow(a[pos], mod-2) % mod;
		a[pos] = val;
		change(1,1,n,pos,n,val);
		all = (LL)all * val % mod;
		printf("%d\n", (tr[1]*2%mod-all+mod)%mod);
	}
}
