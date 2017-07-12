
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<iostream>
#define maxn 30010
#define maxm 200010
#define inf 1000000000

using namespace std;

struct yts
{
	int l,r,num;
}a[20010];

int head[maxn],to[maxm],c[maxm],len[maxm],next[maxm],p[maxm],fr[maxn],dis[maxn],q[maxn];
bool vis[maxn];
int n,m,s,t,num,ans,cnt;

void addedge(int x,int y,int z,int w)
{
	num++;to[num]=y;c[num]=z;len[num]=w;p[num]=x;next[num]=head[x];head[x]=num;
	num++;to[num]=x;c[num]=0;len[num]=-w;p[num]=y;next[num]=head[y];head[y]=num;
}

void build(int i,int l,int r)
{
	a[i].l=l;a[i].r=r;a[i].num=++cnt;
	if (l==r)
	{
		addedge(a[i].num,t,1,0);
		return;
	}
	int mid=(l+r)/2;
	build(i*2,l,mid);build(i*2+1,mid+1,r);
	addedge(a[i].num,a[i*2].num,inf,0);
	addedge(a[i].num,a[i*2+1].num,inf,0);
}

void query(int i,int l,int r,int x)
{
	if (l<=a[i].l && a[i].r<=r)
	{
		addedge(x,a[i].num,1,0);
		return;
	}
	int mid=(a[i].l+a[i].r)/2;
	if (l<=mid) query(i*2,l,r,x);
	if (mid<r) query(i*2+1,l,r,x);
} 

bool spfa()
{
	for (int i=s;i<=t;i++) dis[i]=-inf;
	int l=0,r=1;
	q[1]=s;dis[s]=0;vis[s]=1;
	while (l!=r)
	{
		l++;if (l==maxn) l=0;
		int x=q[l];
		for (int p=head[x];p;p=next[p])
		  if (c[p] && dis[x]+len[p]>dis[to[p]])
		  {
		  	dis[to[p]]=dis[x]+len[p];
		  	fr[to[p]]=p;
		  	if (!vis[to[p]])
		  	{
		  		r++;if (r==maxn) r=0;
		  		q[r]=to[p];vis[to[p]]=1;
		  	}
		  }
		vis[x]=0;
	}
	if (dis[t]==-inf) return 0; else return 1;
}

void mcf()
{
	int x=inf;
	for (int i=fr[t];i;i=fr[p[i]]) x=min(x,c[i]);
	for (int i=fr[t];i;i=fr[p[i]]) ans+=x*len[i],c[i]-=x,c[i^1]+=x;
}

void costflow()
{
	while (spfa()) mcf();
}

int main()
{
	scanf("%d",&n);
	num=1;s=0,t=30000;
	build(1,1,5000);
	for (int i=1;i<=n;i++)
	{
		int l,r,x;
		scanf("%d%d%d",&l,&r,&x);
		r--;
		addedge(s,++cnt,1,x);
		query(1,l,r,cnt);
	}
	costflow();
	printf("%d\n",ans);
	return 0;
}
