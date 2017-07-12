
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int mod = 1e8+7;
typedef long long ll;
const int N = 2005;
const int MOD = 1880213;
struct Point
{
	int x,y;
	Point(){}
	Point(int _x,int _y):x(_x),y(_y){}
}p[N];
int n,m,k;
bool inmap(const Point &s)
{
	return s.x<=n&&s.x>=0&&s.y<=m&&s.y>=0;
}
struct Hash
{
	int head[MOD],tot;
	int nxt[N],x[N],y[N];
	void add(int a,int b)
	{
		int tmp = ((ll)a*37+b)%MOD;
		++tot;
		nxt[tot] = head[tmp];
		x[tot] = a,y[tot] = b;
		head[tmp] = tot;
	}
	bool check(int a,int b)
	{
		int tmp = ((ll)a*37+b)%MOD;
		for(int i = head[tmp];i;i=nxt[i])
			if(x[i]==a&&y[i]==b)
				return true;
		return false;
	}
}hash;
ll calc(ll x,ll y)
{
	return (x+y)*(y-x+1)>>1;
}
ll Calc(ll x,ll y,ll z)
{
	if(!x || !y || z<2)return 0;
	z = min(z,x+y);
	x = min(x,z-1),y = min(y,z-1);
	ll sum = 0;
	sum = (sum+(ll)(z-y)*y%mod)%mod;
	sum = (sum+calc(z-x,y-1))%mod;
	return sum;
}
ll t1=0,t2=0,t3=0,t4=0;
void calc(const Point &p3,const Point &p4)
{
	if(inmap(p3)&&inmap(p4))
	{
		int tmp = hash.check(p3.x,p3.y)+hash.check(p4.x,p4.y);
		t2++;
		t3+=tmp;
		if(tmp>1)t4++;
	}
}
void Calc(const Point &p1,const Point &p2)
{
	int dx = p2.x-p1.x,dy = p2.y-p1.y;
	calc(Point(p1.x+dy,p1.y-dx),Point(p2.x+dy,p2.y-dx));
	calc(Point(p1.x-dy,p1.y+dx),Point(p2.x-dy,p2.y+dx));
	if(abs(dx+dy)&1)return ;
	dy = (dx+dy)>>1;
	dx-=dy;
	calc(Point(p1.x+dx,p1.y+dy),Point(p2.x-dx,p2.y-dy));
}
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i = 1;i<= k;i++)
	{
		scanf("%d%d",&p[i].x,&p[i].y);
		hash.add(p[i].x,p[i].y);
	}
	ll ans = 0;
	for(int i = 1;i<= n&&i<= m;i++)
		ans = (ans+(ll)i*(n-i+1)%mod*(m-i+1)%mod)%mod;
	for(int i = 1;i<= k;i++)
	{
		(t1+=Calc(p[i].x,n-p[i].x,p[i].y))%=mod;
		(t1+=Calc(p[i].x,n-p[i].x,m-p[i].y))%=mod;
		(t1+=Calc(p[i].y,m-p[i].y,p[i].x))%=mod;
		(t1+=Calc(p[i].y,m-p[i].y,n-p[i].x))%=mod;
		t1 = t1+min(p[i].x,p[i].y)+min(n-p[i].x,p[i].y)+min(p[i].x,m-p[i].y)+min(n-p[i].x,m-p[i].y);
		t1 = t1%mod;
		for(int j = 1;j<i;j++)
			Calc(p[i],p[j]);
	}
	ans = ((((ans-t1+mod)%mod+t2)%mod-t3/3)%mod+mod+t4/6)%mod;
	ans = (ans+mod)%mod;
	printf("%lld\n",ans);
	return 0;
}
