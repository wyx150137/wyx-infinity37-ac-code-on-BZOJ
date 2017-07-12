
#include<cstdio>
#include<algorithm>
using namespace std;
struct tree
{
	int l,r;
	int s;
	int ll,rr;
	int ma,mi;
}tr[2400001];
int a[300001];
inline int gcd(int x,int y)
{
	if(x==0)
		return y;
	else if(y==0)
		return x;
	int m=x%y;
	while(m!=0)
	{
		x=y;
		y=m;
		m=x%y;
	}
	return y;
}
inline int absx(int x)
{
	if(x<0)
		x=-x;
	return x;
}
inline void up(int p)
{
	tr[p].ll=tr[p*2].ll;
	tr[p].rr=tr[p*2+1].rr;
	int xx=absx(tr[p*2].rr-tr[p*2+1].ll);
	tr[p].s=gcd(gcd(tr[p*2].s,tr[p*2+1].s),xx);
	tr[p].ma=max(tr[p*2].ma,tr[p*2+1].ma);
	tr[p].mi=min(tr[p*2].mi,tr[p*2+1].mi);
}
inline void build(int p,int l,int r)
{
	tr[p].l=l;
	tr[p].r=r;
	if(l!=r)
	{
		int mid=(l+r)/2;
		build(p*2,l,mid);
		build(p*2+1,mid+1,r);
		up(p);
	}
	else
	{
		tr[p].ll=a[l];
		tr[p].rr=a[l];
		tr[p].ma=a[l];
		tr[p].mi=a[l];
	}
}
inline void change(int p,int l,int r,int x)
{
	if(l<=tr[p].l&&tr[p].r<=r)
	{
		tr[p].ll=x;
		tr[p].rr=x;
		tr[p].ma=x;
		tr[p].mi=x;
	}
	else
	{
		int mid=(tr[p].l+tr[p].r)/2;
		if(l<=mid)
			change(p*2,l,r,x);
		if(r>mid)
			change(p*2+1,l,r,x);
		up(p);
	}
}
tree nx;
inline tree ask(int p,int l,int r)
{
	if(l<=tr[p].l&&tr[p].r<=r)
		return tr[p];
	else
	{
		int mid=(tr[p].l+tr[p].r)/2;
		tree ans=nx;
		tree ans1,ans2;
		bool flag1=false,flag2=false;
		if(l<=mid)
		{
			flag1=true;
			ans1=ask(p*2,l,r);
		}
		if(r>mid)
		{
			flag2=true;
			ans2=ask(p*2+1,l,r);
		}
		if(flag1)
		{
			if(flag2)
			{
				int xx=absx(ans1.rr-ans2.ll);
				ans.s=gcd(gcd(ans1.s,ans2.s),xx);
				ans.ma=max(ans1.ma,ans2.ma);
				ans.mi=min(ans1.mi,ans2.mi);
				ans.ll=ans1.ll;
				ans.rr=ans2.rr;
			}
			else
				ans=ans1;
		}
		else
			ans=ans2;
		return ans;
	}
}
int main()
{
//	freopen("yyn.in","r",stdin);
//	freopen("yyn.out","w",stdout);
	int n,m;
	scanf("%d%d",&n,&m);
	int i;
	for(i=1;i<=n;i++)
		scanf("%d",&a[i]);
	build(1,1,n);
	int xx;
	int l,r,k;
	int sx=0;
	for(i=1;i<=m;i++)
	{
		scanf("%d",&xx);
		if(xx==1)
		{
			scanf("%d%d",&l,&r);
			l=l^sx;
			r=r^sx;
			change(1,l,l,r);
		}
		else
		{
			scanf("%d%d%d",&l,&r,&k);
			l=l^sx;
			r=r^sx;
			k=k^sx;
			tree xt=ask(1,l,r);
			if(xt.s==k&&(xt.ma-xt.mi)==k*(r-l)||l==r)
			{
				printf("Yes\n");
				sx++;
			}
			else
				printf("No\n");
		}
	}
	return 0;
}
