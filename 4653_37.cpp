
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1000005;
const int M = 200005;
const int INF = (1<<30)+((1<<30)-1);
int maxn[N<<2],lazy[N<<2];
int p[N],tot;
inline int read()
{
	int x = 0, f = 1; char ch = getchar();
	while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
	while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
	return x * f;
}
struct Q
{
	int l,r,len;
}qu[N>>1];
bool cmp(Q a,Q b)
{
	return a.len<b.len;
}
void push_down(int p,int l,int r)
{
	if(l==r||!lazy[p])return ;
	lazy[p<<1]+=lazy[p];
	lazy[p<<1|1]+=lazy[p];
	maxn[p<<1]+=lazy[p];
	maxn[p<<1|1]+=lazy[p];
	lazy[p] = 0;
}
void update(int p,int l,int r,int a,int b,int c)
{
	push_down(p,l,r);
	if(l>=a&&r<=b)
	{
		lazy[p]+=c;
		maxn[p]+=c;
		return ;
	}
	int mid = (l+r)>>1;
	if(a<=mid)update(p<<1,l,mid,a,b,c);
	if(b>mid) update(p<<1|1,mid+1,r,a,b,c);
	maxn[p] = max(maxn[p<<1],maxn[p<<1|1]);
}
int find(int x)
{
	int l = 1,r = tot+1;
	while(l<r)
	{
		int mid = (l+r)>>1;
		if(p[mid]<x)l = mid+1;
		else r = mid;
	}
	return l;
}
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= n;i++)
	{
		qu[i].l = read();
		qu[i].r = read();
		qu[i].len = qu[i].r-qu[i].l+1;
		p[++tot] = qu[i].l;p[++tot] = qu[i].r;
	}
	sort(p+1,p+tot+1);
	int tmp = tot;tot = 0;
	for(int i = 1;i<= tmp;i++)
		if(p[i]!=p[tot])
			p[++tot] = p[i];
	for(int i = 1;i<= n;i++)
		qu[i].l = find(qu[i].l),qu[i].r = find(qu[i].r);
	sort(qu+1,qu+n+1,cmp);
	int now = 0;
	int ans = INF;
	for(int i = 1;i<= n;i++)
	{
		while(maxn[1]<m)
		{
			if(now==n)break;
			now++;
			update(1,1,tot,qu[now].l,qu[now].r,1);
		}
		//if(now==n)break;
		if(maxn[1]>=m)ans = min(ans,qu[now].len-qu[i].len);
		update(1,1,tot,qu[i].l,qu[i].r,-1);
	}
	if(ans==INF)printf("-1\n");
	else printf("%d\n",ans);
	return 0;
}
