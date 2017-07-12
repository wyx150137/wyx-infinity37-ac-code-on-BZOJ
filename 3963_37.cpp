
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 1e5+5;
struct data
{
	int d,p,r,g,id;
	ll x,y;
	void read()
	{
		scanf("%d%d%d%d",&d,&p,&r,&g);
		x = g,y = r-p-(ll)d*g-g;
	}
}a[N],t[N];
struct Point
{
	ll x,y;
	Point(ll _x=0,ll _y=0):x(_x),y(_y){}
	friend Point operator -(const Point &a,const Point &b)
	{return Point(a.x-b.x,a.y-b.y);}
	friend double operator *(const Point &a,const Point &b)
	{return (double)a.x*b.y-(double)a.y*b.x;}
}ch[N],p[N];
ll f[N];
inline bool cmp1(const data &a,const data &b)
{return a.d<b.d;}
inline bool cmp2(int i,int j)
{return a[i].x==a[j].x?a[i].y+f[a[i].id]<a[j].y+f[a[j].id]:a[i].x<a[j].x;}
inline ll Val(ll k,const Point &p){return k*p.x+p.y;}
void solve(int l,int r)
{
	if(l==r){f[l] = max(f[l-1],f[l]);return ;}
	int mid = (l+r)>>1;
	solve(l,mid);
	int n = 0,m = 0;
	for(int i = l;i<= mid;i++)if(f[a[i].id]>=a[i].p)
		p[++n] = Point(a[i].x,a[i].y+f[a[i].id]);
	for(int i = 1;i<= n;i++)
	{
		while(m>1&&(ch[m]-ch[m-1])*(p[i]-ch[m-1])>=0)m--;
		ch[++m] = p[i];
	}
	int j = 1;
	for(int i = mid+1;i<= r;i++)
	{
		while(j<m&&Val(a[i].d,ch[j+1])>=Val(a[i].d,ch[j]))j++;
		if(j<=m)f[i] = max(f[i],Val(a[i].d,ch[j]));
	}
	solve(mid+1,r);
	int p1 = l,p2 = mid+1;
	for(int i = l;i<=r;i++)
	{
		if(p2>r||(p1<=mid&&cmp2(p1,p2)))t[i]=a[p1++];
		else t[i] = a[p2++];
	}
	for(int i = l;i<= r;i++)a[i]=t[i];
}
int main()
{
	int n,d;
	int cas = 0;
	while(scanf("%d%lld%d",&n,&f[0],&d)!=EOF)
	{
		if(n==0&&f[0]==0&&d==0)break;
		for(int i = 1;i<= n;i++)a[i].read();
		a[++n].d = d+1;
		sort(a+1,a+n+1,cmp1);
		for(int i = 1;i<= n;i++)a[i].id = i,f[i] = 0;
		solve(1,n);
		printf("Case %d: %lld\n",++cas,f[n]);
	}
	return 0;
}
