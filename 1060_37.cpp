
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N =  500005;
LL f[N];
struct E{int to,next,val;}e[N*2];
int head[N],tot;
void add(int x,int y,int f)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	e[tot].val = f;
	head[x] = tot;
}
LL ans = 0;
void dfs(int x,int fa)
{
	for(int i = head[x];i;i = e[i].next)
		if(e[i].to!=fa)
		{
			dfs(e[i].to,x);
			f[x] = max(f[e[i].to]+e[i].val,f[x]);
		}
	for(int i = head[x];i;i = e[i].next)
		if(e[i].to!=fa)
		{
			ans += f[x]-f[e[i].to]-e[i].val;
		}	
}
int main()
{
	int n,x,y,z,s;
	scanf("%d%d",&n,&s);
	for(int i = 1;i<n;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		add(x,y,z);add(y,x,z);
	}
	dfs(s,0);
	printf("%lld",ans);
	return 0;
}
