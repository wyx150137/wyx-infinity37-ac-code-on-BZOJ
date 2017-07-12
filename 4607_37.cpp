
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int INF = 0x3f3f3f3f;
const int N = 1e6+5;
const int M = 30;
int f[30][1<<13][3];
int cnt[M][M],deg[M],w[M][M],fa[M],d[M],g[M],id[M],n,c,m;
bool vis[M],del[M];
char a[N],b[N];
int getfa(int x)
{
	if(fa[x]==x)return fa[x]=x;
	else return fa[x]=getfa(fa[x]);
}
void Up(int &a,int b){a=a<b?a:b;}
int Cnt(int x)
{
	int cnt = 0;
	while(x)cnt++,x-=x&(-x);
	return cnt;
}
int main()
{
	scanf("%d%d",&n,&c);
	scanf("%s",a);scanf("%s",b);
	for(int i = 0;i<n;i++)
		cnt[a[i]-'a'][b[i]-'a']++,deg[a[i]-'a']++;
	for(int i = 0;i<26;i++)
		for(int j = 0;j<26;j++)
		{
			w[i][j] = deg[i]-cnt[i][j];
			if(i!=j)w[i][j]+=c;
		}
	for(int i = 0;i<26;i++)fa[i]=i,id[i]=-1;
	for(int i = 0;i<26;i++)
	{
		int k = 0;
		for(int j=0;j<26;j++)
			if(w[i][j]<w[i][k])k=j;
		d[g[i]=k]++;
		if(getfa(i)!=getfa(k))fa[fa[i]]=fa[k];
	}
	int ans = 0;
	for(int i = 0;i<26;i++)
		if(!del[getfa(i)])
		{
			del[fa[i]]=vis[i]=true;
			int j;
			for(j = g[i];!vis[j];j=g[j])vis[j]=true;
			if(g[j]==j)continue;id[j]=m;
			for(int k = g[j];k!=j;k=g[k])id[k]=m;
			m++;
		}
	if(!m)
	{
		for(int i = 0;i<26;i++)ans+=w[i][g[i]];
		printf("%d\n",ans);
		return 0;
	}
	int flag = 1;
	for(int i = 0;i<26;i++)
		if(d[i]!=1)flag = 0;
	for(int i = 0;i<= 26;i++)
		for(int S = 0;S < 1<<m;S++)
			for(int j = 0;j<2;j++)
				f[i][S][j]=INF;
	f[0][0][0]=0;
	for(int i = 0;i<26;i++)
		for(int S = 0;S< 1<<m;S++)
			for(int j = 0;j<2;j++)
				if(f[i][S][j]<INF)
				{
					for(int k = 0;k<26;k++)
					{
						int sta = S;
						if(~id[i] && k!=g[i])sta|=1<<id[i];
						if(~id[k] && (k!=g[i] || id[i]!=id[k] ))sta|=1<<id[k];
						Up(f[i+1][sta][j||k!=g[i]],f[i][S][j]+w[i][k]);
					}
				}
	ans = INF;
	for(int S = 0;S<1<<m;S++)
		for(int j = flag;j<2;j++)
			if(f[26][S][j]<INF)
				Up(ans,f[26][S][j]+(m-Cnt(S))*c);
	printf("%d\n",ans);
	return 0;
}
