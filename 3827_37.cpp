
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1000005;
const int INF = 0x3f3f3f3f;
int dis[N],nxt[N<<1],dep[N<<1];
int n,s;
int work(int x)
{
	int fa = x;
	for(;fa<x+n;fa = nxt[fa]);
	for(int i = nxt[x],j = x;i!=fa;j = i,i = nxt[i])nxt[j] = fa;
	return dep[x]-dep[fa];
}
int main()
{
	scanf("%d%d",&n,&s);
	int max_d = 0;
	for(int i = 1;i<= n;i++)
	{
		scanf("%d",&dis[i]);
		max_d = max(max_d,dis[i]);
	}
	while(s--)
	{
		int d;
		scanf("%d",&d);
		if(d<max_d){printf("NIE\n");continue;}
		int j = 1,sum = 0;
		int end = n<<1;
		for(int i = 1;i<= end;i++)
		{
			while(j<end&&sum+dis[j>n?j-n:j]<=d)
			{
				sum = sum+dis[j>n?j-n:j];
				j++;
			}
			sum-=dis[i>n?i-n:i];
			nxt[i] = j;
		}
		dep[end] = 0;
		for(int i = end;i>=1;i--)
			dep[i] = dep[nxt[i]]+1;
		int ans = INF;
		for(int i = 1;i<= n;i++)ans = min(ans,work(i));
		printf("%d\n",ans);
	}
	return 0;
}
