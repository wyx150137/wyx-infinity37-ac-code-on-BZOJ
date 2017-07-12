
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 2e5+5;
const int INF = 2e9;
struct P
{
	int x,y;
}a[N],q1[N],q2[N];
bool cmpy(const P &a,const P &b)
{
	return a.y>b.y;
}
bool cmpx(const P &a,const P &b)
{
	return a.x<b.x;
}
long long ans;
int find(int x,int lim)
{
	int l = 1,r = lim;
	while(l<=r)
	{
		int mid = (l+r)>>1;
		if(q1[mid].y<=x)r = mid-1;
		else l = mid+1;
	}
	return r;
}
void CDQ(int l,int r)
{
	int mid = (l+r)>>1;
	if(l==r)return ;
	CDQ(l,mid);
	sort(a+l,a+mid+1,cmpy);
	sort(a+mid+1,a+r+1,cmpy);
	int top1 = 0,top2 = 0,p = mid+1;
	q1[0].y = q2[0].y = INF;
	int ll,rr;
	for(int i = l;i<=mid;i++)
	{
		while(p<=r&&a[p].y>a[i].y)
		{
			while(top1&&a[p].x<q1[top1].x)
				top1--;
			q1[++top1] = a[p];
			p++;
		}
		while(top2&&a[i].x>q2[top2].x)
			top2--;
		q2[++top2] = a[i];
		ll = find(q2[top2-1].y,top1)+1;
		rr = find(q2[top2].y,top1);
		if(ll<=rr)
			ans+=rr-ll+1;
	}
	sort(a+l,a+mid+1,cmpx);
	sort(a+mid+1,a+r+1,cmpx);
	CDQ(mid+1,r);
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<= n;i++)
		scanf("%d%d",&a[i].x,&a[i].y);
	sort(a+1,a+n+1,cmpx);
	CDQ(1,n);
	printf("%lld\n",ans);
	return 0;
}
