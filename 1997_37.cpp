
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 2005;
const int M = 2e6+5;
struct E
{int next,to;}e[M];
int head[N],tot,c[N],pos[N],u[10005],v[10005];
inline void add(int x,int y)
{e[++tot].to = y;e[tot].next = head[x];head[x] = tot;}
int dfn[N],Dfn,low[N],bel[N],stack[N],top,dcc;
bool ins[N];
void tarjan(int x)
{
	dfn[x] = low[x] = ++Dfn;
	stack[++top] = x;
	ins[x] = true;
	for(int i = head[x];i;i=e[i].next)
	{
		if(!dfn[e[i].to])
		{
			tarjan(e[i].to);
			low[x] = min(low[x],low[e[i].to]);
		}else if(ins[e[i].to])
			low[x] = min(low[x],dfn[e[i].to]);
	}
	if(dfn[x]==low[x])
	{
		dcc++;
		int tmp;
		do
		{
			tmp = stack[top--];
			ins[tmp] = false;
			bel[tmp] = dcc;
		}while(tmp!=x);
	}
}
void init()
{
	memset(head,0,sizeof(head));
	memset(low,0,sizeof(low));
	memset(dfn,0,sizeof(dfn));
	tot = Dfn = dcc = top = 0;
}
struct data
{
	int l,r;
	data(int _l=0,int _r=0):l(_l),r(_r){}
}qj[N];
int main()
{
	int cas;
	scanf("%d",&cas);
	while(cas--)
	{
		int n,m;
		scanf("%d%d",&n,&m);
		init();
		for(int i = 1;i<= m;i++)scanf("%d%d",&u[i],&v[i]);
		for(int i = 1;i<= n;i++)scanf("%d",&c[i]);
		for(int i = 1;i<= n;i++)pos[c[i]] = i;
		if(m>3*n-6){puts("NO");continue;}
		int cnt = 0,x,y;
		for(int i = 1;i<= m;i++)
		{
			x = pos[u[i]],y = pos[v[i]];
			if(x>y)swap(x,y);
			if(y-x==1||(x==1&&y==n))continue;
			qj[++cnt] = data(x,y);
		}
		m = cnt;
		for(int i = 1;i<= m;i++)
			for(int j = i+1;j<= m;j++)
				if((qj[i].l<qj[j].l&&qj[j].l<qj[i].r&&qj[i].r<qj[j].r)||
					(qj[j].l<qj[i].l&&qj[i].l<qj[j].r&&qj[j].r<qj[i].r))
				{
					add(i<<1,j<<1|1);
					add(i<<1|1,j<<1);
					add(j<<1,i<<1|1);
					add(j<<1|1,i<<1);
				}
		for(int i = 2;i<= (m<<1|1);i++)
			if(!dfn[i])tarjan(i);
		bool flag = true;
		for(int i = 1;i<= m&&flag;i++)
			if(bel[i<<1]==bel[i<<1|1])flag = false;
		if(flag)puts("YES");
		else puts("NO");
	}
	return 0;
}
