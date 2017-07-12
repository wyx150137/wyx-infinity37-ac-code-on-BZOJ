
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = 2e4+5;
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
bool used[N];
int sum,root,size[N],f[N];
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
	f[x] = max(f[x],sum-size[x]);
	if(f[x]<f[root])root = x;
}
int dep[N];
LL cnt[4];
void get_dep(int x,int fa)
{
	cnt[dep[x]]++;
	for(int i = head[x];i;i = e[i].next)
	{
		if(e[i].to==fa||used[e[i].to])continue;
		dep[e[i].to] = (dep[x]+e[i].val)%3;
		get_dep(e[i].to,x);
	}
}
LL cal(int x,int now)
{
	dep[x] = now%3;
	cnt[1] = cnt[0] = cnt[2] = 0;
	get_dep(x,0);
	return cnt[1]*cnt[2]*2+cnt[0]*cnt[0];
}
LL ans;
void work(int x)
{
	ans+=cal(x,0);
	used[x] = true;
	for(int i = head[x];i;i = e[i].next)
	{
		if(used[e[i].to])continue;
		ans-=cal(e[i].to,e[i].val);
		sum = size[e[i].to];
		root = 0;
		get_root(e[i].to,0);
		work(root);
	}
}
LL gcd(LL a,LL b)
{
	if(b==0)return a;
	return gcd(b,a%b);
}
int main()
{
	int n;
	scanf("%d",&n);
	int x,y,z;
	for(int i = 1;i<n;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		add(x,y,z),add(y,x,z);
	}
	f[0] = 0x3f3f3f3f;
	sum = n;
	get_root(1,0);
	work(root);
	LL t = gcd(ans,(LL)n*n);
	printf("%lld/%lld\n",ans/t,n*n/t);
	return 0;
}
