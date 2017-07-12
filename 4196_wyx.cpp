
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define N 100000+5
#define M 400000+5
#define inf 0x7fffff
using namespace std;
int head[N],w[N],size[N],sz;
int top[N],fa[N],depth[N];
int last[N];
inline int read()
{
	int x = 0, f = 1; char ch = getchar();
	while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
	while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
	return x * f;
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
	edge[++cnt]=graph(head[x],y);
	head[x]=cnt;
	edge[++cnt]=graph(head[y],x);
	head[y]=cnt;
}
void DFS1(int x)
{
	size[x]=1;
	for(int i=head[x];i;i=edge[i].next)
	{
		if(edge[i].to!=fa[x])
		{
			fa[edge[i].to]=x;
			DFS1(edge[i].to);
			size[x]+=size[edge[i].to];
		}
	}
}
void DFS2(int x,int chain)
{
	last[x]=w[x]=++sz;
	top[x]=chain;
	int k = 0;
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to!=fa[x]&&size[k]<size[edge[i].to])
			k=edge[i].to;
	if(!k)return;
	DFS2(k,chain);last[x]=max(last[x],last[k]);
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to!=fa[x]&&edge[i].to!=k)
			DFS2(edge[i].to,edge[i].to),last[x]=max(last[x],last[edge[i].to]);
	return;
}
struct seg
{
	int l,r,mn,lazy;
}tr[M];
void build(int k,int l,int r)
{
	tr[k].l=l,tr[k].r=r,tr[k].lazy=inf;
	if(l==r)return;
	int mid =(l+r)>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
}
void updata(int k)
{
	tr[k].mn = tr[k<<1].mn + tr[k<<1|1].mn;
}
void down(int k)
{
	int tmp=tr[k].lazy;
	tr[k].lazy = inf;
	if(tmp==inf || tr[k].l==tr[k].r)return;
	tr[k<<1].lazy=tr[k<<1|1].lazy=tmp;
	tr[k<<1].mn=(tr[k<<1].r-tr[k<<1].l+1)*tmp;
	tr[k<<1|1].mn=(tr[k<<1|1].r-tr[k<<1|1].l+1)*tmp;
	return;
}
void change(int k,int l,int r,int c)
{
	down(k);
	if(l==tr[k].l && r==tr[k].r)
	{
		tr[k].mn = (r-l+1)*c;
		tr[k].lazy = c;
		return;
	}
	int mid =(tr[k].l+tr[k].r)>>1;
	if(r<=mid)change(k<<1,l,r,c);
	else if(l>mid)change(k<<1|1,l,r,c);
	else change(k<<1,l,mid,c),change(k<<1|1,mid+1,r,c);
	updata(k);
}
void solvechange(int x)
{
	while(top[x]!=1){
		change(1,w[top[x]],w[x],1);
		x=fa[top[x]];
		//cout<<x<<endl;
	}
	change(1,w[top[x]],w[x],1);
}
int main()
{
	int n;
	cin>>n;
	for(int i=2;i<=n;++i)
	{
		int tx=read()+1;
		add(tx,i);
	}
	DFS1(1);
	DFS2(1,1);
	build(1,1,n);
	int test = read();
	//for(int i=1;i<=n;++i)
	//	cout<<top[i]<<" "<<fa[i]<<" "<<size[i]<<endl;
	//cout<<size[0];
	//return 0;
	while(test --)
	{
		int ans = tr[1].mn;
		//cout<<ans<<endl;
		char str[40];
		scanf("%s",str);
		int tt=read();
		//cout<<tt<<endl;
		tt++;
		if(str[0]=='i')
			solvechange(tt);
		else
			change(1,w[tt],last[tt],0);
		printf("%d\n",abs(tr[1].mn-ans));
	}
}
