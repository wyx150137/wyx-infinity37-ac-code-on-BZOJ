
#include <stdio.h>
#include <map>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 1e5+5;
const int P = N*25;
const int M = P*4;
const int bas = 2e9;
struct E
{int next,to;}e[M];
struct P
{int x,y,lev;}p[P];
int head[P],tot=1;
void add(int x,int y)
{
	e[++tot].to = y;e[tot].next = head[x];head[x] = tot;
	e[++tot].to = x;e[tot].next = head[y];head[y] = tot;
}
map<ll,int>pos;
int dfn[P],low[P],Dfn,cnt;
bool flag;
void tarjan(int x)
{
	dfn[x] = low[x] = ++Dfn;
	int son = 0;
	for(int i = head[x];i;i=e[i].next)
		if(p[e[i].to].lev)
		{
			if(!dfn[e[i].to])
			{
				son++;
				tarjan(e[i].to);
				low[x] = min(low[x],low[e[i].to]);
				if(p[x].lev==2)continue;
				if(dfn[x]==1&&son>=2)flag = true;
				if(dfn[x]!=1&&dfn[x]<=low[e[i].to])flag = true;
			}else
				low[x] = min(low[x],dfn[e[i].to]);
		}
}
bool vis[P];int vt;
void dfs(int x)
{
	vis[x] = true;
	if(p[x].lev)vt++;
	for(int i = head[x];i;i=e[i].next)if(!vis[e[i].to])dfs(e[i].to);
}
int main()
{
	int cas;
	scanf("%d",&cas);
	while(cas--)
	{
		for(int i = 0;i<= cnt;i++)head[i]=dfn[i]=low[i]=vis[i]=0;tot=1;
		pos.clear();
		int n,m,c,tmp;cnt = 0;
		bool ans0=false;
		ll x,y;
		scanf("%d%d%d",&n,&m,&c);
		for(int i = 1;i<= c;i++)
		{
			scanf("%lld%lld",&x,&y);
			pos[x*bas+y]=i;
			p[i].x = x,p[i].y = y;p[i].lev = 0;
		}
		cnt = c;
		if(1ll*n*m-c<=1){puts("-1");continue;}
   		if(1ll*n*m==2&&!c){puts("-1");continue;}
		for(int i = 1;i<= c;i++)
			for(int nx = max(1,p[i].x-1);nx<=min(n,p[i].x+1);nx++)
				for(int ny = max(1,p[i].y-1);ny<=min(m,p[i].y+1);ny++)
				{
					if(pos[(ll)nx*bas+ny])continue;
					p[++cnt].x = nx,p[cnt].y = ny;p[cnt].lev = 1;
					pos[(ll)nx*bas+ny]=cnt;
				}
		for(int i = 1;i<= c;i++)
			for(int nx = max(1,p[i].x-2);nx<=min(n,p[i].x+2);nx++)
				for(int ny = max(1,p[i].y-2);ny<=min(m,p[i].y+2);ny++)
				{
					if(pos[(ll)nx*bas+ny])continue;
					p[++cnt].x = nx,p[cnt].y = ny;p[cnt].lev = 2;
					pos[(ll)nx*bas+ny]=cnt;
				}
		for(int i = 1;i<= cnt;i++)
		{
			if((tmp=pos[((ll)(p[i].x+1)*bas+p[i].y)]))
				add(i,tmp);
			if((tmp=pos[((ll)p[i].x*bas+p[i].y+1)]))
				add(i,tmp);
		}
		flag = false;
		for(int i = c+1;i<= cnt;i++)
		{
			if(vis[i])continue;
			vt = 0;dfs(i);
			Dfn = 0;tarjan(i);
			if(Dfn!=vt){ans0=true;break;}
		}
		if(ans0){puts("0");continue;}
		if(1ll*n*m-c==2&&Dfn==2){puts("-1");continue;}
    	if(n==1||m==1){puts("1");continue;}
    	if(flag){puts("1");continue;}
    	puts("2");
	}
	return 0;
}
