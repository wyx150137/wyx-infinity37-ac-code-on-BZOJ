
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 200005;
typedef long long ll;
struct List
{
	struct E
	{
		int l,r,type,val,next;
	}e[N*3];
	int head[N],tot;
	void add(int x,int l,int r,int type,int val)
	{
		e[++tot].l = l;e[tot].r = r;e[tot].type = type;
		e[tot].val = val;
		e[tot].next = head[x];
		head[x] = tot;
	}
	void clear()
	{
		memset(head,0,sizeof(head));
		tot = 0;
	}
}ad,as;
struct Ask
{int l,r,id;}ask[N];
struct Seg
{
	ll sum[N<<2],lazy[N<<2];
	void Push_down(int p,int l,int r)
	{
		if(!lazy[p]||l==r)return ;
		int mid = (l+r)>>1;
		sum[p<<1]+=(ll)(mid-l+1)*lazy[p];
		sum[p<<1|1]+=(ll)(r-mid)*lazy[p];
		lazy[p<<1]+=lazy[p],lazy[p<<1|1]+=lazy[p];
		lazy[p] = 0;
	}
	void update(int p,int l,int r,int a,int b,int val)
	{
		if(a>b)return ;
		Push_down(p,l,r);
		if(l>=a&&r<=b)
		{
			sum[p]+=(ll)(r-l+1)*val;
			lazy[p]+=val;
			return ;
		}
		int mid = (l+r)>>1;
		if(a<=mid)update(p<<1,l,mid,a,b,val);
		if(b >mid)update(p<<1|1,mid+1,r,a,b,val);
		sum[p] = sum[p<<1]+sum[p<<1|1];
	}
	ll getans(int p,int l,int r,int a,int b)
	{
		if(a>b)return 0;
		Push_down(p,l,r);
		if(l>=a&&r<=b)return sum[p];
		ll ans = 0;
		int mid = (l+r)>>1;
		if(a<=mid)ans = ans+getans(p<<1,l,mid,a,b);
		if(b >mid)ans = ans+getans(p<<1|1,mid+1,r,a,b);
		return ans;
	}
}tr[2];
ll ans[N];
int l[N],r[N],stack[N],top,a[N];
int main()
{
	//freopen("test.in","r",stdin);
	int n,m,p1,p2;
	scanf("%d%d%d%d",&n,&m,&p1,&p2);
	for(int i = 1;i<= n;i++)scanf("%d",&a[i]);
	top = 0;
	for(int i = 1;i<= n;i++)
	{
		while(top&&a[stack[top]]<a[i])r[stack[top]]=i-1,top--;
		stack[++top] = i;
	}
	while(top)r[stack[top]]=n,top--;
	for(int i = n;i>= 1;i--)
	{
		while(top&&a[stack[top]]<a[i])l[stack[top]]=i+1,top--;
		stack[++top] = i;
	}
	while(top)l[stack[top]]=1,top--;
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d",&ask[i].l,&ask[i].r);
		ask[i].id = i;
		as.add(ask[i].r,ask[i].l,ask[i].r,1,i);
		as.add(ask[i].l-1,ask[i].l,ask[i].r,-1,i);
	}
	for(int i = 1;i<= n;i++)
	{
		ad.add(l[i]-1,r[i]+1,r[i]+1,0,p1);
		ad.add(l[i]-1,i+1,r[i],0,p2);
		ad.add(r[i]+1,l[i],i-1,1,p2);
	}
	for(int i = 1;i<= n;i++)
	{
		for(int j = ad.head[i];j;j=ad.e[j].next)
		{
			int L = ad.e[j].l,R = ad.e[j].r,typ = ad.e[j].type,vl = ad.e[j].val;
			tr[typ].update(1,1,n,max(1,L),min(R,n),vl);
		}
		if(i!=n)tr[0].update(1,1,n,i+1,i+1,p1);
		for(int j = as.head[i];j;j=as.e[j].next)
		{
			int L = as.e[j].l,R = as.e[j].r,typ = as.e[j].type,vl = as.e[j].val;
			for(int k =0;k<2;k++)
				ans[vl]+=(ll)typ*tr[k].getans(1,1,n,L,R);
		}
	}
	for(int i = 1;i<= m;i++)
		printf("%lld\n",ans[i]);
	return 0;
}
