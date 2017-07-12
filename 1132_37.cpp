
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 3005;
struct Point
{
	int x,y;
	double sl;
	Point(){}
	Point(int x,int y):x(x),y(y)
	{
		sl = x?(double)y/x:1e10;
	}
	bool operator<(const Point &a)const
	{
		if(x==a.x)
			return y<a.y;
		return x<a.x;
	}
	Point operator-(const Point &a)const
	{
		return Point(x-a.x,y-a.y);
	}
}a[N],poi[N];
bool cmp(const Point &a,const Point &b)
{
	return a.sl<b.sl;
}
int main()
{
	int n,tot;
	ll ans = 0;
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
		scanf("%d%d",&a[i].x,&a[i].y);
	sort(a+1,a+n+1);
	for(int i = 1;i<= n;i++)
	{
		tot = 0;
		ll sumx = 0,sumy = 0;
		for(int j = i+1;j<= n;j++)
			poi[++tot]=a[j]-a[i];
		sort(poi+1,poi+tot+1,cmp);
		for(int j = 1;j<= tot;j++)
		{
			ans+=sumx*poi[j].y-sumy*poi[j].x;
			sumx+=poi[j].x;
			sumy+=poi[j].y;
		}
	}
	printf("%lld.%d",ans>>1,(ans&1)?5:0);
	return 0;
}
