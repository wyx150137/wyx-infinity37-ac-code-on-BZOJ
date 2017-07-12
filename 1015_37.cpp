
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 400005;
struct E
{int next,to;}e[N];
int head[N],tot,T;
int fa[N];
bool used[N];
void add_e(int x,int y)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	head[x] = tot;

	e[++tot].to = x;
	e[tot].next = head[y];
	head[y] = tot;
}
int getfa(int x)
{
	if(fa[x]==x||!fa[x])
		return fa[x] = x;
	else return fa[x] = getfa(fa[x]);
}
void add_p(int x)
{
	int root = getfa(x);
	for(int i = head[x];i;i = e[i].next)
	{
		int q= getfa(e[i].to);
		if(used[e[i].to]&&q!=root){fa[q] = root;T--;}
	}
	return ;
}
int ask[N],ans[N],b[N];
int main()
{
	int n,m,x,y;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d",&x,&y);
		x++;y++;
		add_e(x,y);
	}
	int k;
	scanf("%d",&k);
	for(int i = 1;i<= k;i++)
	{
		scanf("%d",&ask[i]);
		ask[i]++;
		b[ask[i]] = 1;
	}
	for(int i = 1;i<= n;i++)
		if(b[i]==0)
		{
			T++;
			add_p(i);
			used[i] = true;
		}
	ans[k] = T;
	for(int i = k;i>=1;i--)
	{
		T++;
		add_p(ask[i]);
		used[ask[i]] =true;
		ans[i-1] = T;
	}
	for(int i = 0;i<= k;i++)
		printf("%d\n",ans[i]);
	return 0;
}
