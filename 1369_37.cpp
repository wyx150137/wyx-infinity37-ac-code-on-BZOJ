
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 10005;
struct E
{
	int next,to;
}e[N<<1];
int head[N],tot;
void add(int x,int y)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	head[x] = tot;
}
int f[N][16];
void dp(int x,int fa)
{
	for(int i = head[x];i;i = e[i].next)
		if(e[i].to!=fa)
			dp(e[i].to,x);
	for(int t = 1;t<= 15;t++)
	{
		f[x][t] = t;
		for(int i = head[x];i;i = e[i].next)
		{
			if(fa==e[i].to)continue;
			int tmp = 0x3f3f3f3f;
			for(int k = 1;k<= 15;k++)
			{
				if(t==k)continue;
				tmp = min(tmp,f[e[i].to][k]);
			}
			f[x][t] = f[x][t]+tmp;
		}
	}
}
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
	dp(1,0);
	int ans = 0x3f3f3f3f;
	for(int i = 1;i<= 15;i++)
		ans = min(ans,f[1][i]);
	printf("%d\n",ans);
	return 0;
}
