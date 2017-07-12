
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e5+5;
int n,X,Y;
struct Line
{
	int x,y;
	Line(){}
	Line(int _x,int _y):x(_x),y(_y){}
	bool operator <(const Line &s)const
	{
		bool pd = ((x<0)^(s.x<0));
		return pd?y*s.x>x*s.y:y*s.x<x*s.y;
	}
}k1[N],k2[N];
int tot1,tot2,L1,L2,ans1,ans2;
int cur0[2],cur1[2];
int main()
{
	int a,b;
	scanf("%d%d%d",&n,&X,&Y);n--;
	for(int i = 1;i<= n;i++)
	{
		scanf("%d%d",&a,&b);
		if(a<X)k1[++tot1] = Line(X-a,b-Y);
		else if(a>X)k2[++tot2] = Line(X-a,b-Y);
		else
		{
			if(b<Y)L1++,L2++;
			else if(b==Y)L1++;
		}
		cur1[0]+=a<=X;
		cur1[1]+=a<X;
		cur0[0]+=b<=Y;
		cur0[1]+=b<Y;
	}
	sort(k1+1,k1+tot1+1);sort(k2+1,k2+tot2+1);
	ans1 = 0,ans2 = n+4;
	for(int i = 1;i<= tot1;i++)
	{
		if(k1[i].x*k1[i].y<0)continue;
		a = i-1,b = i;
		int p1 = lower_bound(k2+1,k2+tot2+1,k1[i])-k2;
		int p2 = upper_bound(k2+1,k2+tot2+1,k1[i])-k2;
		a+=(tot2-p2+1),b+=(tot2-p1+1);
		ans1 = max(ans1,b),ans2 = min(ans2,a);
	}
	for(int i = 1;i<= tot2;i++)
	{
		if(k2[i].x*k2[i].y<0)continue;
		a = tot2-i,b = tot2-i+1;
		int p1 = lower_bound(k1+1,k1+tot1+1,k2[i])-k1;
		int p2 = upper_bound(k1+1,k1+tot1+1,k2[i])-k1;
		a+=(p1-1),b+=(p2-1);
		ans1 = max(ans1,b),ans2 = min(ans2,a);
	}
	ans1+=L1,ans2+=L2;
	ans1 = max(ans1,max(cur1[0],cur0[0]));
	ans2 = min(ans2,min(cur1[1],cur0[1]));
	printf("%d %d\n",n+1-ans1,n+1-ans2);
	return 0;
}
