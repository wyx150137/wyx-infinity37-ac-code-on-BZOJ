
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 2e5+5;
const ll INF = 1ll<<62;
ll n;
char s[N];
struct Matrix
{
	ll d[4][4];
	Matrix()
	{
		memset(d,0,sizeof(d));
	}
	Matrix(bool flag)
	{
		memset(d,0,sizeof(d));
		for(int i = 0;i<4;i++)d[i][i]=1;
	}
	void operator *=(const Matrix &s)
	{
		Matrix res;
		for(int i = 0;i<4;i++)for(int j  =0;j<4;j++)
		{
			res.d[i][j] = INF;
			for(int k = 0;k<4;k++)
				res.d[i][j] = min(res.d[i][j],d[i][k]+s.d[k][j]);
		}
		*this = res;
	}
	friend Matrix quick_pow(Matrix s,ll d)
	{
		Matrix res(true);
		while(d)
		{
			if(d&1)res*=s;
			s*=s;
			d>>=1;
		}
		return res;
	}
};
struct SAM
{
	int trs[N][4],fa[N],len[N];
	int cnt,last;
	void init(){cnt=last=1;}
	void insert(int x)
	{
		int p,newp,q,newq;
		p = last,newp = ++cnt;
		last = newp,len[newp] = len[p]+1;
		for(;p&&!trs[p][x];p=fa[p])trs[p][x] = newp;
		if(!p)fa[newp] = 1;
		else
		{
			q = trs[p][x];
			if(len[q]==len[p]+1)fa[newp] = q;
			else
			{
				newq = ++cnt;
				fa[newq] = fa[q];
				len[newq] = len[p]+1;
				memcpy(trs[newq],trs[q],sizeof(trs[q]));
				fa[newp] = fa[q] = newq;
				for(;p&&trs[p][x]==q;p=fa[p])trs[p][x] = newq;
			}
		}
	}
	ll mn[N][4];
	bool vis[N];
	void dfs(int x)
	{
		vis[x] = true;
		for(int i = 0;i<4;i++)
		{
			if(!vis[trs[x][i]])dfs(trs[x][i]);
			if(trs[x][i])mn[x][i] = INF;
			else mn[x][i]=1;
		}
		for(int i = 0;i<4;i++)if(trs[x][i])
			for(int j = 0;j<4;j++)
				mn[x][j] = min(mn[x][j],mn[trs[x][i]][j]+1);
	}	
}sam;
Matrix go;
bool check(ll x)
{
	Matrix ans = quick_pow(go,x);
	for(int i= 0;i<4;i++)
		for(int j = 0;j<4;j++)
			if(ans.d[i][j]+1<=n)return true;
	return false;
}
int main()
{
	scanf("%lld",&n);
	scanf("%s",s+1);
	sam.init();
	sam.vis[0] = true;
	for(int i = 1;s[i];i++)
		sam.insert(s[i]-'A');
	sam.dfs(1);
	for(int i = 0;i<4;i++)
		for(int j = 0;j<4;j++)
			go.d[i][j] = sam.mn[sam.trs[1][i]][j];
	ll l = 0,r = n+1,ans=0;
	while(l<=r)
	{
		ll mid = (l+r)>>1;
		if(check(mid))l=mid+1;
		else r = mid-1,ans = mid;
	}
	printf("%lld\n",ans);
	return 0;
}
