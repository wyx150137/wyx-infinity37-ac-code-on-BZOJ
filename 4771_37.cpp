
#include <stdio.h>
#include <set>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e5+5;
set<int>S[N];
set<int>::iterator it;
int fa[N][18],dep[N],col[N],in[N],out[N],Dfn,seq[N],a[N];
struct E
{int next,to;}e[N];
int head[N],tot,mx;
void add(int x,int y){e[++tot].to=y;e[tot].next=head[x];head[x]=tot;}
void dfs(int x)
{
	dep[x] = dep[fa[x][0]]+1;
	mx = max(mx,dep[x]);
	in[x] = ++Dfn;seq[Dfn] = x;
	for(int i = 1;i<= 17;i++)fa[x][i]=fa[fa[x][i-1]][i-1];
	for(int i = head[x];i;i=e[i].next)
		dfs(e[i].to);
	out[x] = Dfn;
}
int lca(int x,int y)
{
	if(dep[y]>dep[x])swap(x,y);
	for(int i = 17;i>=0;i--)
		if(dep[fa[x][i]]>=dep[y])x = fa[x][i];
	if(x==y)return x;
	for(int i = 17;i>= 0;i--)
		if(fa[x][i]!=fa[y][i])
			x = fa[x][i],y = fa[y][i];
	return fa[x][0];
}
int tr[N*100],ls[N*100],rs[N*100],cnt,root[N],n,m;
void update(int &p,int pre,int l,int r,int pos,int val)
{
	p = ++cnt;
	ls[p] = ls[pre],rs[p] = rs[pre];
	tr[p] = tr[pre]+val;
	if(l==r)return ;
	int mid = (l+r)>>1;
	if(pos<=mid)update(ls[p],ls[pre],l,mid,pos,val);
	else update(rs[p],rs[pre],mid+1,r,pos,val);
}
int getans(int p,int l,int r,int a,int b)
{
	if(l>=a&&r<=b)return tr[p];
	int mid = (l+r)>>1,ans = 0;
	if(a<=mid)ans+=getans(ls[p],l,mid,a,b);
	if(b >mid)ans+=getans(rs[p],mid+1,r,a,b);
	return ans;
}
void init()
{
	for(int i = 1;i<= cnt;i++)tr[i]=ls[i]=rs[i]=0;
	cnt = 0;
	Dfn = 0;tot = 0;
	for(int i = 1;i<= n;i++)head[i]=0,root[i]=0;
	for(int i = 1;i<= n;i++)S[i].clear();
	mx = 0;
}
bool cmp(int x,int y)
{
	return dep[x]==dep[y]?in[x]<in[y]:dep[x]<dep[y];
}
int main()
{
	int cas;
	scanf("%d",&cas);
	while(cas--)
	{
		scanf("%d%d",&n,&m);
		for(int i = 1;i<= n;i++)scanf("%d",&col[i]),a[i]=i;
		for(int i = 2;i<= n;i++)scanf("%d",&fa[i][0]),add(fa[i][0],i);
		dfs(1);
		sort(a+1,a+n+1,cmp);
		int tmp1,tmp2;
		for(int i = 1;i<= n;i++)
		{
			if(dep[a[i]]==dep[a[i-1]])
				update(root[dep[a[i]]],root[dep[a[i]]],1,n,in[a[i]],1);
			else 
				update(root[dep[a[i]]],root[dep[a[i]]-1],1,n,in[a[i]],1);
			it = S[col[a[i]]].upper_bound(in[a[i]]);
			tmp1 = tmp2 = 0;
			if(it!=S[col[a[i]]].end())
			{
				tmp1 = (*it);
				tmp1 = seq[tmp1];
				update(root[dep[a[i]]],root[dep[a[i]]],1,n,in[lca(tmp1,a[i])],-1);
			}
			if(it!=S[col[a[i]]].begin())
			{
				it--;
				tmp2 = (*it);
				tmp2 = seq[tmp2];
				update(root[dep[a[i]]],root[dep[a[i]]],1,n,in[lca(tmp2,a[i])],-1);
			}
			if(tmp1&&tmp2)
				update(root[dep[a[i]]],root[dep[a[i]]],1,n,in[lca(tmp1,tmp2)],1);
			S[col[a[i]]].insert(in[a[i]]);
		}
		int x,d,ans=0;
		for(int i = 1;i<= m;i++)
		{
			scanf("%d%d",&x,&d);
			x = x^ans,d = d^ans;
			ans = getans(root[min(dep[x]+d,mx)],1,n,in[x],out[x]);
			printf("%d\n",ans);
		}
		init();
	}
	return 0;
}
