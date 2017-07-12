
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 100005;
const int M = 50005;
int n,m,cnt[N],a[N],b[N],c[N],tim[N],f[M],tot;
long long ans;
void update(int x,int flag)
{
	for(int i = x;i&&i<N;i+=flag*(i&-i))
	{
		if(tim[i]!=tot)
			c[i] = 0,tim[i] = tot;
		c[i]++;
	}
}
int getans(int x,int flag)
{
	int ans = 0;
	for(int i = x;i&&i<N;i+=flag*(i&-i))
		if(tim[i]==tot)
			ans+=c[i];
	return ans;
}
struct A
{
	int x,y,pos;
	bool operator <(const A &b)const
	{return y<b.y;}
}q[N],nq[N];
void CDQ(int l,int r)
{
	int mid = (l+r)>>1;
	if(l==r)
	{
		printf("%lld\n",ans);
		ans-=cnt[q[mid].y];
		ans+=f[mid];
		return ;
	}
	int l1 = l,l2 = mid+1;
	for(int i = l;i<= r;i++)
		if(q[i].pos<=mid)
			nq[l1++]=q[i];
		else 
			nq[l2++]=q[i];
	memcpy(q+l,nq+l,sizeof(q[0])*(r-l+1));
	CDQ(l,mid);
	tot++;int j = l;
	for(int i = mid+1;i<= r;i++)
	{
		for(;j<=mid&&q[j].y<q[i].y;j++)
			update(q[j].x,-1);
		f[q[i].pos]+=getans(q[i].x,1);
	}
	tot++,j = mid;
	for(int i = r;i>=mid+1;i--)
	{
		for(;j>=l&&q[j].y>q[i].y;j--)
			update(q[j].x,1);
		f[q[i].pos]+=getans(q[i].x,-1);
	}
	CDQ(mid+1,r);
	l1=l;l2=mid+1;
    for(int i=l;i<=r;i++)
        if((q[l1]<q[l2]||l2>r)&&l1<=mid)
            nq[i]=q[l1++];
        else
            nq[i]=q[l2++];
    memcpy(q+l,nq+l,sizeof(q[0])*(r-l+1));
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= n;i++)
	{
		scanf("%d",&a[i]);
		b[a[i]] = i;
	}
	for(int i = 1;i<= n;i++)
	{
		cnt[i] = getans(a[i],1);
		update(a[i],-1);
		ans+=cnt[i];
	}
	tot++;
	for(int i = n;i;i--)
	{
		cnt[i] += getans(a[i],-1);
		update(a[i],1);
	}
	for(int i = 1;i<= m;i++)
	{
		scanf("%d",&q[i].x);
		q[i].y = b[q[i].x];
		q[i].pos = i;
	}
	sort(q+1,q+m+1);
	CDQ(1,m);
	return 0;
}
