
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 100005;
struct E
{int next,to;}e[N<<1];
int head[N],tot,cnt;
void add(int x,int y)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	head[x] = tot;
}
int top[N],deep[N],fa[N],w[N],size[N],son[N],t[N];
int sum[N<<2],f[N<<2],n;
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
			if(size[tmp]>size[son[x]])son[x] = tmp;
			fa[tmp] = x;
		}
	}
}
void dfs2(int x,int tp)
{
	top[x] = tp;
	w[x] = ++cnt;
	if(son[x]!=n)dfs2(son[x],tp);
	for(int i = head[x];i;i = e[i].next)
		if(e[i].to!=fa[x]&&e[i].to!=son[x])
			dfs2(e[i].to,e[i].to);
	t[x] = cnt;
}
void push_down(int p,int l,int r)
{
	int mid = (l+r)>>1;
	sum[p] = (r-l+1)*f[p];
	f[p<<1] = f[p];
	sum[p<<1] = f[p]*(mid-l+1);
	f[(p<<1)+1] = f[p];
	sum[(p<<1)+1] = f[p]*(r-mid);
	f[p] = -1;
}
void update(int p,int l,int r,int a,int b,int c)
{
	if(l>=a&&r<=b){f[p] =c;sum[p] = (r-l+1)*f[p];return ;}
	if(f[p]!=-1)push_down(p,l,r);
	int mid = (l+r)>>1;
	if(a<= mid)
		update(p<<1,l,mid,a,b,c);
	if(b>mid)
		update((p<<1)+1,mid+1,r,a,b,c);
	sum[p] = sum[p<<1]+sum[(p<<1)+1];
}
int getans(int p,int l,int r,int a,int b)
{
	if(l>=a&&r<=b)return sum[p];
	if(f[p]!=-1)push_down(p,l,r);
	int mid = (l+r)>>1;
	if(b<=mid)return getans(p<<1,l,mid,a,b);
	else if(a>mid)return getans((p<<1)+1,mid+1,r,a,b);
	else return getans(p<<1,l,mid,a,b)+getans((p<<1)+1,mid+1,r,a,b);
}
int t_ans;
void get_update(int x,int y,int c,int opt)
{
	while(top[x]!=top[y])
	{
		if(deep[x]<deep[y])swap(x,y);
		if(opt==1)update(1,1,n,w[top[x]],w[x],c);
		else t_ans+=getans(1,1,n,w[top[x]],w[x]);
		x = fa[top[x]];
	}
	if(deep[x]<deep[y])swap(x,y);
	if(opt==1)update(1,1,n,w[y],w[x],c);
	else t_ans+=getans(1,1,n,w[y],w[x]);
}
int main()
{
	memset(f,-1,sizeof(f));
	int x;
	scanf("%d",&n);
	for(int i = 0;i< n;i++)
		son[i] = n;
	for(int i = 1;i< n;i++)
		{scanf("%d",&x);add(x,i);}
	dfs1(0,1);
	dfs2(0,0);
	char j[20];
	int q,tmp1,tmp2;
	scanf("%d",&q);
	for(int i = 1;i<= q;i++)
	{
		scanf("%s%d",j,&x);
		if(j[0]=='i')
		{
			t_ans = 0;
			get_update(0,x,0,0);
			tmp1 = t_ans;
			get_update(0,x,1,1);
			t_ans = 0;
			get_update(0,x,0,0);
			printf("%d\n",t_ans-tmp1);
		}else
		{
			tmp1= getans(1,1,n,w[x],t[x]);
			update(1,1,n,w[x],t[x],0);
			tmp2 = getans(1,1,n,w[x],t[x]);
			printf("%d\n",tmp1-tmp2);
		}
	}
	return 0;
}
