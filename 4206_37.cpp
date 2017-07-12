
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int N = 2005;
const double PI = acos(-1.0);
const double INF = 1e18;
double R,x,y,len,ang1,ang2;
double stack[N];
int top;
struct Point
{
	double x,y;
	bool flag;
	bool operator <(const Point &s)const
	{
		if(flag==s.flag)
		{
			if(x==s.x)return y<s.y;
			return x<s.x;
		}
		return flag<s.flag;
	}
}p[N];
double getdis(double x,double y)
{
	return sqrt(x*x+y*y);
}
int Find(double x)
{
	int l = 0,r = top,ans = 0;
	while(l<=r)
	{
		int mid = (l+r)>>1;
		if(stack[mid]>=x)ans = mid,r = mid-1;
		else l = mid+1;
	}
	return ans;
}
int main()
{
	int n;
	scanf("%d%lf",&n,&R);
	for(int i = 1;i<= n;i++)
	{
		scanf("%lf%lf",&p[i].x,&p[i].y);
		if(getdis(p[i].x,p[i].y)<R)
		{
			p[i].flag = true;
			continue;
		}
		ang1 = atan2(p[i].y,p[i].x),ang2 = acos(R/getdis(p[i].x,p[i].y));
		p[i].x = ang1-ang2;p[i].y = ang1+ang2;
		if(p[i].y>PI)p[i].y-=PI*2,swap(p[i].x,p[i].y);
		if(p[i].x<-PI)p[i].x+=PI*2,swap(p[i].x,p[i].y);
	}
	sort(p+1,p+n+1);
	for(int i = 1;i<= n;i++)
		if(p[i].flag)
			{n = i-1;break;}
	stack[0] = -INF;
	int ans = 0;
	for(int i = 1;i<= n;i++)
	{
		stack[top=1]=p[i].y;
		for(int j = i+1;j<= n;j++)
		{
			if(p[j].x>p[i].y)break;
			if(p[j].y>stack[top])
				stack[++top] = p[j].y;
			else
			{
				int tmp = Find(p[j].y);
				if(tmp!=1)stack[tmp]=p[j].y;
			}
		}
		ans = max(ans,top);
	}
	printf("%d\n",ans);
	return 0;
}
