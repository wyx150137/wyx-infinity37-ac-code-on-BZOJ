
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int N = 400020;
struct yts { int x,t,ne;} e[N];
struct PP { int l,r,id;} p[N];
int head[N],dep[N],st[N],ans[N],w;
int m,num;
 
bool cmp(PP a,PP b) { return a.l<b.l;}
void put(int x,int y)
{
	num++; e[num].x=x; e[num].t=y;
	e[num].ne=head[x]; head[x]=num;
}
 
void dfs(int x,int h)
{
	st[++w]=x;
	if (p[x].id!=-1)
	{
		while (h<w&&p[st[h+1]].r>=p[x].l+m) h++;
		ans[p[x].id]=dep[x]-dep[st[h]]+1;
	}
	for (int i=head[x];i;i=e[i].ne)
	{
		int y=e[i].t;
		dep[y]=dep[x]+1;
		dfs(y,h);
	}
	w--;
}
 
int main()
{
	int n;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
	{
		int l,r;
		scanf("%d%d",&l,&r);
		if (r<l) r+=m;
		p[i]=(PP){l,r,i}; p[i+n]=(PP){l+m,r+m,-1};
	}
	n<<=1;
	sort(p+1,p+n+1,cmp);
	int now=1;
	for (int i=1;i<n;i++)
	{
		while (now<n&&p[now+1].l<=p[i].r) now++;
		put(now,i);
	}
	n>>=1;
	dep[2*n]=1; dfs(2*n,1);
	for (int i=1;i<=n;i++) printf("%d ",ans[i]);
	printf("\n");
	return 0;
}
