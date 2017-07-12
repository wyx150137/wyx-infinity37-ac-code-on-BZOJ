
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 5e5+5;
int l[N],r[N],del[N],a[N<<1],c,n,m;
ll s,now,ans,tmp;
struct E
{int next,to;};
struct Gragh
{
	E e[N<<1];
	int head[N],tot,d[N],f[N];
	void add(int x,int y)
	{
		e[++tot].to = y;
		e[tot].next = head[x];
		head[x] = tot;
		d[y]++;
		f[y] = x;
	}
}g,G;
void dfs(int x)
{
	if(!G.head[x])return ;
	for(int i = G.head[x];i;i=G.e[i].next)
		dfs(G.e[i].to);
	tmp = 1ll<<60;
	c = m = s = 0;
	for(int j = 0,i = G.head[x];i;i=G.e[i].next)
	{
		int to = G.e[i].to;
		a[m++]=l[to];
		a[m++]=r[to];
		c--;
		s+=l[to];
	}
	std::sort(a,a+m);
	for(int i = 0;i<m;i++)
	{
		c++;
		s-=a[i];
		now=s+1ll*a[i]*c;
		if(now<tmp)
			l[x]=a[i],tmp = now;
		if(now==tmp)
			r[x]=a[i];
	}
	ans+=tmp;
}
int q[N],h,t,ed;
int main()
{
	int o,u;
	scanf("%d%d",&n,&m);
	for(int i = 1;i< n;i++)
	{
		scanf("%d%d",&o,&u);
		g.add(o,u),g.add(u,o);
	}
	for(int i = 1;i<= m;i++)
		scanf("%d",&l[i]),r[i]=l[i];
	if(n==m)
	{
		for(int i = 1;i<= n;i++)
			for(int j = g.head[i];j;j=g.e[j].next)
			{
				int to = g.e[j].to;
				ans+=abs(l[i]-l[to]);
			}
		printf("%lld\n",ans>>1);
		return 0;
	}
	h = 1,t = 0;
	for(int i = 1;i<= m;i++)
		del[q[++t]=i]=1;
	int x=0;
	while(h<=t)
	{
		for(int i = h;i<= t;i++)
			for(int j = g.head[q[i]];j;j=g.e[j].next)
				if(!del[g.e[j].to])
				{
					int to = g.e[j].to;
					G.add(to,q[i]);
				}
		x = t;
		for(int i = h;i<= x;i++)
			for(int j = g.head[q[i]];j;j=g.e[j].next)
				if(!del[g.e[j].to])
				{
					int to = g.e[j].to;
					if((--g.d[to])<=1)
						del[q[++t]=to]=1;
				}
		h = x+1;
	}
	for(int i = 1;i<= n;i++)
		if(!G.f[i])
			G.add(0,i);
	dfs(0);
	printf("%lld\n",ans);
	return 0;
}
