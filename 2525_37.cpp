
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 300005;
struct E
{int next,to;}e[N<<1];
int head[N],tot;
void add(int x,int y)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	head[x] = tot;
}
int f[N],sta[N],cnt,ans,d[N],n,m;
void dfs(int x,int fa)
{
	int nf = -1,fw= d[x]-1;
	for(int i = head[x];i;i = e[i].next)
		if(e[i].to!=fa)
			dfs(e[i].to,x);
	for(int i = head[x];i;i = e[i].next)
		if(e[i].to!=fa)
		{
			if(sta[e[i].to]==0)
				nf = max(nf,f[e[i].to]-1);
			else if(sta[e[i].to]==1)
				fw = max(fw,f[e[i].to]+1);
		}
	if(nf<fw)
	{
		if(fw==ans)
		{
			cnt++;
			f[x] = ans;
			sta[x] = 0;
		}else
		{
			f[x] = fw;
			sta[x] = 1;
		}
	}else if(nf!=-1)
	{
		f[x] = nf;
		sta[x] = 0;
	}else
	{
		f[x] = 0;
		sta[x] = 2;
	}
}
int check()
{
	int l = 0,r = n+1;
	while(l<r)
	{
		ans = (l+r)>>1;
		memset(f,0,sizeof(f));
		memset(sta,-1,sizeof(sta));
		cnt = 0;
		dfs(1,0);
		if(sta[1]==1)cnt++;
		if(cnt>m)l = ans+1;
		else r = ans;
	}
	return l;
}
int main()
{
	int x,y;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= n;i++)
		scanf("%d",&d[i]);
	for(int i = 1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y),add(y,x);
	}
	printf("%d\n",check());
	return 0;
}
