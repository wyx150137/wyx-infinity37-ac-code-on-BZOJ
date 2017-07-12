
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
#define N 100005
#define M 10000005
struct seg{int ls,rs,sum,mw;}t[M];
int tpn,n;
struct E{int next,to;}e[N<<1];
int head[N],tot;
void add(int x,int y)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	head[x]= tot;
}
int top[N],deep[N],fa[N],size[N],son[N],w[N],cnt;
bool v[N];
void dfs1(int x,int dep)
{
	v[x] = true;
	deep[x] = dep;
	size[x]++;
	for(int i = head[x];i;i = e[i].next)
	{
		int tmp = e[i].to;
		if(!v[tmp])
		{
			dfs1(tmp,dep+1);
			size[x]+=size[tmp];
			fa[tmp] = x;
			if(size[tmp]>size[son[x]])son[x] = tmp;
		}
	}
}
void dfs2(int x,int tp)
{
	top[x] = tp;
	w[x]= ++cnt;
	if(son[x])dfs2(son[x],tp);
	for(int i = head[x];i;i = e[i].next)
		if(e[i].to!=fa[x]&&e[i].to!=son[x])
			dfs2(e[i].to,e[i].to);
}
int score[N],color[N];
int root[N];
void update(int p,int l,int r,int x,int b)
{
	if(l==r){t[p].sum = b,t[p].mw= b;return ;}
	int mid = (l+r)>>1;
	if(x<=mid)
	{
		if(t[p].ls==0)t[p].ls= ++tpn;
		update(t[p].ls,l,mid,x,b);
	}else
	{
		if(t[p].rs==0)t[p].rs= ++tpn;
		update(t[p].rs,mid+1,r,x,b);
	}
	t[p].sum = t[t[p].ls].sum+t[t[p].rs].sum;
	t[p].mw = max(t[t[p].ls].mw,t[t[p].rs].mw);	
}
int getmax(int p,int l,int r,int a,int b)
{
	if(l>=a&&r<=b)return t[p].mw;
	int mid = (l+r)>>1;
	int ans = 0;
	if(a<=mid)
		ans = max(ans,getmax(t[p].ls,l,mid,a,b));
	if(b>mid)
		ans = max(ans,getmax(t[p].rs,mid+1,r,a,b));
	return ans;
}
int getsum(int p,int l,int r,int a,int b)
{
	if(l>=a&&r<=b)return t[p].sum;
	int mid = (l+r)>>1;
	int ans = 0;
	if(a<= mid)
		ans+=getsum(t[p].ls,l,mid,a,b);
	if(b>mid)
		ans+=getsum(t[p].rs,mid+1,r,a,b);
	return ans;
}
int get_ans(int x,int y,int opt,int c)
{
	int ans = 0;
	while(top[x]!=top[y])
	{
		if(deep[top[x]]<deep[top[y]])swap(x,y);
		if(opt==1)ans += getsum(root[c],1,n,w[top[x]],w[x]);
		else ans = max(ans,getmax(root[c],1,n,w[top[x]],w[x]));
		x = fa[top[x]];
	}
	if(deep[x]<deep[y])swap(x,y);
	if(opt==1)ans += getsum(root[c],1,n,w[y],w[x]);
	else ans = max(ans,getmax(root[c],1,n,w[y],w[x]));
	return ans;
}
int main()
{
	for(int i = 1;i<= N-5;i++)
		root[i] = ++tpn;
	int x,y,q;
	scanf("%d%d",&n,&q);
	for(int i = 1;i<= n;i++)
		scanf("%d%d",&score[i],&color[i]);
	for(int i = 1;i<n;i++)
		{scanf("%d%d",&x,&y);add(x,y);add(y,x);}
	dfs1(1,1);
	dfs2(1,1);
	for(int i = 1;i<= n;i++)
		update(root[color[i]],1,n,w[i],score[i]);
	char j[5];
	for(int i = 1;i<= q;i++)
	{
		scanf("%s%d%d",j,&x,&y);
		if(j[1]=='S')printf("%d\n",get_ans(x,y,1,color[x]));
		else if(j[1]=='M')printf("%d\n",get_ans(x,y,0,color[x]));
		else if(j[1]=='W')
		{
			score[x] = y;
			update(root[color[x]],1,n,w[x],y);
		}else
		{
			update(root[color[x]],1,n,w[x],0);
			color[x] = y;
			update(root[color[x]],1,n,w[x],score[x]);
		}
	}
	return 0;
}
