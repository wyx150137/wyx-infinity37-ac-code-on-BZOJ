
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e5+5;
const int INF = 0x3f3f3f3f;
typedef long long ll;
struct P
{
	ll x,y;
	P(){}
	P(ll x,ll y):x(x),y(y){}
	bool operator <(const P &s)const
	{
		if(x!=s.x)
			return x< s.x;
		return y<s.y;
	}
}p[N];
int n;
ll max_y=-INF,min_y=INF,area;
void get_area()
{
	static P *stack[N];
	int i,top=0;
	for(i=1;i<=n;i++)
	{
		if(!top||p[i].y>=stack[top]->y)
			stack[++top] = &p[i];
		if(p[i].y==max_y)
			break;
	}
	for(i++;i<=n;i++)
	{
		while(p[i].y>stack[top]->y)
			stack[top--]=NULL;
		stack[++top] = &p[i];
	}
	for(i = 2;i<= top;i++)
		area+=min(stack[i]->y,stack[i-1]->y)*(stack[i]->x-stack[i-1]->x);
	top = 0;
	for(i=1;i<= n;i++)
	{
		if(!top||p[i].y<=stack[top]->y)
			stack[++top] = &p[i];
		if(p[i].y==min_y)
			break;
	}
	for(i++;i<=n;i++)
	{
		while(p[i].y<stack[top]->y)
			stack[top--]=NULL;
		stack[++top] = &p[i];
	}
	for(i = 2;i<= top;i++)
		area-=max(stack[i]->y,stack[i-1]->y)*(stack[i]->x-stack[i-1]->x);
}
int main()
{
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
	{
		scanf("%lld%lld",&p[i].x,&p[i].y);
		max_y = max(max_y,p[i].y);
		min_y = min(min_y,p[i].y);
	}
	sort(p+1,p+n+1);
	printf("%lld\n",(max_y-min_y+p[n].x-p[1].x)<<1);
	get_area();
	printf("%lld\n",area);
	return 0;
}
