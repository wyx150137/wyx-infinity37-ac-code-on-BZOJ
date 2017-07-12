
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e5+5;
const int MD = 320;
const int S = 65540;
const int ss = 65535;
int cnt[S];
typedef unsigned long long ull;
ull MAXN = 0;
struct Bitset
{
	ull s[470];
	int len;
	void clear()
	{memset(s,0,sizeof(s));len = 0;}
	void operator |=(const int &x){s[x>>6] |= 1ll<<(x&63);len = max(len,x>>6);}
	void operator |=(const Bitset &y)
	{
		len = max(len,y.len);
		for(int i = 0;i<=len;i++)
			s[i]|=y.s[i];
	}
	int num()
	{
		int res = 0;
		for(int i = 0;i<=len;i++)
			res+=cnt[s[i]>>48]+cnt[(s[i]>>32)&ss]+cnt[(s[i]>>16)&ss]+cnt[s[i]&ss];
		return res;
	}
	int getans()
	{
		for(int i = 0;i<470;i++)if(s[i]!=MAXN)
			for(int j = 0;j<64;j++)
				if(!(s[i]&((ull)1<<j)))
					return i*64+j;
	}
}b[325][325],ans;
struct E
{int next,to;}e[N<<1];
int head[N],tot;
void add(int x,int y)
{
	e[++tot].to = y;e[tot].next = head[x];head[x] = tot;
	e[++tot].to = x;e[tot].next = head[y];head[y] = tot;
}
int mark[N],rtnum,rt[N],n,m,flag;
int size[N],dep[N],mx[N],top[N],fa[N][18],w[N];
void dfs(int x)
{
	mx[x] = dep[x];
	for(int i = head[x];i;i=e[i].next)
		if(e[i].to!=fa[x][0])
		{
			dep[e[i].to] = dep[x]+1;
			fa[e[i].to][0] = x;
			dfs(e[i].to);
			mx[x] = max(mx[x],mx[e[i].to]);
		}
	if(mx[x]-dep[x]>=MD||x==1)
	{
		mark[x] = ++rtnum;
		rt[rtnum] = x;
		mx[x] = 0;
	}
}
int lca(int x,int y)
{
	if(dep[x]<dep[y])swap(x,y);
	for(int i = 17;i>=0;i--)
		if(dep[fa[x][i]]>=dep[y])
			x = fa[x][i];
	if(x==y)return x;
	for(int i = 17;i>= 0;i--)
		if(fa[x][i]!=fa[y][i])
			x = fa[x][i],y = fa[y][i];
	return fa[x][0];
}

int main()
{
	int x,y;
	scanf("%d%d%d",&n,&m,&flag);
	for(int i = 0;i<64;i++)MAXN = MAXN<<1|1;
	for(int i = 0;i<S;i++)
		for(int j = i;j;j-=j&(-j))
			cnt[i]++;
	for(int i = 1;i<= n;i++)scanf("%d",&w[i]);
	for(int i = 1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y);
	}
	dep[1] = 1;
	dfs(1);
	for(int j = 1;j<= 17;j++)
		for(int i = 1;i<= n;i++)
			fa[i][j] = fa[fa[i][j-1]][j-1];
	for(int i = 1;i<= rtnum;i++)
	{
		Bitset now;
		now.clear();
		now|=w[rt[i]];b[i][i] = now;
		for(int t = fa[rt[i]][0];t;t=fa[t][0])
		{
			now|=w[t];
			if(mark[t])
			{
				b[i][mark[t]] = now;
				if(!top[rt[i]])top[rt[i]] = t;
			}
		}
	}
	int nn,last = 0;
    for(int i=1;i<=m;++i)
    {
        ans.clear();scanf("%d",&nn);
        for(int j=1;j<=nn;++j)
        {
        	scanf("%d%d",&x,&y);
            int xx,yy;
            if(flag) x^=last,y^=last;
            int z=lca(x,y);ans|=w[x];ans|=w[y];
            for(;!mark[x]&&dep[x]>dep[z];)
                x=fa[x][0],ans|=w[x];
            for(;!mark[y]&&dep[y]>dep[z];)
                y=fa[y][0],ans|=w[y];
            for(xx=x;dep[top[xx]]>=dep[z];xx=top[xx]);
            for(yy=y;dep[top[yy]]>=dep[z];yy=top[yy]);
            ans|=b[mark[x]][mark[xx]];
            ans|=b[mark[y]][mark[yy]];
            for(;xx!=yy;)
            {
                if(dep[xx]<dep[yy]) swap(xx,yy);
                xx=fa[xx][0];ans|=w[xx];
            }
        }
        int x=ans.num(),y=ans.getans();
        last=x+y;
        printf("%d %d\n",x,y);
    }
	return 0;
}
