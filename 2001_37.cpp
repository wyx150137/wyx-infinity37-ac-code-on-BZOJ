
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 50005;
const int INF = 0x3f3f3f3f;
typedef long long ll;
int fa[N],Fa[N];
void Init(int n)
{
	for(int i = 1;i<=n;i++)fa[i] = i;
}
int getfa(int x)
{
	return fa[x]==x?x:(fa[x]=getfa(fa[x]));
}
struct P
{
	int x,y,w,k,id;
	bool operator<(const P &s)const 
		{return w<s.w;}
}e[20][N];
struct C
{
	int x,to;
}chg[N];
int pos[N],dis[N],pa[N];
void init(int m)
{
	for(int i = 1;i<= m;i++)
		dis[e[0][i].id] = e[0][i].w;
}
void solve(int d,int L,int R,int n,int m,ll ans = 0ll)
{
	for(int i = 1;i<= m;i++)
	{
		P &a = e[d][i],a2 = e[d-1][i];
		a = (P){a2.x,a2.y,dis[a2.id],0,a2.id};
		pos[a.id] = i;
	}
	if(L==R)
	{
		C &b = chg[L];
		e[d][pos[b.x]].w = dis[b.x] = b.to;
		Init(n);
		sort(e[d]+1,e[d]+m+1);
		for(int i = 1;i<= m;i++)
		{
			P &tmp = e[d][i];
			int x = getfa(tmp.x),y = getfa(tmp.y);
			if(x==y)continue;
			fa[y] = x;
			ans+=tmp.w;
		}
		printf("%lld\n",ans);
		return ;
	}
	int mid = (L+R)>>1;
	for(int i = L;i<=R;i++)e[d][pos[chg[i].x]].k = 1;
	Init(n);
	sort(e[d]+1,e[d]+m+1);
	for(int i = 1;i<= m;i++)
		if(e[d][i].k==0)
		{
			P &a = e[d][i];
			int x = getfa(a.x),y = getfa(a.y);
			if(x==y)continue;
			fa[y] = x;
			a.k = 2;
		}
	for(int i = 1;i<= m;i++)
		if(e[d][i].k==1)e[d][i].w = -INF;
	Init(n);
	sort(e[d]+1,e[d]+m+1);
	for(int i = 1;i<= m;i++)
		if(e[d][i].k!=0)
		{
			P &a = e[d][i];
			int x = getfa(a.x),y = getfa(a.y);
			if(x==y)continue;
			fa[y] = x;
			if(a.k!=1)a.k = 3;
		}
	Init(n);
	for(int i = 1;i<= m;i++)
		if(e[d][i].k==3)
		{
			P &a = e[d][i];
			int x = getfa(a.x),y = getfa(a.y);
			if(x==y)continue;
			fa[y] = x;
			ans+=a.w;
		}
	int newn = 0,newm = 0;
	for(int i = 0;i<= n;i++)Fa[i] = 0;
	for(int i = 1;i<= n;i++)
	{
		int x = getfa(i);
		if(!Fa[x])Fa[x] = ++newn;
	}
	for(int i = 1;i<= m;i++)
		if(e[d][i].k!=0)
		{
			P &a = e[d][i];
			int x = getfa(a.x),y = getfa(a.y);
			if(x==y)continue;
			e[d][++newm] = (P){Fa[x],Fa[y],a.w,a.k,a.id};
		}
	solve(d+1,L,mid,newn,newm,ans);
	solve(d+1,mid+1,R,newn,newm,ans);
}
int main()
{
	int n,m,q;
	scanf("%d%d%d",&n,&m,&q);
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d%d",&e[0][i].x,&e[0][i].y,&e[0][i].w);
		e[0][i].id = i;
	}
	for(int i = 1;i<= q;i++)
		scanf("%d%d",&chg[i].x,&chg[i].to);
	init(m);
	solve(1,1,q,n,m);
	return 0;
}
