
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = 3e5+5;
int fa[N],dis[N];
struct EDGE
{int next,to;}e[N<<1];
int head[N],tot;
void add(int x,int y)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	head[x] = tot;
}
struct Fac
{
	LL c,a;
	void operator +=(const Fac &S)
		{c+=S.c;a+=S.a;}
	void operator -=(const Fac &S)
		{c-=S.c;a-=S.a;}
	void operator *=(int y)
		{c*=y,a*=y;}
}two_size[N],two_a[N];
void dfs(int x,int f)
{
	fa[x] = f;
	if(x!=1)dis[x] = dis[f]+1;
	for(int i = head[x];i;i = e[i].next)
		if(e[i].to!=f)
			dfs(e[i].to,x);
}
LL size[N],a[N],b[N];
int main()
{
	int n;
	scanf("%d",&n);
	int x,y;
	for(int i = 1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y),add(y,x);
	}
	for(int i = 1;i<= n;i++)
		scanf("%lld",&b[i]);
	dfs(1,0);
	for(int i = 2;i<= n;i++)
		two_size[i] = (Fac){b[fa[i]]-b[i],1};
	for(int i = 2;i<= n;i++)
	{
		two_a[i]+=two_size[i];
		for(int j = head[i];j;j = e[j].next)
			if(e[j].to!=fa[i])
				two_a[i]-=two_size[e[j].to];
	}
	Fac b1;
	b1.c = 0,b1.a = 0;
	for(int i = 2;i<= n;i++)
	{
		Fac tmp = two_a[i];
		tmp*=dis[i];
		b1+=tmp;
	}
	size[1] = (b[1]*2-b1.c)/b1.a;
	for(int i = 2;i<= n;i++)
		size[i] = (two_size[i].c+size[1])/2;
	for(int i = 1;i<= n;i++)
	{
		a[i]+=size[i];
		for(int j = head[i];j;j = e[j].next)
			if(e[j].to!=fa[i])
				a[i]-=size[e[j].to];
		printf("%lld",a[i]);
		if(i!=n)printf(" ");
	}
	return 0;
}
