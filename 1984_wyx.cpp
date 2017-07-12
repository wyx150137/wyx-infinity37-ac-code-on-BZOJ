
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define N 100000+5
#define M 400000+5
using namespace std;

int head[N],size[N],top[N];
int w[N],sz,fa[N],depth[N];

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0'||ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0'&&ch <='9'){x=(x<<1)+(x<<3) + ch - '0';ch = getchar();}
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
	static int cnt = 0;
	edge[++cnt] = graph(head[x],y);
	head[x] = cnt;
	edge[++cnt] = graph(head[y],x);
	head[y] = cnt;
}

void DFS1(int x)
{
	size[x] = 1;
	for(int i=head[x] ; i; i=edge[i].next)
		if(edge[i].to!=fa[x])
		{
			depth[edge[i].to] = depth [x] + 1;
			fa[edge[i].to] = x;
			DFS1(edge[i].to);
			size[x] += size[edge[i].to];
		}
}

void DFS2(int x,int chain)
{
	w[x]= ++sz;top[x] = chain;
	int k = 0;
	for(int i=head[x] ; i; i=edge[i].next)
		if(edge[i].to!=fa[x]&&size[k]<size[edge[i].to])
			k = edge[i].to;
	if(!k)return;
	DFS2(k,chain);
	for(int i=head[x]; i ;i=edge[i].next)
		if(edge[i].to!=fa[x] && edge[i].to!=k)
			DFS2(edge[i].to,edge[i].to);
}

struct seg
{
	int l,r;
	int Plazy,Alazy;
	int mn;
}tr[M];

void build(int k,int l,int r)
{
	tr[k].l=l,tr[k].r=r;
	if(l==r)return;
	int mid = (l+r)>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
}

void updata(int k)
{
	tr[k].mn = max(tr[k<<1].mn,tr[k<<1|1].mn);
}

void down(int k)
{
	if(tr[k].l==tr[k].r)return;
	if(tr[k].Plazy)
	{
		tr[k<<1].Alazy = tr[k<<1|1].Alazy = 0;
		tr[k<<1].mn = tr[k<<1|1].mn = tr[k].Plazy;
		tr[k<<1].Plazy = tr[k<<1|1].Plazy = tr[k].Plazy;
		tr[k].Plazy = 0;
	}
	if(tr[k].Alazy)
	{
		tr[k<<1].mn += tr[k].Alazy;
		tr[k<<1|1].mn += tr[k].Alazy;
		if(tr[k<<1].Plazy)tr[k<<1].Plazy += tr[k].Alazy;
		else tr[k<<1].Alazy += tr[k].Alazy;
		if(tr[k<<1|1].Plazy)tr[k<<1|1].Plazy += tr[k].Alazy;
		else tr[k<<1|1].Alazy += tr[k].Alazy;
		tr[k].Alazy = 0;
	}
	return;

}

void Pchange(int k,int l,int r,int x)
{
	down(k);
	if(l==tr[k].l && r==tr[k].r)
	{
		tr[k].Plazy = x;
		tr[k].mn = x;
		return;
	}
	int mid = (tr[k].l+tr[k].r)>>1;
	if(r<=mid)Pchange(k<<1,l,r,x);
	else if(l>mid)Pchange(k<<1|1,l,r,x);
	else Pchange(k<<1,l,mid,x),Pchange(k<<1|1,mid+1,r,x);
	updata(k);
}

void Achange(int k,int l,int r,int x)
{
	down(k);
	if(l==tr[k].l && r==tr[k].r)
	{
		tr[k].Alazy  += x;
		tr[k].mn +=  x;
		return;
	}
	int mid = (tr[k].l+tr[k].r)>>1;
	if(r<=mid)Achange(k<<1,l,r,x);
	else if(l>mid)Achange(k<<1|1,l,r,x);
	else Achange(k<<1,l,mid,x),Achange(k<<1|1,mid+1,r,x);
	updata(k);
}

int ask(int k,int l,int r)
{
	down(k);
	if(l==tr[k].l && r==tr[k].r)
		return tr[k].mn;
	int mid = (tr[k].l+tr[k].r)>>1;
	if(r<=mid)return ask(k<<1,l,r);
	else if(l>mid)return ask(k<<1|1,l,r);
	else return max(ask(k<<1,l,mid),ask(k<<1|1,mid+1,r));
}

void solvePchange(int x,int y,int c)
{
	while(top[x]!=top[y])
	{
		if(depth[top[x]] < depth[top[y]])swap(x,y);
		Pchange(1,w[top[x]],w[x],c);x=fa[top[x]];
	}
	if(depth[x] > depth[y])swap(x,y);
	if(w[x]!=w[y])Pchange(1,w[x]+1,w[y],c);
	return;
}

void solveAchange(int x,int y,int c)
{
	while(top[x]!=top[y])
	{
		if(depth[top[x]] < depth[top[y]])swap(x,y);
		Achange(1,w[top[x]],w[x],c);x=fa[top[x]];
	}
	if(depth[x] > depth[y])swap(x,y);
	if(w[x]!=w[y])Achange(1,w[x]+1,w[y],c);
	return;
}

int solveask(int x,int y)
{
	int ans = 0;
	while(top[x]!=top[y])
	{
		if(depth[top[x]] < depth[top[y]])swap(x,y);
		ans = max(ans ,ask(1,w[top[x]],w[x]));x=fa[top[x]];
	}
	if(depth[x] > depth[y])swap(x,y);
	if(w[x]!=w[y])ans = max(ans,ask(1,w[x]+1,w[y]));
	return ans;
}

int X[N],Y[N],val[N];

int main()
{
	int n=read();
	for(int i=1;i<n;++i)
	{
		X[i]=read(),Y[i]=read(),val[i]=read();
		add(X[i],Y[i]);
	}
	build(1,1,n);
	DFS1(1);
	DFS2(1,1);
	for(int i=1;i<=n;++i)
		Pchange(1,w[depth[X[i]]>depth[Y[i]]?X[i]:Y[i]],w[depth[X[i]]>depth[Y[i]]?X[i]:Y[i]],val[i]);
	char str[40];
	while(1)
	{
		scanf("%s",str);
		int x,y,tt;
		if(str[0]=='M')
		{
			scanf("%d%d",&x,&y);
			printf("%d\n",solveask(x,y));
		}
		else if(str[0]=='C')
		{	
			if(str[1]=='o')
			{
				scanf("%d%d%d",&x,&y,&tt);
				solvePchange(x,y,tt);
			}
			else
			{
				scanf("%d%d",&x,&y);
				Pchange(1,w[depth[X[x]]>depth[Y[x]]?X[x]:Y[x]],w[depth[X[x]]>depth[Y[x]]?X[x]:Y[x]],y);
			}
		}
		else if(str[0] =='A')
		{
			scanf("%d%d%d",&x,&y,&tt);
			solveAchange(x,y,tt);	
		}
		else
			break;
		
	}

}
