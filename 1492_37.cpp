
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef double db;
typedef pair<db,db>PA;
const int N = 1e5+5;
const int INF = 0x3f3f3f3f;
db f[N];
struct P
{
	db a,b,rate,slope;
	int pos;
	bool operator<(const P &s)const
	{
		return slope<s.slope;
	}
}q[N],nq[N];
PA p[N],np[N];
int st[N],top,n;
double getslope(PA x,PA y)
{
	if(x.first==y.first)
		return y.second>=x.second?INF:-INF;
	return (y.second-x.second)/(y.first-x.first);
}
void CDQ(int l,int r)
{
	int mid = (l+r)>>1;
	if(l==r)
	{
		f[mid] = max(f[mid],f[mid-1]);
		p[mid].first = f[mid]/(q[mid].a+q[mid].b/q[mid].rate);
		p[mid].second = f[mid]/(q[mid].a*q[mid].rate+q[mid].b);
		return ;
	}
	int l1 = l,l2 = mid+1;
	for(int i = l;i<= r;i++)
		if(q[i].pos<=mid)
			nq[l1++] = q[i];
		else nq[l2++] = q[i];
	memcpy(q+l,nq+l,sizeof(q[0])*(r-l+1));
	CDQ(l,mid);
	top = 0;
	for(int i = l;i<= mid;i++)
	{
		while(top>1&&getslope(p[st[top-1]],p[st[top]])<getslope(p[st[top]],p[i]))
			st[top--] = 0;
		st[++top] = i;
	}
	for(int i = mid+1;i<= r;i++)
	{
		while(top>1&&getslope(p[st[top-1]],p[st[top]])<q[i].slope)
			st[top--] =0;
		f[q[i].pos] = max(f[q[i].pos],q[i].a*p[st[top]].first+q[i].b*p[st[top]].second);
	}
	CDQ(mid+1,r);
	l1 = l,l2 = mid+1;
	for(int i = l;i<= r;i++)
		if((p[l1]<p[l2]||l2>r)&&l1<=mid)
			np[i] = p[l1++];
		else np[i] = p[l2++];
	memcpy(p+l,np+l,sizeof(p[0])*(r-l+1));
}
int main()
{
	scanf("%d%lf",&n,&f[0]);
	for(int i = 1;i<= n;i++)
	{
		scanf("%lf%lf%lf",&q[i].a,&q[i].b,&q[i].rate);
		q[i].slope = -q[i].a/q[i].b;
		q[i].pos = i;
	}
	sort(q+1,q+n+1);
	CDQ(1,n);
	printf("%.3lf",f[n]);
	return 0;
}
