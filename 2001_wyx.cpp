
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 50005;
const int inf = 0x3f3f3f3f;
typedef long long ll;
int fa[N],Fa[N];

inline int read(){
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar(); }
	return x*f;
}

void Init(int n) {
	for(int i=1;i<=n;++i) fa[i] = i;
}

int find(int x) {
	return fa[x] ^ x ? fa[x] = find(fa[x]) : fa[x];
}

struct data {
	int x,y,w,k,id;
	bool operator<(const data &s)const  {
		return w<s.w;
	}
}edge[20][N];

struct Lux{
	int x,to;
}chg[N];
int pos[N],dis[N],pa[N];

void init(int m) {
	for(int i = 1;i<= m;i++)
		dis[edge[0][i].id] = edge[0][i].w;
}

void solve(int d,int L,int R,int n,int m,ll ans = 0ll) {
	for(int i = 1;i<= m;i++) {
		data &a = edge[d][i],a2 = edge[d-1][i];
		a = (data){a2.x,a2.y,dis[a2.id],0,a2.id};
		pos[a.id] = i;
	}

	if(L==R) {
		Lux &b = chg[L];
		edge[d][pos[b.x]].w = dis[b.x] = b.to;
		Init(n);
		sort(edge[d]+1,edge[d]+m+1);
		for(int i = 1;i<= m;i++)  {
			data &tmp = edge[d][i];
			int x = find(tmp.x),y = find(tmp.y);
			if(x==y)continue;
			fa[y] = x;
			ans+=tmp.w;
		}
		printf("%lld\n",ans);
		return ;
	}

	int mid = (L+R)>>1;
	for(int i = L;i<=R;i++) edge[d][pos[chg[i].x]].k = 1;

	Init(n);
	sort(edge[d]+1,edge[d]+m+1);
	for(int i = 1;i<= m;i++)
		if(edge[d][i].k==0) {
			data &a = edge[d][i];
			int x = find(a.x), y = find(a.y);
			if(x==y)continue;
			fa[y] = x; a.k = 2;
		}

	for(int i = 1;i<= m;i++) if(edge[d][i].k==1)edge[d][i].w = -inf;

	Init(n);
	sort(edge[d]+1,edge[d]+m+1);
	for(int i = 1;i<= m;i++)
		if(edge[d][i].k!=0)
		{
			data &a = edge[d][i];
			int x = find(a.x),y = find(a.y);
			if(x==y)continue;
			fa[y] = x; if(a.k!=1)a.k = 3;
		}

	Init(n);
	for(int i = 1;i<= m;i++)
		if(edge[d][i].k==3)
		{
			data &a = edge[d][i];
			int x = find(a.x),y = find(a.y);
			if(x==y)continue;
			fa[y] = x;
			ans+=a.w;
		}
	 
	int tmpcnt = 0,cnt = 0;
	for(int i=0;i<=n;++i) Fa[i] = 0;
	for(int i = 1;i<= n;i++) {
		int x = find(i);
		if(!Fa[x])
			Fa[x] = ++tmpcnt;
	}

	for(int i = 1;i<= m;i++)
		if(edge[d][i].k!=0) {
			data &a = edge[d][i];
			int x = find(a.x),y = find(a.y);
			if(x==y)continue;
			edge[d][++cnt] = (data){Fa[x],Fa[y],a.w,a.k,a.id};
		}

	solve(d+1,L,mid,tmpcnt,cnt,ans);
	solve(d+1,mid+1,R,tmpcnt,cnt,ans);
}

int main()
{
	int n = read(), m = read(), q = read();
	for(int i=1;i<=m;++i)
		edge[0][i].x = read(), edge[0][i].y = read(), edge[0][i].w = read(),edge[0][i].id = i;
	for(int i=1;i<=q;++i)chg[i].x = read(), chg[i].to = read();
	init(m);
	solve(1,1,q,n,m);
}
