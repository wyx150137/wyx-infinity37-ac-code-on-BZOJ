
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define N 20000+5
#define M 80000+5
using namespace std;
const int inf = 0x7fffff;
int head[N],depth[N];
int top[N],size[N],w[N],n,m;
int fa[N],sz,val[N];
inline int read()
{
    int x=0,f=1;char ch =getchar();
    while(ch <'0' || ch >'9'){if(ch == '-')f=-1;ch = getchar();}
    while(ch >='0'&& ch<='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
    return x*f;
}
struct graph
{
	int next,to;
	graph () {}
	graph (int _next,int _to)
	:next(_next),to(_to){}
}edge[M];
inline void add(int x,int y)
{
	static int cnt= 0 ;
	edge[++cnt] = graph(head[x],y);
	head[x]=cnt;
	edge[++cnt] = graph(head[y],x);
	head[y]=cnt;
}
void DFS1(int x)
{
	size[x]=1;
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to!=fa[x])
		{
			depth[edge[i].to]=depth[x]+1;
			fa[edge[i].to]=x;
			DFS1(edge[i].to);
			size[x]+=size[edge[i].to];
		}
}
void DFS2(int x,int chain)
{
	top[x]=chain,w[x]=++sz;
	int k = 0;
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to!=fa[x]&&size[k]<size[edge[i].to])
			k=edge[i].to;
	if(!k)return;DFS2(k,chain);
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to!=fa[x]&&edge[i].to!=k)
			DFS2(edge[i].to,edge[i].to);
}
struct seg
{
	int l,r,lazy_rev;
	int MIN,MAX,sum;
}tr[M];
void build(int k,int l,int r)
{
	tr[k].l=l,tr[k].r=r,tr[k].MAX = -inf,tr[k].MIN = inf;
	if(l==r)return;
	int mid = (l+r)>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
}
void ss(int k)
{
	tr[k].lazy_rev ^= 1;
	int tmp = tr[k].MIN;
	tr[k].MIN = (-1)*tr[k].MAX;
	tr[k].MAX = (-1)*tmp;
	tr[k].sum *= -1;
}
inline void down(int k)
{
	if(!tr[k].lazy_rev || tr[k].l==tr[k].r)return;
	tr[k].lazy_rev=0;
	ss(k<<1);
	ss(k<<1|1);
}
inline void updata(int k)
{
	tr[k].sum = (tr[k<<1].sum + tr[k<<1|1].sum);
	tr[k].MAX = max(tr[k<<1].MAX,tr[k<<1|1].MAX);
	tr[k].MIN = min(tr[k<<1].MIN,tr[k<<1|1].MIN);
}
void Rev(int k,int l,int r)
{
	down(k);
	if(l==tr[k].l && r==tr[k].r)
	{
		ss(k);
		return;
	}
	int mid = (tr[k].l+tr[k].r)>>1;
	if(r<=mid)Rev(k<<1,l,r);
	else if(l>mid)Rev(k<<1|1,l,r);
	else Rev(k<<1,l,mid),Rev(k<<1|1,mid+1,r);
	updata(k);
}
void change(int k,int pos,int x)
{
	down(k);
	if(tr[k].l==tr[k].r){tr[k].sum=tr[k].MAX=tr[k].MIN=x;return;}
	int mid = (tr[k].l+tr[k].r)>>1;
	if(pos<=mid)change(k<<1,pos,x);
	else change(k<<1|1,pos,x);
	updata(k);
}
int asksum(int k,int l,int r)
{
	down(k);
	if(l==tr[k].l&&r==tr[k].r)return tr[k].sum;
	int mid = (tr[k].l+tr[k].r)>>1;
	if(r<=mid)return asksum(k<<1,l,r);
	else if(l>mid)return asksum(k<<1|1,l,r);
	else return asksum(k<<1,l,mid)+asksum(k<<1|1,mid+1,r);
}
int askMAX(int k,int l,int r)
{
	down(k);
	if(l==tr[k].l&&r==tr[k].r)return tr[k].MAX;
	int mid = (tr[k].l+tr[k].r)>>1;
	if(r<=mid)return askMAX(k<<1,l,r);
	else if(l>mid)return askMAX(k<<1|1,l,r);
	else return max(askMAX(k<<1,l,mid),askMAX(k<<1|1,mid+1,r));
}
int askMIN(int k,int l,int r)
{
	down(k);
	if(l==tr[k].l&&r==tr[k].r)return tr[k].MIN;
	int mid = (tr[k].l+tr[k].r)>>1;
	if(r<=mid)return askMIN(k<<1,l,r);
	else if(l>mid)return askMIN(k<<1|1,l,r);
	else return min(askMIN(k<<1,l,mid),askMIN(k<<1|1,mid+1,r));
}
int solvesum(int x,int y)
{
	int ans = 0;
	while(top[x] ^ top[y])
	{
		if(depth[top[x]]<depth[top[y]])swap(x,y);
		ans += asksum(1,w[top[x]],w[x]);x=fa[top[x]];
	}
	if(depth[x]>depth[y])swap(x,y);
	if(w[x]!=w[y])
		ans += asksum(1,w[x]+1,w[y]);
	return ans;
}
int solveMAX(int x,int y)
{
	int ans = -inf;
	while(top[x]!=top[y])
	{
		if(depth[top[x]]<depth[top[y]])swap(x,y);
		ans = max(ans,askMAX(1,w[top[x]],w[x]));x=fa[top[x]];
	}
	if(depth[x]>depth[y])swap(x,y);
	if(w[x]!=w[y])ans = max (askMAX(1,w[x]+1,w[y]),ans);
	return ans;
}
int solveMIN(int x,int y)
{
	int ans = inf;
	while(top[x]!=top[y])
	{
		if(depth[top[x]]<depth[top[y]])swap(x,y);
		ans = min(ans,askMIN(1,w[top[x]],w[x]));x=fa[top[x]];
	}
	if(depth[x]>depth[y])swap(x,y);
	if(w[x]!=w[y])ans = min (askMIN(1,w[x]+1,w[y]),ans);
	return ans;
}
void solveRev(int x,int y)
{
	while(top[x]!=top[y])
	{
		if(depth[top[x]]<depth[top[y]])swap(x,y);
		Rev(1,w[top[x]],w[x]);x=fa[top[x]];
	}
	if(depth[x]>depth[y])swap(x,y);
	if(w[x]!=w[y])Rev(1,w[x]+1,w[y]);
}
int x[N],y[N];
int main()
{
	//freopen("02.in","r",stdin);
	cin>>n;
	for(int i=1;i<n;++i)
	{
		x[i]=read(),y[i]=read(),val[i]=read();
		++x[i],++y[i];
		add(x[i],y[i]);
	}
	DFS1(1);
	DFS2(1,1);
	build(1,1,n);
	for(int i=1;i<n;i++)change(1,w[ depth[x[i]] > depth[y[i]] ? x[i] : y[i] ],val[i]);
	int m=read();
	char str[10];
	while(m--)
	{
		scanf("%s",str);
		int X=read()+1,Y=read()+1;
		if(str[0]=='C')
		{
			X--,Y--;
			change(1,w[ depth[x[X]] > depth[y[X]] ? x[X] : y[X] ],Y);
		}
		else if(str[0]=='N')
			solveRev(X,Y);
		else if(str[0]=='S')
			printf("%d\n",solvesum(X,Y));
		else if(str[1]=='I')
			printf("%d\n",solveMIN(X,Y));
		else
			printf("%d\n",solveMAX(X,Y));
	}
}
