
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 1e5+5;
const int mod = 2147483647;
int d[N];
int sum[N];
void update(int x,int y)
{
	for(int i = x;i<N;i+=i&(-i))
		d[i]+=y;
}
int getans(int x)
{
	int ans = 0;
	for(int i = x;i>0;i-=i&(-i))
		ans+=d[i];
	return ans;
}
struct P
{int x,y,l,r,u,d;}p[N];
bool cmp(const P &a,const P &b)
{
	return a.y<b.y||(a.y==b.y&&a.x<=b.x);
}
int fac[N],env[N];
int c[N][20];
void init()
{
	c[0][0] = 1;
	for(int i = 1;i<N;i++)
	{
		c[i][0]=1;
		for(int j=1;j<=10;j++)
			c[i][j]=c[i-1][j-1]+c[i-1][j];
	}
}
int id[N],X[N];
int find(int x)
{
	int l = 1,r = id[0]+1;
	while(l<r)
	{
		int mid = (l+r)>>1;
		if(id[mid]<x)l=mid+1;
		else r=mid;
	}
	return l;
}
int main()
{
	int n,m,w,k;
	init();
	scanf("%d%d%d",&n,&m,&w);
	for(int i = 1;i<= w;i++)
	{
		scanf("%d%d",&p[i].x,&p[i].y);
		X[i] = p[i].x;
	}
	scanf("%d",&k);
	sort(X+1,X+w+1);
	id[id[0]=1]=X[1];
	for(int i = 2;i<= w;i++)
		if(X[i]!=X[i-1])
			id[++id[0]]=X[i];
	sort(p+1,p+w+1,cmp);
	int tmp = 0;
	for(int i = 1;i<= w;i++)p[i].x=find(p[i].x);
	for(int i = 1;i<= w;i++)
	{
		if(p[i].y==p[i-1].y)tmp++;else tmp=1;
		p[i].l=tmp;
		sum[p[i].x]++;
		p[i].u=sum[p[i].x];
	}
	tmp = 0;
	for(int i = w;i>=1;i--)
	{
		if(p[i].y==p[i+1].y)tmp++;else tmp=1;
		p[i].r=tmp;
		p[i].d=sum[p[i].x]-p[i].u;
	}
	int ans = 0;
	for(int i = 1;i<= w;i++)
	{
		update(p[i].x,c[p[i].u][k]*c[p[i].d][k]-getans(p[i].x)+getans(p[i].x-1));
		if(i>1&&p[i].y==p[i-1].y)
			ans+=c[p[i-1].l][k]*c[p[i].r][k]*(getans(p[i].x-1)-getans(p[i-1].x));
	}
	printf("%d\n",ans&mod);
	return 0;
}
