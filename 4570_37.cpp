
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e6+5;
const double eps = 1e-8;
const double INF = 1e20;
typedef long long ll;
struct P
{
	double x,y;
	P(double _x=0,double _y=0):x(_x),y(_y){}
	bool operator <(const P &s)const
	{
		if(x==s.x)return y>s.y;
		return x<s.x;
	}
	friend P operator -(const P &a,const P &b)
	{
		return P(a.x-b.x,a.y-b.y);
	}
	friend double operator *(const P &a,const P &b)
	{
		return a.x*b.y-a.y*b.x;
	}
}p[N],stack[N];
int top;
double slope(const P &a,const P &b)
{
	if(fabs(a.x-b.x)<eps)return -INF;
	else return (b.y-a.y)/(b.x-a.x);
}
double slope(const P &a)
{
	return -sqrt(a.y/a.x);
}
double calc(const P &a,double k)
{
	if(k>-eps)return INF;
	else return a.x+a.y-a.x*k-a.y/k;
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
		scanf("%lf%lf",&p[i].x,&p[i].y);
	sort(p+1,p+n+1);
	stack[++top] = p[1];
	for(int i = 2;i<= n;i++)
	{
		while(top>1&&(p[i]-stack[top])*(stack[top]-stack[top-1])<-eps)
			top--;
		stack[++top] = p[i];
	}
	double ans;
	if(top==1)ans = calc(stack[1],slope(stack[1]));
	else
	{
		double sp,sp1,sp2;
		ans = INF;
		sp2 = slope(stack[1],stack[2]),sp = slope(stack[1]);
		if(sp+eps>sp2)ans = min(ans,calc(stack[1],sp));
		for(int i = 2;i<top;i++)
		{
			sp1 = slope(stack[i-1],stack[i]);
			sp2 = slope(stack[i],stack[i+1]);
			sp = slope(stack[i]);
			ans = min(ans,calc(stack[i],sp1));
			if(sp1+eps>sp&&sp+eps>sp2)ans = min(ans,calc(stack[i],sp));
		}
		sp1 = slope(stack[top-1],stack[top]),sp = slope(stack[top]);
		ans = min(ans,calc(stack[top],sp1));
		if(sp1+eps>sp)ans = min(ans,calc(stack[top],sp));
	}
	printf("%.4f\n",ans);
	return 0;
}
