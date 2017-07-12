
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 3e5+5;
typedef long long LL;
struct E
{int next,to;}e[N],k[N];
int head[N],tot;
void add(int x,int y)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	head[x] = tot;
}
int pos[N],Cnt,n,m,K;
void Add(int x,int y)
{
	k[++Cnt].to = y;
	k[Cnt].next = pos[x];
	pos[x] = Cnt;
}
struct A
{int l,r,mid;}ask[N];
LL c[N];
struct R
{int s,t,a;}rain[N];
void update(int x,int y)
{
	for(int i = x;i<N;i+=i&(-i))
		c[i]+=y;
}
LL getans(int x)
{
	LL ans = 0;
	for(int i = x;i>0;i-=i&(-i))
		ans+=c[i];
	return ans;
}
void UP(int i)
{
	if(rain[i].s>rain[i].t)
	{
		update(1,rain[i].a);update(rain[i].t+1,-rain[i].a);
		update(rain[i].s,rain[i].a);update(m+1,-rain[i].a);
	}else
		update(rain[i].s,rain[i].a),update(rain[i].t+1,-rain[i].a);
}
LL p[N];
void check()
{
	memset(c,0,sizeof(c));
	memset(head,0,sizeof(head));
	tot = 0;
	for(int i = 1;i<= n;i++)
	{
		ask[i].mid = (ask[i].l+ask[i].r)>>1;
		add(ask[i].mid,i);
	}
	for(int i = 1;i<= K;i++)
	{
		UP(i);
		for(int j = head[i];j;j = e[j].next)
		{
			LL ans = 0;
			for(int t = pos[e[j].to];t;t = k[t].next)
			{
				ans+=getans(k[t].to);
				if(ans>p[e[j].to])break;
			}
			if(ans<p[e[j].to])
				ask[e[j].to].l = ask[e[j].to].mid+1;
			else
				ask[e[j].to].r = ask[e[j].to].mid;
		}
	}
}
int main()
{
	//freopen("met.in","r",stdin);
	//freopen("met.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= m;i++)
	{
		int x;
		scanf("%d",&x);
		Add(x,i);
	}
	for(int i = 1;i<= n;i++)
		scanf("%lld",&p[i]);
	scanf("%d",&K);
	for(int i = 1;i<= K;i++)
		scanf("%d%d%d",&rain[i].s,&rain[i].t,&rain[i].a);
	for(int i = 1;i<= n;i++)
		ask[i].l = 1,ask[i].r = K+1;
	for(int i = 1;i<= 20;i++)
		check();
	for(int i = 1;i<= n;i++)
	{
		if(ask[i].mid<=K)
			printf("%d\n",ask[i].mid);
		else printf("NIE\n");
	}
	return 0;
}
