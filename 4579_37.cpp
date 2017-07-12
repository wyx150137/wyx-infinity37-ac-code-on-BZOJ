
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 400005;
struct E
{int next,to;}e[N];
int head[N],tot,fa[N],ask[N],size[N];
void add(int x,int y)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	head[x] = tot;
}
bool ans[N],used[N];
int getfa(int x)
{
	if(fa[x]==x)return x;
	else return fa[x] = getfa(fa[x]);
}
void uni(int x,int y)
{
	x = getfa(x),y = getfa(y);
	if(x==y)return ;
	if(size[x]>size[y])
		fa[y] = x;
	else fa[x] = y; 
	size[x] = size[y] = size[x]+size[y];
}
int cnt = 0;
void solve(int x)
{
	for(int i = head[x];i;i = e[i].next)
		if(used[e[i].to])
			uni(e[i].to,x);
	used[x] = true;
	cnt++;
}
int main()
{
	int n,m,x,y;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= n;i++)size[fa[i] = i] = 1;
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y),add(y,x);
	}
	for(int i = 1;i<= n;i++)
		scanf("%d",&ask[i]);
	for(int i = n;i>=1;i--)
	{
		solve(ask[i]);
		if(size[getfa(ask[i])]==cnt)ans[i] =true;
		else ans[i] = false;
	}
	for(int i = 1;i<= n;i++)
	{
		if(ans[i])printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
