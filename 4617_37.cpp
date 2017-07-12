
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 2.5e5+5;
struct Point
{
	int x,y;
	Point(){}
	Point(int _x,int _y):x(_x),y(_y){}
	friend Point operator +(const Point &a,const Point &b)
	{return Point(a.x+b.x,a.y+b.y);}
	friend Point operator -(const Point &a,const Point &b)
	{return Point(a.x-b.x,a.y-b.y);}
	friend void operator -=(Point &a,const Point &b)
	{a = a-b;}
	friend ll operator *(const Point &a,const Point &b)
	{return 1ll*a.x*b.y-1ll*a.y*b.x;}
	friend Point operator *(const Point &a,int k)
	{return Point(a.x*k,a.y*k);} 
	friend bool operator ==(const Point &a,const Point &b)
	{return a.x==b.x&&a.y==b.y;}
	friend bool operator !=(const Point &a,const Point &b)
	{return a.x!=b.x||a.y!=b.y;}
}a[N],b[N],c[N<<1];
int cnta,cntb,m,n,cnt,ce;
struct E
{
	Point o;int t;
	E(){}
	E(Point _o,int _t):o(_o),t(_t)
	{
		if(o.x<0)o = o*-1;
	}
}e[N<<1];
inline bool cmp1(const Point &x,const Point &y)
{return x.x==y.x?x.y<y.y:x.x<y.x;}
inline bool cmp2(const E &a,const E &b)
{return a.o*b.o<0ll;}
int get_convexhull(Point *p,int n,Point *q)
{
	int k,m;
	m = 0;
	for(int i = 0;i<n;q[m++]=p[i++])
		while(m>1&&(q[m-1]-q[m-2])*(p[i]-q[m-2])<=0)m--;
	k = m;
	for(int i = n-2;~i;q[m++]=p[i--])
		while(m>k&&(q[m-1]-q[m-2])*(p[i]-q[m-2])<=0)m--;
	return --m;
}
bool P_on_Seg(const Point &p,const Point &a,const Point &b)
{
	return (b-a)*(p-a)==0&&
	1ll*(p.x-a.x)*(p.x-b.x)+1ll*(p.y-a.y)*(p.y-b.y)<=0;
}
int getl(int l,int r,const Point &p)
{
	int ret = l++,mid;
	while(l<=r)
	{
		mid = (l+r)>>1;
		if((c[mid]-p)*(c[(mid-1+n)%n]-c[mid])<=0)l=(ret=mid)+1;
		else r = mid-1;
	}
	return ret;
}
int getr(int l,int r,const Point &p)
{
	int ret = r--,mid;
	while(l<=r)
	{
		mid = (l+r)>>1;
		if((c[mid]-p)*(c[(mid+1)%n]-c[mid])>=0)r=(ret=mid)-1;
		else l = mid+1;
	}
	return ret;
}
void solve(const Point &p)
{
	if(P_on_Seg(p,c[0],c[n-1]))
		{cnt++;return ;}
	int o = 0;
	if(p.x>0)
	{
		int l = 1,r = n-1,mid;
		while(l<=r)
		{
			mid = (l+r)>>1;
			if(c[mid]*p>=0)l=(o=mid)+1;
			else r = mid-1;
		}
	}else if(p.y>0)o = n-1;
	if(p.x>=0&&(p-c[o])*(c[o+1]-p)<0){cnt++;return ;}
	if(p.x>=0&&P_on_Seg(p,c[o],c[o+1])){cnt++;return ;}
	int l,r;
	if(p.x>0)l = getl(0,o,p),r = getr(o,n,p);
	else l = getl(m,n,p),r = getr(0,m,p);
	e[++ce] = E(p-c[l],1);
	e[++ce] = E(p-c[r],-1);
	if(cmp2(e[ce],e[ce-1]))cnt++;
}
int main()
{
	int x,y,opt;
	scanf("%d",&n);
	while(n--)
	{
		scanf("%d%d%d",&x,&y,&opt);
		if(opt)a[++cnta] = Point(x,y);
		else b[++cntb] = Point(x,y);
	}
	if(cnta==1)
	{
		printf("1");
		return 0;
	}
	sort(a+1,a+cnta+1,cmp1);
	cnt = cnta;cnta = 0;
	for(int i = 1;i<= cnt;i++)
		if(a[i]!=a[i-1]||i==1)
			a[++cnta]=a[i];
	if(cnta==1)
	{
		for(int i = 1;i<= cntb;i++)
			if(a[1]==b[i])cnt++;
		printf("%d\n",cnt);return 0;
	}
	if(cnta==2)
	{
		for(int i = 1;i<= cntb;i++)
			if(P_on_Seg(b[i],a[1],a[2]))
				cnt++;
		printf("%d\n",cnt);return 0;
	}
	n = get_convexhull(a+1,cnta,c);
	for(int i = 1;i<n;i++)c[i]-=c[0];
	for(int i = 1;i<= cntb;i++)b[i]-=c[0];
	c[0]-=c[0];
	for(int i = 0;i<n;i++)if(c[i].x>=c[m].x)m=i;
	for(int i = 0;i<n;i++)c[i+n]=c[i];
	for(int i = 1;i<= cntb;i++)solve(b[i]);
	sort(e+1,e+ce+1,cmp2);
	int ret=0,mv=0,j;
	for(int i = 1;i<= ce;i=j)
	{
		for(j=i;j<=ce&&e[i].o*e[j].o==0;j++)
			ret+=e[j].t;
		if(ret<mv)mv = ret;
	}
	printf("%d\n",cnt+mv);
	return 0;
}
