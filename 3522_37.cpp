
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 5005;
typedef long long LL;
struct E
{int next,to;}e[N<<1];
int head[N],tot,tmp[N],g[N],f[N];
void add(int x,int y)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	head[x] = tot;
}
void dfs(int x,int fa,int dep)
{
	tmp[dep]++;
	for(int i = head[x];i;i = e[i].next)
		if(e[i].to!=fa)
			dfs(e[i].to,x,dep+1);
}
int main()
{
	int n,x,y;
	scanf("%d",&n);
	for(int i = 1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y),add(y,x);
	}
	LL ans = 0;
	for(int rt = 1;rt<= n;rt++)
	{
		memset(f,0,sizeof(f));
		memset(g,0,sizeof(g));
		for(int i = head[rt];i;i = e[i].next)
		{
			memset(tmp,0,sizeof(tmp));
			dfs(e[i].to,rt,1);	
			for(int j = 1;j<= n;j++)
			{
				ans+=(LL)g[j]*tmp[j];
				g[j]+=f[j]*tmp[j];
				f[j]+=tmp[j];
			}
		}
	}
	printf("%lld\n",ans);
	return 0;
}
