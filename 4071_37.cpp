
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = 100005;
LL sum[N<<3];
int size[N<<3];
struct P{int a,b;}per[N];
int pos[N<<1],cnt,tot,d[N<<1];
bool cmp(const P &x,const P &y)
{
	return (x.a+x.b)<(y.a+y.b);
}
void init()
{
	sort(pos+1,pos+cnt+1);
	int tmp = cnt;cnt = 0;
	pos[0] = -1e9;
	for(int i = 1;i<= tmp;i++)
		if(pos[i]!=pos[cnt])
			pos[++cnt] = pos[i];
}
int find(int x)
{
	int l = 1,r = cnt+1;
	while(l<r)
	{
		int mid = (l+r)>>1;
		if(pos[mid]<x)l = mid+1;
		else r = mid;
	}
	return l;
}
void push_up(int p)
{
	sum[p] = sum[p<<1]+sum[p<<1|1];
	size[p] = size[p<<1]+size[p<<1|1];
}
void build(int p,int l,int r)
{
	if(l==r)
	{
		sum[p] = size[p] = 0;
		return ;
	}
	int mid = (l+r)>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
	push_up(p);
}
void update(int p,int l,int r,int x)
{
	if(l==r)
	{
		sum[p]+=d[l];
		size[p]++;
		return ;
	}
	int mid = (l+r)>>1;
	if(x<=mid)update(p<<1,l,mid,x);
	else update(p<<1|1,mid+1,r,x);
	push_up(p);
}
LL get_sum(int p,int l,int r,int cnt)
{
	if(size[p]<=cnt)return sum[p];
	if(l==r)return (LL)cnt*d[l];
	int mid = (l+r)>>1;
	if(size[p<<1]>=cnt)return get_sum(p<<1,l,mid,cnt);
	else return sum[p<<1]+get_sum(p<<1|1,mid+1,r,cnt-size[p<<1]);
}
LL Ask(LL k)
{
	LL s = get_sum(1,1,cnt,k);
	return sum[1]-(LL)2*s;
}
LL ans[N];
int main()
{
	int k,n;
	scanf("%d%d",&k,&n);
	LL pre = 0;
	char x1[5],x2[5];int x,y;
	for(int i = 1;i<= n;i++)
	{
		scanf("%s%d%s%d",x1,&x,x2,&y);
		if(x1[0]==x2[0])pre+=abs(y-x);
		else
		{
			pre++;
			pos[++cnt] = x;pos[++cnt] = y;
			per[++tot].a = x;per[tot].b = y;
		}
	}
	init();
	sort(per+1,per+tot+1,cmp);
	if(cnt)
	{
		n = tot;
		for(int i = 1;i<= n;i++)
			d[find(per[i].a)] = per[i].a,d[find(per[i].b)] = per[i].b;
		build(1,1,cnt);
		for(int i = 1;i<= n;i++)
		{
			update(1,1,cnt,find(per[i].a));
			update(1,1,cnt,find(per[i].b));
			ans[i] = Ask(i);
		}
	}
	if(k==1){printf("%lld\n",ans[n]+pre);return 0;}
	else
	{
		LL Ans = ans[n];
		if(cnt)
		{
			build(1,1,cnt);
			for(int i = n;i>1;i--)
			{
				update(1,1,cnt,find(per[i].a));
				update(1,1,cnt,find(per[i].b));
				Ans = min(Ans,ans[i-1]+Ask(n-i+1));
			}
		}
		printf("%lld\n",Ans+pre);
	}
	return 0;
}
