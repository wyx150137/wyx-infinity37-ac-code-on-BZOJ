
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 80000+5;
const int M = N << 2;
typedef long long LL;

int tr[M];

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

inline void down(int k,int l,int r)
{
	if(l==r)return;
	int tmp = tr[k];
	tr[k] = 0 ;
	tr[k<<1] = max(tr[k<<1],tmp);
	tr[k<<1|1] = max(tr[k<<1|1],tmp);
}

void change(int k,int l,int r,int x,int y,int tmp)
{
	down(k,l,r);
	if(l==x && r==y){
		tr[k] = max(tr[k],tmp);
		return;
	}
	int mid = (l+r)>>1;
	if(y <= mid) change(k<<1,l,mid,x,y,tmp);
	else if(x > mid) change(k<<1|1,mid+1,r,x,y,tmp);
	else change(k<<1,l,mid,x,mid,tmp),change(k<<1|1,mid+1,r,mid+1,y,tmp);
}

int ans[N];

void go(int k,int l,int r)
{
	down(k,l,r);
	if(l==r){ans[l] = tr[k];return;}
	int mid = (l+r)>>1;
	go(k<<1,l,mid);go(k<<1|1,mid+1,r);
}

int T[N<<1];
int sz;
int X[2][N];
int Y[N];

int find(int x)
{
	int l = 1;
	int r = sz;
	while(l<=r){
		int mid = (l+r)>>1;
		if(T[mid] == x) return mid;
		if(T[mid] < x) l = mid + 1;
		else r = mid - 1;
	}
	return 0;
}

int main()
{
	int n = read();
	for(int i=1;i<=n;++i){
		T[++sz] = X[0][i] = read();
		T[++sz] = X[1][i] = read();
		Y[i] = read();
	}
	sort(T+1,T+sz+1);
	int tt = n << 1;
	for(int i=1;i<=n;++i)
	{
		X[0][i] = find(X[0][i]);
		X[1][i] = find(X[1][i]);
		change(1,1,tt,X[0][i],X[1][i]-1,Y[i]);
	}
	LL tmp = 0;
	go(1,1,tt);
	for(int i=1;i<tt;++i)
		tmp += (LL) ans[i]*(T[i+1]-T[i]);
	cout << tmp << endl;
}
