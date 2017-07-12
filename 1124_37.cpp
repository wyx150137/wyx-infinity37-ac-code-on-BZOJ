
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e6+5;
int degree[N],aim[N];
int ans1,ans2,n;
namespace Ans1
{
	int degree[N];
	bool vis[N],dead[N];
	void Solve()
	{
		static int q[N];
		int hd = 1,tl = 0;
		memcpy(degree,::degree,sizeof(degree));
		for(int i = 1;i<= n;i++)if(!degree[i])q[++tl]=i;
		while(hd<=tl)
		{
			int x = q[hd++];
			vis[x] = true;
			if(!dead[aim[x]])
			{
				dead[aim[x]] = vis[aim[x]] = true;ans1++;
				if(!--degree[aim[aim[x]]])
					q[++tl] = aim[aim[x]];
			}
		}
		for(int i =1;i<= n;i++)
			if(!vis[i])
			{
				int cnt = 0,x = i;
				while(!vis[x])
				{
					vis[x] = true;
					cnt++;
					x = aim[x];
				}
				ans1+=(cnt+1)>>1;
			}
	}
}
namespace Ans2
{
	struct E
	{int next,to;}e[N<<1];
	int head[N],tot;
	void add(int x,int y)
	{
		e[++tot].to = y;e[tot].next = head[x];head[x] = tot;
		e[++tot].to = x;e[tot].next = head[y];head[y] = tot;
	}
	bool vis[N];
	int stack[N],top;
	void bfs(int x)
	{
		static int q[N];
		int hd = 1,tl = 0;
		q[++tl] = x;vis[x] = true;
		while(hd<=tl)
		{
			int cur = q[hd++];
			stack[++top] = cur;
			for(int i = head[cur];i;i=e[i].next)
				if(!vis[e[i].to])
					vis[e[i].to]=true,q[++tl] = e[i].to;
		}
	}
	void Solve()
	{
		for(int i = 1;i<= n;i++)
			add(i,aim[i]);
		for(int i = 1;i<= n;i++)
			if(!vis[i])
			{
				top = 0;
				bfs(i);
				if(top==1)ans2++;
				else
				{
					int cnt = 0,size = top;
					while(top)
						cnt+=degree[stack[top--]]==0;
					ans2+=size-max(1,cnt);
				}
			}
	}
}
int main()
{
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
	{
		scanf("%d",&aim[i]);
		degree[aim[i]]++;
	}
	Ans1::Solve();
	Ans2::Solve();
	printf("%d %d\n",ans1,ans2);
	return 0;
}
