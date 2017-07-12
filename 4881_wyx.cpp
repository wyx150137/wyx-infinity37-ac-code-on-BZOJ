
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int mod = 998244353;
const int N = 1e5+5;
const int M = N << 2;
using namespace std;

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int n;
int Max[M], Min[M], a[N];
int col[N];

inline int merge_mx(int x,int y) {
	if(!x || !y) return x + y;
	return a[x] > a[y] ? x : y;
}

inline int merge_mn(int x,int y) {
	if(!x || !y) return x + y;
	return a[x] < a[y] ? x : y;
}

inline void updata(int k) {
	Max[k] = merge_mx(Max[k<<1], Max[k<<1|1]);
	Min[k] = merge_mn(Min[k<<1], Min[k<<1|1]);
}

int pos[N];

inline void build(int k,int l,int r) {
	if(l==r) {
		Max[k] = Min[k] = l;
		pos[l] = k;
		return;
 	}
	int mid = (l+r) >> 1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
	updata(k);
}

inline void del(int k) {
	k = pos[k];
	Min[k] = Max[k] = 0;
	for(k>>=1;k;k>>=1) updata(k);
}

int ans;

inline void ask_mx(int k,int l,int r,int x,int y) {
	if(x <= l && r <= y) {
		ans = merge_mx(ans, Max[k]);
		return ;
	}
	int mid = (l+r) >> 1;
	if(x <= mid) ask_mx(k<<1,l,mid,x,y);
	if(y > mid) ask_mx(k<<1|1,mid+1,r,x,y);
}

inline void ask_mn(int k,int l,int r,int x,int y) {
	if(x <= l && r <= y) {
		ans = merge_mn(ans, Min[k]);
		return;
	}
	int mid = (l+r) >> 1;
	if(x <= mid) ask_mn(k<<1,l,mid,x,y);
	if(y > mid) ask_mn(k<<1|1,mid+1,r,x,y);
}

inline void DFS(int x,int y) {
	del(x);
	col[x] = y;
	y = 3 - y;
	while(1) {
		ans = 0;
		ask_mn(1,1,n,x,n);
		if(ans && a[ans] < a[x]) DFS(ans, y); 
		else break;
	}
	while(1) {
		ans = 0;
		ask_mx(1,1,n,1,x);
		if(ans && a[ans] > a[x]) DFS(ans, y);
		else break;
	}
}

int f[20];

int main() {
	n = read();
	for(int i=1;i<=n;++i) a[i] = read();
	build(1,1,n);
	int cnt = 0;
	for(int i=1;i<=n;++i) {
		if(!col[i]) {
			DFS(i,1);
			cnt ++;
		}
	}
	for(int i=1;i<=n;++i) {
		if(a[i] < f[col[i]]) return 0*puts("0");
		f[col[i]] = a[i];
	}
	ans = 1;
	while(cnt --) {
		ans = ans << 1;
		ans %= mod;
	}
	cout << ans << endl;
}
