
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = 1e5+5;
struct E
{int next,to,val;}e[N<<1];
int head[N],tot;
void add(int x,int y,int f)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	e[tot].val = f;
	head[x] = tot;
}
int sum,root,f[N],size[N],n;
bool used[N];
void get_root(int x,int fa)
{
	size[x] = 1;
	f[x] = 0;
	for(int i = head[x];i;i = e[i].next)
	{
		if(e[i].to==fa||used[e[i].to])continue;
		get_root(e[i].to,x);
		size[x]+=size[e[i].to];
		f[x] = max(f[x],size[e[i].to]);
	}
	f[x] =max(f[x],sum-size[x]);
	if(f[x]<f[root])root = x;
}
int G[N<<1][2],F[N<<1][2],t[N<<1];
int maxdep;
void get_sum(int x,int fa,int num,int dep)
{
	maxdep = max(maxdep,dep);
	if(t[num])G[num][1]++;
	else G[num][0]++;
	t[num]++;
	for(int i = head[x];i;i = e[i].next)
		if(e[i].to!=fa&&!used[e[i].to])
			get_sum(e[i].to,x,num+e[i].val,dep+1);
	t[num]--;
}
LL ans;
void calc(int x)
{
	F[n][0] = 1;
	int mx = 0;
	for(int i = head[x];i;i = e[i].next)
		if(!used[e[i].to])
		{
			maxdep = 0;
			get_sum(e[i].to,x,n+e[i].val,1);
			mx = max(mx,maxdep);
			ans+=(F[n][0]-1)*G[n][0];
			for(int j = -maxdep;j<= maxdep;j++)
			{
				ans+=(LL)F[n-j][0]*G[n+j][1];
				ans+=(LL)F[n-j][1]*G[n+j][0];
				ans+=(LL)F[n-j][1]*G[n+j][1];
			}
			for(int j = n-maxdep;j<= n+maxdep;j++)
				{F[j][0]+=G[j][0],F[j][1]+=G[j][1];G[j][0] = G[j][1] = 0;}
		}
	for(int i = n-mx;i<= n+mx;i++)
		F[i][0] = F[i][1] = 0;
}
void work(int x)
{
	calc(x);
	used[x] = true;
	for(int i = head[x];i;i=e[i].next)
	{
		if(used[e[i].to])continue;
		sum = size[e[i].to];
		root = 0;
		get_root(e[i].to,0);
		work(root);
	}
}
int main()
{
	int x,y,z;
	scanf("%d",&n);
	for(int i = 1;i<n;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		if(!z)z = -1;
		add(x,y,z),add(y,x,z);
	}
	f[0] = 0x3f3f3f3f;
	root = 0;sum = n;
	get_root(1,0);
	work(1);
	printf("%lld\n",ans);
	return 0;
}
