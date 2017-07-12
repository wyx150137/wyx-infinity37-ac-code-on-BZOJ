
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N =300005;
typedef long long LL;
struct E
{int next,to;}e[N<<1];
int head[N],tot;
LL f[N];
bool is_leaf[N];
void add(int x,int y)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	head[x] = tot;
}
int ans;
void dfs(int x,int fa)
{
	is_leaf[x] = true;
	for(int i = head[x];i;i = e[i].next)
		if(e[i].to!=fa)
		{
			is_leaf[x] = false;
			dfs(e[i].to,x);
			f[x]+=f[e[i].to]+1;
		}
	f[x]-=ans;
	f[x] = max(f[x],(LL)0);
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
	int l = 0,r = n-1;
	while(l<r)
	{
		ans = (l+r)>>1;
		memset(f,0,sizeof(f));
		dfs(1,0);
		if(f[1]!=0)l = ans+1;
		else r = ans;
	}
	printf("%d\n",l);
	return 0;
}
