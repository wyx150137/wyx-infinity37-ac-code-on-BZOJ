
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 500000+5;
int c[N],cnt;
int in_w[N],out_w[N];
struct E{int next,to;}e[N];
int head[N],tot;
void add(int x,int y)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	head[x] = tot;
}
void dfs(int x,int fa)
{
	in_w[x] = ++cnt;
	for(int i = head[x];i;i = e[i].next)
		if(e[i].to!=fa)
			dfs(e[i].to,x);
	out_w[x] = ++cnt;
}
void update(int x,int dec)
{
	for(int i = x;i<=N;i +=(i&(-i)))
		c[i]+=dec;
	return ;
}
int getans(int x)
{
	int ans = 0;
	for(int i = x;i>0;i -= (i&(-i)))
		ans+=c[i];
	return ans;
}
int main()
{
	int n,m,x,y;
	scanf("%d",&n);
	for(int i = 1;i<n;i++)
		{scanf("%d%d",&x,&y);add(x,y);add(y,x);}
	dfs(1,0);
	for(int i = 1;i<= n;i++)
		{update(in_w[i],1);update(out_w[i],-1);}
	scanf("%d",&m);
	char ju[5];
	for(int i = 1;i<= n+m-1;i++)
	{
		scanf("%s",ju);
		if(ju[0]=='A')
		{
			scanf("%d%d",&x,&y);
			update(in_w[y],-1);update(out_w[y],1);
		}else
		{
			scanf("%d",&x);
			printf("%d\n",getans(in_w[x])-1);
		}
	}
	return 0;
}
