
#include <map>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define lowbit(x) ((x)&(-x))
using namespace std;
const int N = 5e4+5;
const int M = 20 *N;
map <int,int> mp;
int n,m,cnt,lastans,T[N];
int sum[N],tot,a[N],block;
int root[N],F[250+1][N];
int ls[M],rs[M],tr[M],num[N];

inline int read(){
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

inline void updata(int x,int val){
	while(x <= tot){
		sum[x] += val;
		x += lowbit(x);
	}
}

int ask(int x){
	int ans = 0;
	while(x){
		ans += sum[x] ;
		x -= lowbit(x);
	}
	return ans;
}

void change(int x,int &y,int L,int R,int val){
	y = ++cnt; tr[y] = tr[x] + 1; ls[y] = ls[x], rs[y] = rs[x];
	if(L==R) return;
	int mid = (L+R) >> 1;
	if(val <= mid) change(ls[x],ls[y],L,mid,val);
	else change(rs[x],rs[y],mid+1,R,val);
}

int ask(int x,int y,int L,int R,int l,int r){
	if(L == l && R == r) return tr[y] - tr[x];
	int mid = (L+R) >> 1;
	if(r<=mid)return ask(ls[x],ls[y],L,mid,l,r);
	else if(l > mid)return ask(rs[x],rs[y],mid+1,R,l,r);
	else return ask(ls[x],ls[y],L,mid,l,mid) + ask(rs[x],rs[y],mid+1,R,mid+1,r);
}

int ask(int x,int y){
	int ans = 0;
	register int i;
	if(num[x] == num[y]){
		memset(sum,0,sizeof sum);
		for(i=x;i<=y;++i) {
			ans += ask(tot) - ask(a[i]);
			updata(a[i],1);
		}
		return ans;
	}
	ans = F[num[x]+1][y];
	for(int i=x;i<=num[x]*block;++i) if(a[i] > 1) ans += ask(root[i],root[y],1,tot,1,a[i]-1);
	return ans;
}

int main(){ //freopen("noon.in","r",stdin); freopen("noon.out","w",stdout);
	n = read();
	block = 250;
	register int i,j;
	for(i=1;i<=n;++i) T[i] = a[i] = read();
	sort(T+1,T+n+1); tot = n;
	for(i=1;i<=n;++i) mp[T[i]] = i;
	for(i=1;i<=n;++i) a[i] = mp[a[i]];
	for(i=1;i<=n;++i) change(root[i-1],root[i],1,tot,a[i]);
	for(i=1;i<=n;++i) num[i] = (i-1)/250+1;
	for(i=1;i<=num[n];++i){
		memset(sum,0,sizeof sum);
		for(j=(i-1)*250+1;j<=n;++j){
			F[i][j] = F[i][j-1] + ask(tot) - ask(a[j]);
			updata(a[j],1);
		}
	}
	int Q = read(),x,y;
	for(i=1;i<=Q;++i){
		x = read() ^ lastans;
		y = read() ^ lastans;
	//	x = read(), y = read();
		printf("%d\n",lastans = ask(x,y));
	}
}
