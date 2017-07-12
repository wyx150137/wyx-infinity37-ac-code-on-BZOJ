
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int N = 3e5+5;
const int INF = 0x3f3f3f3f;
int n,m,r1,r2;
struct Ask
{
	int o,x,y;
	void scanA()
	{
		char opt[3];
		scanf("%s",opt);
		if(opt[0]=='U')
			o = 1,scanf("%d%d",&x,&y);
		else if(opt[0]=='A')
		{
			if(opt[1]=='1')o = 2,scanf("%d%d",&x,&y);
			else if(opt[1]=='2')o = 3,scanf("%d%d",&x,&y);
			else o = 4,scanf("%d",&x);
		}else
		{
			if(opt[1]=='1')o = 5,scanf("%d",&x);
			else if(opt[1]=='2')o = 6,scanf("%d",&x);
			else o =7;
		}
	} 
}ask[N];
int maxn[N<<2],lazy[N<<2];
int fa[N<<2],ed[N<<2],next[N<<2],w[N<<2],save[N<<2],a[N];
int tot;
int getfa(int x)
{
	if(fa[x]==x)return fa[x] = x;
	else return fa[x] = getfa(fa[x]);
}
void push_down(int p,int l,int r)
{
	if(!lazy[p]||l==r)return ;
	lazy[p<<1]+=lazy[p];
	lazy[p<<1|1]+=lazy[p];
	maxn[p<<1]+=lazy[p];
	maxn[p<<1|1]+=lazy[p];
	lazy[p] = 0;
}
void update(int p,int l,int r,int a,int b,int y)
{
	push_down(p,l,r);
	if(l>=a&&r<=b)
	{
		maxn[p]+=y;
		lazy[p]+=y;
		return ;
	}
	int mid=(l+r)>>1;
	if(a<=mid)update(p<<1,l,mid,a,b,y);
	if(b >mid)update(p<<1|1,mid+1,r,a,b,y);	
	maxn[p] = max(maxn[p<<1],maxn[p<<1|1]);
}
int getans(int p,int l,int r,int a,int b)
{
	push_down(p,l,r);
	if(l>=a&&r<=b)return maxn[p];
	int mid=(l+r)>>1,ans = -INF;
	if(a<=mid)ans = max(ans,getans(p<<1,l,mid,a,b));
	if(b >mid)ans = max(ans,getans(p<<1|1,mid+1,r,a,b));
	return ans;
}
void build(int p,int l,int r)
{
	if(l==r)
	{
		maxn[p] = save[l];
		return ;
	}
	int mid = (l+r)>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
	maxn[p] = max(maxn[p<<1],maxn[p<<1|1]);
}
int id;
int main()
{
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
		scanf("%d",&a[i]);
	for(int i = 1;i<= n;i++)
		fa[i] = i,ed[i] = i;
	scanf("%d",&m);
	for(int i= 1;i<= m;i++)
	{
		ask[i].scanA();
		if(ask[i].o==1)
		{
			r1 = getfa(ask[i].x),r2 = getfa(ask[i].y);
			if(r1==r2)continue;
			fa[r2] = r1;
			next[ed[r1]] = r2;
			ed[r1] = ed[r2];
		}
	}
	for(int i = 1;i<= n;i++)
		if(getfa(i)==i)
			for(int j = i;j;j = next[j])
			{
				id++;
				w[j] = id;
				save[id] = a[j];
			}
	build(1,1,n);
	for(int i= 1;i<= n;i++)
		fa[i] = i,ed[i] = i;
	for(int i = 1;i<= m;i++)
	{
		if(ask[i].o==1)
		{
			r1=getfa(ask[i].x),r2=getfa(ask[i].y);
			if(r1==r2)continue;
			fa[r2] = r1;
			ed[r1] = ed[r2];
		}
		else if(ask[i].o==2)update(1,1,n,w[ask[i].x],w[ask[i].x],ask[i].y);
		else if(ask[i].o==3)update(1,1,n,w[getfa(ask[i].x)],w[ed[getfa(ask[i].x)]],ask[i].y);
		else if(ask[i].o==4)update(1,1,n,1,n,ask[i].x);
		else if(ask[i].o==5)printf("%d\n",getans(1,1,n,w[ask[i].x],w[ask[i].x]));
		else if(ask[i].o==6)printf("%d\n",getans(1,1,n,w[getfa(ask[i].x)],w[ed[getfa(ask[i].x)]]));
		else printf("%d\n",getans(1,1,n,1,n));
	}
	return 0;
}
