
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int N = 2e5+5;
const int INF = 0x3f3f3f3f;
int sg[N<<2],lazy[N<<2],fa[N],a[N],fs[N],next[N],last[N];
int getfa(int x)
{
	if(fa[x]==x)return fa[x] = x;
	else return fa[x] = getfa(fa[x]);
}
struct A
{int l,r,no,ans;}ask[N];
bool cmp(A a,A b){return a.l<b.l;}
bool fir(A a,A b){return a.no<b.no;}
void build(int p,int l,int r)
{
	lazy[p] = INF;
	if(l==r)
	{
		sg[p] = fs[l];
		return ;
	}
	int mid = (l+r)>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
	sg[p] = max(sg[p<<1],sg[p<<1|1]);
}
void push_down(int p,int l,int r)
{
	if(lazy[p]==INF||l==r)return ;
	sg[p<<1] = min(sg[p<<1],lazy[p]);
	sg[p<<1|1] = min(sg[p<<1|1],lazy[p]);
	lazy[p<<1] = min(lazy[p<<1],lazy[p]);
	lazy[p<<1|1] = min(lazy[p<<1|1],lazy[p]);
	lazy[p] = INF;
}
void update(int p,int l,int r,int a,int b,int c)
{
	push_down(p,l,r);
	if(l>=a&&r<=b)
	{
		sg[p] = min(sg[p],c);
		lazy[p] = min(lazy[p],c);
		return ;
	}
	int mid = (l+r)>>1;
	if(a<=mid)update(p<<1,l,mid,a,b,c);
	if(b>mid)update(p<<1|1,mid+1,r,a,b,c);
	sg[p] = max(sg[p<<1],sg[p<<1|1]);
}
int getans(int p,int l,int r,int x)
{
	push_down(p,l,r);
	if(l==r)return sg[p];
	int mid = (l+r)>>1;
	if(x<=mid)return getans(p<<1,l,mid,x);
	else return getans(p<<1|1,mid+1,r,x);
}
int main()
{
	int n,q,maxn = 0;
	scanf("%d%d",&n,&q);
	for(int i = 1;i<= n;i++)
	{
		scanf("%d",&a[i]);
		maxn = max(maxn,a[i]);
		next[last[a[i]]] = i;
		last[a[i]] = i;
	}
	for(int i = 1;i<= n;i++)
		if(!next[i])next[i] = n+1;
	for(int i = 1;i<= maxn;i++)
		fa[i] = i;
	fa[maxn+1] = maxn+1;
	for(int i = 1;i<= n;i++)
	{
		fa[a[i]] = a[i]+1;
		fs[i] = getfa(0);
	}
	build(1,1,n);
	for(int i = 1;i<= q;i++)
	{
		scanf("%d%d",&ask[i].l,&ask[i].r);
		ask[i].no = i;
	}
	sort(ask+1,ask+q+1,cmp);
	ask[0].l = 1;
	for(int i = 1;i<= q;i++)
	{
		for(int j = ask[i-1].l;j<ask[i].l;j++)
			update(1,1,n,j,next[j]-1,a[j]);
		ask[i].ans = getans(1,1,n,ask[i].r);
	}
	sort(ask+1,ask+q+1,fir);
	for(int i = 1;i<= q;i++)
		printf("%d\n",ask[i].ans);
	return 0;
}
