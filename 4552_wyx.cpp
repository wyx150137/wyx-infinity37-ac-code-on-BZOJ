
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 1e5+5;
const int M = N << 2;
using namespace std;

inline int read(){
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int tr[M],lazy[M];
int a[N];

void build(int k,int l,int r){
	lazy[k] = -1;
	if(l==r){
		tr[k] = a[l];
		return;
	}
	int mid = (l+r) >> 1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
	tr[k] = tr[k<<1] + tr[k<<1|1];
}

inline void down(int k,int l,int r){
	if(l==r || lazy[k] == -1)return;
	int tmp = lazy[k]; lazy[k] = -1;
	int mid = (l+r) >> 1;
	tr[k<<1] = (mid-l+1) * tmp;
	tr[k<<1|1] = (r-mid) * tmp;
	lazy[k<<1] = lazy[k<<1|1] = tmp;
	return;
}

void change(int k,int l,int r,int x,int y,int val){
	if(l==x && r==y){
		tr[k] = (r-l+1)*val;
		lazy[k] = val;
		return;
	}
	down(k,l,r);
	int mid = (l+r) >> 1;
	if(y <= mid) change(k<<1,l,mid,x,y,val);
	else if(x > mid) change(k<<1|1,mid+1,r,x,y,val);
	else change(k<<1,l,mid,x,mid,val), change(k<<1|1,mid+1,r,mid+1,y,val);
	tr[k] = tr[k<<1] + tr[k<<1|1];
}

int ask(int k,int l,int r,int x,int y){
	if(l==x && r==y) return tr[k];
	int mid = (l+r) >> 1;
	down(k,l,r);
	if(y <= mid) return ask(k<<1,l,mid,x,y);
	else if(x > mid) return ask(k<<1|1,mid+1,r,x,y);
	else return ask(k<<1,l,mid,x,mid) + ask(k<<1|1,mid+1,r,mid+1,y);
}

int ask(int k,int l,int r,int pos){
	if(l==r)return tr[k];
	down(k,l,r);
	int mid = (l+r) >> 1;
	if(pos <= mid)return ask(k<<1,l,mid,pos);
	else return ask(k<<1|1,mid+1,r,pos);
}

int tmp[N];

struct data{
	int opt,x,y;
}t[N];

int n,m;

void solve(int x){
	memset(tr,0,sizeof tr);
	for(int i=1;i<=n;++i) a[i] = (tmp[i] >= x);
	build(1,1,n);
	for(int i=1;i<=m;++i){

		int tmp = ask(1,1,n,t[i].x,t[i].y);
		int left = t[i].y - t[i].x + 1 - tmp;

		if(t[i].opt == 0){
			if(t[i].x <= t[i].x+left-1) change(1,1,n,t[i].x,t[i].x+left-1,0);
			if(t[i].x+left <= t[i].y) change(1,1,n,t[i].x+left,t[i].y,1);
		}
		else{
			if(t[i].x <= t[i].x+tmp-1) change(1,1,n,t[i].x,t[i].x+tmp-1,1);
			if(t[i].x+tmp<=t[i].y) change(1,1,n,t[i].x+tmp,t[i].y,0);
		}
	}
}

int main(){
	n = read(), m = read();
	for(int i=1;i<=n;++i) tmp[i] = read();
	for(int i=1;i<=m;++i) t[i].opt = read(), t[i].x = read(), t[i].y = read();
	int q = read();
	int l = 1, r = n + 1;
	while(l < r){
		int mid = (l+r) >> 1;
		solve(mid);
		int tmp = ask(1,1,n,q);
		if(tmp) l = mid + 1;
		else r = mid;
	}
	cout << l-1 << endl;
}
