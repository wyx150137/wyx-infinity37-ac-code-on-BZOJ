
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 1505;
struct Point
{
	ll x,y;
	Point(){}
	Point(ll x,ll y):x(x),y(y){}
	bool operator ==(const Point &a)const
	{
		return (a.x==x&&a.y==y);
	}
	Point operator -(const Point &a)const
	{
		return Point(x-a.x,y-a.y);
	}
	ll operator *(const Point &a)const
	{
		return x*a.y-y*a.x;
	}
}poi[N];
struct Line
{
	Point *p1,*p2;
	Point midp;
	ll len;
	bool operator==(const Line &a)const
	{
		return (a.len==len&&a.midp==midp);
	}
	bool operator<(const Line &a)const
	{
		if(a.len==len)
		{
			if(a.midp.x==midp.x)
				return midp.y<a.midp.y;
			return midp.x<a.midp.x;
		}
		return len<a.len;
	}
}line[(N*N)>>1];
ll dis(const Point &p1,const Point &p2)
{
	return (p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y);
}
ll Abs(ll x)
{
	return x>0?x:-x;
}
int tot;
int main()
{
	int n;
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
	{
		scanf("%lld%lld",&poi[i].x,&poi[i].y);
		for(int j = 1;j<i;j++)
		{
			line[++tot].len = dis(poi[i],poi[j]);
			line[tot].p1 = &poi[i];
			line[tot].p2 = &poi[j];
			line[tot].midp = Point(poi[i].x+poi[j].x,poi[i].y+poi[j].y);
		}
	}
	sort(line+1,line+tot+1);
	int i,j;
	ll ans = 0;
	for(i = 1;i<= tot;i++)
	{
		for(j = i-1;j&&line[j]==line[i];j--)
			ans = max(ans,Abs( ((*line[i].p1)-(*line[j].p1))*((*line[i].p1)-(*line[j].p2)) ) );
	}
	printf("%lld\n",ans);
	return 0;
}
