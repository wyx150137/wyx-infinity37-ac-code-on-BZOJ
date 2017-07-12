
#include <stdio.h>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 105;
const int M = 1005;
const int mod = 31011;
struct E
{
	int u,v,l;
	bool operator<(const E &s)const
	{
		return l<s.l;
	}
}e[M];
int n,m;
int fa[N],U[N],vis[N];
int G[N][N],C[N][N];
vector<int>V[N];
int getfa(int x,int fa[])
{
	return fa[x]==x?x:fa[x]=getfa(fa[x],fa);
}
int gauss(int a[][N],int n)
{
	for(int i= 0;i<n;i++)
		for(int j = 0;j<n;j++)
			a[i][j]%=mod;
	int ans = 1;
	for(int i = 1;i<n;i++)
	{
		for(int j = i+1;j<n;j++)
			while(a[j][i])
			{
				int t = a[i][i]/a[j][i];
				for(int k = i;k<n;k++)
					a[i][k]=(a[i][k]-a[j][k]*t)%mod;
				for(int k = i;k<n;k++)
					swap(a[i][k],a[j][k]);
				ans = -ans;
			}
		if(a[i][i]==0)return 0;
		ans = ans*a[i][i]%mod;
	}
	if(ans<0)ans=-ans;
	return (ans+mod)%mod;
}
void solve()
{
	sort(e,e+m);
	for(int i = 1;i<= n;i++)fa[i]=i,vis[i]=0;
	int edge = -1,ans=1;
	for(int k = 0;k<= m;k++)
	{
		if(edge!=e[k].l||k==m)
		{
			for(int i = 1;i<= n;i++)
				if(vis[i])
				{
					int u = getfa(i,U);
					V[u].push_back(i);
					vis[i]=0;
				}
			for(int i = 1;i<= n;i++)
				if(V[i].size()>1)
				{
					for(int a = 1;a<=n;a++)
						for(int b = 1;b<=n;b++)
							C[a][b]=0;
					int len = V[i].size();
					for(int a = 0;a<len;a++)
						for(int b = a+1;b<len;b++)
						{
							int a1 = V[i][a],b1 = V[i][b];
							C[a][b] = (C[b][a]-=G[a1][b1]);
							C[a][a]+=G[a1][b1];
							C[b][b]+=G[a1][b1];
						}
					int tmp = gauss(C,len);
					ans = ans*tmp%mod;
					for(int a = 0;a<len;a++)
						fa[V[i][a]]=i;
				}
			for(int i = 1;i<= n;i++)
			{
				U[i] = fa[i] = getfa(i,fa);
				V[i].clear();
			}
			if(k==m)break;
			edge=e[k].l;
		}
		int a = e[k].u,b=e[k].v;
		int a1 = getfa(a,fa),b1=getfa(b,fa);
		if(a1==b1)continue;
		vis[a1]=vis[b1]=1;
		U[getfa(a1,U)]=getfa(b1,U);
		G[a1][b1]++;
		G[b1][a1]++;
	}
	bool flag = false;
	for(int i = 2;i<= n&&!flag;i++)
		if(U[i]!=U[i-1])
			flag = true;
	if(m==0)
		flag=1;
	printf("%d\n",flag?0:ans%mod);
}
int main()
{
	while(scanf("%d%d",&n,&m)!=EOF)
	{
		memset(G,0,sizeof(G));
		for(int i = 1;i<= n;i++)
			V[i].clear();
		for(int i = 0;i<m;i++)
			scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].l);
		solve();
	}
	return 0;
}
