
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 8e4+5;
struct E
{int next,to;}e[N<<1];
int head[N],tot,fa[N][20];
struct Plate
{int xd,xu,yd,yu,v;}plate[N];
struct Event
{int x,yd,yu,v,id;}event[N];
struct Poi
{int x,y,k,id;}poi[N],tmp1[N],tmp2[N];
bool operator <(Plate a,Plate b){return a.v<b.v;}
bool operator <(Event a,Event b){return a.x==b.x?a.id<b.id:a.x<b.x;}
void add(int x,int y)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	head[x] = tot;
}
int last[N],dfn[N],dep[N],cnt,n,m,q,Cnt;
void dfs(int x,int f)
{
	dfn[x] = ++cnt;
	dep[x] = dep[f]+1;
	fa[x][0] = f;
	for(int i= head[x];i;i=e[i].next)
		if(e[i].to!=f)
			dfs(e[i].to,x);
	last[x] = cnt;
}
void init()
{
	for(int j = 1;j<= 18;j++)
		for(int i = 1;i<= n;i++)
			fa[i][j] = fa[fa[i][j-1]][j-1];
}
int getlca(int x,int y)
{
	if(dep[x]<dep[y])swap(x,y);
	for(int i = 18;i>= 0;i--)
		if(dep[fa[x][i]]>=dep[y])
			x = fa[x][i];
	if(x==y)return x;
	for(int i = 18;i>= 0;i--)
		if(fa[x][i]!=fa[y][i])
			x = fa[x][i],y = fa[y][i];
	return fa[x][0];
}
int jump(int x,int h)
{
	for(int j = 18;j>= 0;j--)
		if(h>=(1<<j))
			x = fa[x][j],h-=(1<<j);
	return x;
}
struct Tree
{
	int val[N];
	void update(int l,int r,int x)
	{
		for(int i = l;i<N;i+=i&(-i))
			val[i]+=x;
		for(int i = r+1;i<N;i+=i&(-i))
			val[i]-=x;
	}
	int getans(int x)
	{
		int ans = 0;
		for(int i = x;i>0;i-=i&(-i))
			ans+=val[i];
		return ans;
	}
}T;
int ans[N],sum[N];
void solve(int l,int r,int st,int ed)
{
	if(ed<st)return ;
	if(l==r)
	{
		for(int i = st;i<= ed;i++)
			ans[poi[i].id] = plate[l].v;
		return ;
	}
	int mid = (l+r)>>1,siz=0;
	for(int i = l;i<= mid;i++)
	{
		event[++siz]=(Event){plate[i].xd,plate[i].yd,plate[i].yu,1,0};
		event[++siz]=(Event){plate[i].xu,plate[i].yd,plate[i].yu,-1,n+1};
	}
	for(int i = st;i<=ed;i++)
		event[++siz]=(Event){poi[i].x,poi[i].y,0,0,i};
	sort(event+1,event+siz+1);
	for(int i = 1;i<= siz;i++)
		if(event[i].id>=st&&event[i].id<=ed)
			sum[event[i].id]=T.getans(event[i].yd);
		else T.update(event[i].yd,event[i].yu,event[i].v);
	int a = 0,b = 0;
	for(int i = st;i<=ed;i++)
		if(sum[i]>=poi[i].k)tmp1[++a] = poi[i];
		else tmp2[++b] = (Poi){poi[i].x,poi[i].y,poi[i].k-sum[i],poi[i].id};
	for(int i = st;i<= st+a-1;i++)poi[i]=tmp1[i-st+1];
	for(int i = st+a;i<= ed;i++)poi[i] = tmp2[i-st-a+1];
	solve(l,mid,st,st+a-1),solve(mid+1,r,st+a,ed);
}
int main()
{
	int x,y,z,lca;
	scanf("%d%d%d",&n,&m,&q);
	for(int i = 1;i< n;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y),add(y,x);
	}
	dfs(1,0);
	init();
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		lca = getlca(x,y);
		if(dfn[x]>dfn[y])swap(x,y);
		if(lca!=x)plate[++Cnt] = (Plate){dfn[x],last[x],dfn[y],last[y],z};
		else
		{
			int t = jump(y,dep[y]-dep[x]-1);
			plate[++Cnt]=(Plate){1,dfn[t]-1,dfn[y],last[y],z};
			if(last[t]<n)
				plate[++Cnt]=(Plate){dfn[y],last[y],last[t]+1,n,z};
		}
	}
	sort(plate+1,plate+Cnt+1);
	for(int i =1;i<=q;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		if(dfn[x]>dfn[y])swap(x,y);
		poi[i]=(Poi){dfn[x],dfn[y],z,i};
	}
	solve(1,Cnt,1,q);
	for(int i = 1;i<= q;i++)
		printf("%d\n",ans[i]);
	return 0;
}
