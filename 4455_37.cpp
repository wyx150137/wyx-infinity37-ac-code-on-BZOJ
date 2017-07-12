
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 20;
int mp[N][N],fa[N],n,m;
bool islf[N];
ll f[N][N];
struct E
{int next,to;}e[N*N];
int head[N],tot;
void add(int x,int y)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	head[x] = tot;
}
int p[N],q[N];
void dfs(int s)
{
	q[1] = s;
	int l = 1,r = 1;
	while(l<=r)
	{
		int x = q[l++];
		islf[x] = true;
		for(int i = head[x];i;i=e[i].next)
			if(e[i].to!=fa[x])
			{
				fa[e[i].to] = x;
				islf[x] = false;
				q[++r] = e[i].to;
			}
	}
}
int get_point(int x)
{
	int j = 0,cnt = 0;
	while(x)
	{
		j++;
		if(x&1)p[++cnt] = j;
		x>>=1;
	}
	return cnt;
}
void dp(int cnt)
{
	for(int i = n;i>= 1;i--)
	{
		int x = q[i];
		if(islf[x])continue;
		for(int j = 1;j<= cnt;j++)
		{
			for(int o = head[x];o;o=e[o].next)
			{
				ll num = 0;int to = e[o].to;
				if(fa[to]!=x)continue;
				for(int k = 1;k<= cnt;k++)
					if(mp[p[j]][p[k]])
						num+=f[to][k];
				f[x][j]*=num;
			}
		}
	}
}
int main()
{
	int x,y;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= n;i++)mp[i][i]=1;
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d",&x,&y);
		mp[x][y] = mp[y][x] = 1;
	}
	for(int i = 1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y),add(y,x);
	}
	dfs(1);
	ll ans = 0;int tmp = n%2;
	for(int i = 0;i<(1<<n);i++)
	{
		int cnt = get_point(i);
		int flag = (cnt%2==tmp)?1:-1;
		ll tans = 0;
		for(int j = 1;j<= n;j++)
			for(int k =1;k<= cnt;k++)
				f[j][k] = 1;
		dp(cnt);
		for(int j = 1;j<= cnt;j++)tans+=f[1][j];
		ans+=(ll)flag*tans;
	}
	printf("%lld\n",ans);
	return 0;
}
