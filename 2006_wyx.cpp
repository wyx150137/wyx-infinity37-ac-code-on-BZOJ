
#include <queue>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 5e5+5;
const int Maxm = 20*N;
#define mp make_pair 
inline int read(){
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}	
	return x*f;
}

priority_queue <pair<int,int> > q;
int sum[N],now[N],tt,root[N],T[N];
int tr[Maxm],ls[Maxm],rs[Maxm],sz;

void change(int x,int &y,int L,int R,int val){
	y = ++sz; ls[y] = ls[x], rs[y] = rs[x], tr[y] = tr[x] + 1;
	if(L == R) return;
	int mid = (L+R) >> 1;
	if(val <= mid) change(ls[x],ls[y],L,mid,val);
	else change(rs[x],rs[y],mid+1,R,val);
}

int ask(int x,int y,int L,int R,int k){
	if(L == R) return T[L];
	int mid = (L+R) >> 1,
		tmp = tr[ls[y]] - tr[ls[x]];
	if(k <= tmp) return ask(ls[x],ls[y],L,mid,k);
	else return ask(rs[x],rs[y],mid+1,R,k-tmp);
}

inline int find(int x){
	int l = 1, r = tt;
	while(l <= r){
		int mid = (l+r) >> 1;
		if(T[mid] == x) return mid;
		if(T[mid] < x) l = mid + 1;
		else r = mid - 1;
	}
	return l;
}

int main(){
	int n = read(), k = read(), l = read(), r = read(), L,R,tmp,pos;
	for(int i=2;i<=n+1;++i) sum[i] = read()+sum[i-1];
	for(int i=1;i<=n+1;++i) T[++::tt] = sum[i];
	sort(T+1,T+::tt+1); T[::tt=1] = T[1];
	for(int i=2;i<=n+1;++i) if(T[i] != T[i-1]) T[++::tt] = T[i];
	for(int i=1;i<=n+1;++i) sum[i] = find(sum[i]);
	for(int i=1;i<=n+1;++i) change(root[i-1],root[i],1,::tt,sum[i]);
	for(int i=l+1;i<=n+1;++i) {
		L = i - r + 1;
		R = i - l + 1;
		L = max(L,2);
		tmp = ask(root[L-2],root[R-1],1,::tt,++now[i]);
		q.push(mp(T[sum[i]]-tmp,i));
//		cout << i << " " << T[sum[i]] - tmp << endl;
	}
	pair <int,int> tt;
	long long ans = 0;
	for(int i=1;i<=k;++i) {
		tt = q.top(); q.pop(); pos = tt.second, ans += tt.first;
//		cout << tt.first << " " << pos << endl;
		L = pos - r + 1;
		R = pos - l + 1;
		L = max(L,2);
		if(R-L+1!=now[pos]) {
			tmp = ask(root[L-2],root[R-1],1,::tt,++now[pos]);
			q.push(mp(T[sum[pos]]-tmp,pos));
		}
	}
	cout << ans << endl;
}
