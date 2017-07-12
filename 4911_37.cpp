
#include <stdio.h>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 3e4+5;
const int mxK = 130;
const int mod = 10007;
const int inv2 = (mod+1)>>1;

inline void FWT(int *a,int n,int type)
{
	for(int i = 1;i<n;i<<=1)
		for(int j = 0;j<n;j+=(i<<1))
			for(int k = 0;k<i;k++)
			{
				int x = a[j+k],y = a[j+k+i];
				a[j+k] = (x+y)%mod;
				a[j+k+i] = (x-y+mod)%mod;
				if(!type)(a[j+k]*=inv2)%=mod,(a[j+k+i]*=inv2)%=mod;
			}
}
int quick_pow(int x,int y)
{int res=1;while(y){if(y&1)res=res*x%mod;x=x*x%mod;y>>=1;}return res;}
int K,kx[mxK][mxK];
int inv[mod];
void pre(int n)
{
	for(int i = 0;i<n;i++)
		kx[i][i]=1,FWT(kx[i],n,1);
	for(int i = 1;i<mod;i++)inv[i]=quick_pow(i,mod-2);
}
struct E
{int next,to;}e[N<<1];
int head[N],tot;
void add(int x,int y)
{
	e[++tot].to = y;e[tot].next = head[x];head[x] = tot;
	e[++tot].to = x;e[tot].next = head[y];head[y] = tot;
}
int fa[N],size[N],top[N];
int dep[N],son[N];
vector<int>P[N];
void dfs1(int x)
{
	size[x] = 1;dep[x] = dep[fa[x]]+1;
	for(int i = head[x];i;i=e[i].next)
		if(e[i].to!=fa[x])
		{
			fa[e[i].to] = x;
			dfs1(e[i].to);
			size[x]+=size[e[i].to];
			if(size[e[i].to]>size[son[x]])son[x] = e[i].to;
		}
}
void dfs2(int x,int tp)
{
	P[tp].push_back(x);
	top[x] = tp;
	if(son[x])dfs2(son[x],tp);
	for(int i = head[x];i;i=e[i].next)
		if(e[i].to!=fa[x]&&e[i].to!=son[x])
			dfs2(e[i].to,e[i].to);
}
struct data
{
	int x,y;
	data(int num=0)
	{
		if(num)x=num,y=0;
		else x=y=1;
	}
	int val(){return y?0:x;}
	data & operator *=(int a)
	{
		if(!a)y++;
		else x = x*a%mod;
		return *this;
	} 
	data & operator /=(int a)
	{
		if(!a)y--;
		else x = x*inv[a]%mod;
		return *this;
	}
};
data Base[N][mxK];
int cnt,pos[N],rt[N];
int ps[N<<2],ls[N<<2],rs[N<<2];
int val[N<<2][mxK],lv[N<<2][mxK],rv[N<<2][mxK],sum[N<<2][mxK];
inline void update(int p)
{
	int l = ls[p],r = rs[p];
	for(int i = 0;i<K;i++)
	{
		val[p][i] = (val[l][i]+val[r][i]+rv[l][i]*lv[r][i])%mod;
		lv[p][i] = (lv[l][i]+lv[r][i]*sum[l][i])%mod;
		rv[p][i] = (rv[r][i]+rv[l][i]*sum[r][i])%mod;
		sum[p][i] = sum[l][i]*sum[r][i]%mod;
	}
}
inline void Build(int &p,int l,int r,int t)
{
	p = ++cnt;
	if(l==r)
	{
		for(int i = 0;i<K;i++)
			val[p][i]=lv[p][i]=rv[p][i]=sum[p][i]=Base[P[t][l-1]][i].val();
		pos[P[t][l-1]] = p;
		return ;
	}
	int mid = (l+r)>>1;
	Build(ls[p],l,mid,t);
	Build(rs[p],mid+1,r,t);
	update(p);ps[ls[p]]=ps[rs[p]]=p;
}
int ans[mxK],tmp[mxK];
void Update(int u)
{
	int t = top[u];
	if (fa[t])
		for (int j=0;j<K;j++)
			Base[fa[t]][j]/=(lv[rt[t]][j]+kx[0][j])%mod;
	for(int j = 0;j<K;j++)
		ans[j] = (ans[j]+mod-val[rt[t]][j])%mod;

	int x = pos[u];
	for(int i = 0;i<K;i++)
		val[x][i]=lv[x][i]=rv[x][i]=sum[x][i]=Base[u][i].val();
	x = ps[x];
	while(x)
		update(x),x=ps[x];

	if (fa[t])
		for (int j=0;j<K;j++)
			Base[fa[t]][j]*=(lv[rt[t]][j]+kx[0][j])%mod;
	for(int j = 0;j<K;j++)
		ans[j] = (ans[j]+val[rt[t]][j])%mod;
}
int n,Val[N],last[N],pnt;
inline bool cmp(int a,int b)
{
	return dep[a]>dep[b];
}
int main()
{
	//freopen("4911.in","r",stdin);
	//freopen("4911.out","w",stdout);
	int x,y,Q;
	char order[10];
	scanf("%d%d",&n,&K);
	int t = 1;
	while(t<K)t<<=1;K = t;
	pre(K);
	for(int i = 1;i<= n;i++)
	{
		scanf("%d",&x);Val[i] = x;
		for(int j = 0;j<K;j++)Base[i][j]=data(kx[x][j]);
	}
	for(int i = 1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y);
	}
	dfs1(1);
	dfs2(1,1);
	for(int i = 1;i<= n;i++)
		if(top[i]==i)
			last[++pnt]=i;
	sort(last+1,last+pnt+1,cmp);
	for(int i = 1;i<= pnt;i++)
	{
		int x = last[i];
		Build(rt[x],1,P[x].size(),x);
		if(fa[x])
		{
			int f = fa[x];
			for(int j = 0;j<K;j++)
				Base[f][j]*=(lv[rt[x]][j]+kx[0][j])%mod;
		}
		for(int j = 0;j<K;j++)
			ans[j] = (ans[j]+val[rt[x]][j])%mod;
	}
	scanf("%d",&Q);
	while(Q--)
	{
		scanf("%s",order);
		if(order[0]=='C')
		{
			scanf("%d%d",&x,&y);
			for(int j=0;j<K;j++)
				Base[x][j]/=kx[Val[x]][j];
			Val[x]=y;
			for (int j=0;j<K;j++)
				Base[x][j]*=kx[Val[x]][j];
			while (x!=0)
				Update(x),x=fa[top[x]];
		}
		else
		{
			scanf("%d",&x);
			for(int j = 0;j<K;j++)tmp[j]=ans[j];
			FWT(tmp,K,0);
			printf("%d\n",tmp[x]);
		}
	}
	return 0;
}
