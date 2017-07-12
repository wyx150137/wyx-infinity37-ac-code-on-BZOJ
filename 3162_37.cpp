
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int mod = 1e9+7;
const int sed = 377;
const int N = 5e5+5;
struct E
{
	int next,to;
}e[N<<1];
int head[N],tot=1,n,rot,cgs[2];
void add(int x,int y)
{
	e[++tot].to = y;e[tot].next = head[x];head[x] = tot;
	//e[++tot].to = x;e[tot].next = head[y];head[y] = tot;
}
int size[N],stack[N];
ull hash[N];
ll f[N][2],inv[N];
void Init()
{
	inv[1] = 1;
	for(int i = 2;i<= n;i++)
		inv[i] = (ll)(mod-mod/i)*inv[mod%i]%mod;
}
ll C(ll n,ll m)
{
	ll res = 1;
	n%=mod;
	for(int i = 1;i<= m;i++)
		(res*=(ll)(n-i+1)*inv[i]%mod)%=mod;
	return res;
}
bool cmp(int x,int y)
{
	return hash[x]<hash[y];
}
void dfs(int x,int fa)
{
	bool flag = true;
	size[x] = 1;
	for(int i = head[x];i;i=e[i].next)if(e[i].to!=fa)
	{
		dfs(e[i].to,x);
		size[x]+=size[e[i].to];
		if(size[e[i].to]<<1>n)
			flag = false;
	}
	if((n-size[x])<<1>n)
		flag = false;
	if(flag)
		(cgs[0]?cgs[1]:cgs[0])=x;
}
void DP(int x,int fa)
{
	for(int i = head[x];i;i=e[i].next)
		if(e[i].to!=fa)
			DP(e[i].to,x);
	int top = 0;
	for(int i = head[x];i;i=e[i].next)
		if(e[i].to!=fa)
			stack[++top] = e[i].to;
	sort(stack+1,stack+top+1,cmp);
	hash[x] = sed;
	f[x][0]=f[x][1]=1;
	int j;
	for(int i = 1;i<= top;i=j)
	{
		for(j = i+1;j<=top&&hash[stack[i]]==hash[stack[j]];j++);
		(f[x][0]*=C(j-i+f[stack[i]][0]+f[stack[i]][1]-1,j-i))%=mod,
		(f[x][1]*=C(j-i+f[stack[i]][0]-1,j-i))%=mod;
	}
	for(int i = 1;i<= top;i++)
	{
		hash[x] = hash[x]*sed+hash[stack[i]];
		hash[x] = (hash[x]^hash[stack[i]])+hash[stack[i]];
	}
}
int main()
{
	scanf("%d",&n);
	Init();
	int x,y;
	for(int i = 1;i< n;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
	}
	dfs(1,0);
	if(cgs[1])
	{
		for(int i = head[cgs[0]];i;i=e[i].next)
			if(e[i].to==cgs[1])
			{
				e[i].to = e[i^1].to = rot = n+1;
				break;
			}
		add(n+1,cgs[0]);
		add(n+1,cgs[1]);
	}else rot = cgs[0];
	DP(rot,0);
	ll ans = 0;
	if(!cgs[1])
		ans = (f[rot][0]+f[rot][1])%mod;
	else
	{
		x=cgs[0];y=cgs[1];
        if(hash[x]!=hash[y])
            ans=(f[x][0]*f[y][0]%mod+f[x][1]*f[y][0]%mod+f[x][0]*f[y][1]%mod)%mod;
        else
            ans=(f[x][0]*f[y][1]+C(f[x][0]+1,2) )%mod;
	}
	printf("%lld\n",ans);
	return 0;
}
