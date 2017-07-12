
#include <stdio.h>
#include <math.h>
#include <set>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 2e5+5;
ll sqr(ll x){return x*x;}
struct Cir
{
	ll x,y,r;
}c[N];
ll T;
struct data
{
	ll num,x,o;
	data(){}
	data(ll _num,ll _x,ll _o):num(_num),x(_x),o(_o){}
	bool operator <(const data &s)const
	{
		double xx = c[num].y+o*sqrt(sqr(c[num].r)-sqr(T-c[num].x));
		double yy = c[s.num].y+s.o*sqrt(sqr(c[s.num].r)-sqr(T-c[s.num].x));
		if(xx!=yy)return xx<yy;
		return o<s.o;
	}
}poi[N<<1];
bool cmp(const data &a,const data &b)
{
	return a.x<b.x;
}
set<data>S;
ll f[N];
int main()
{
	int n;
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
	{
		scanf("%lld%lld%lld",&c[i].x,&c[i].y,&c[i].r);
		poi[(i<<1)-1] = data(i,c[i].x-c[i].r,1);
		poi[i<<1] = data(i,c[i].x+c[i].r,-1);
	}
	sort(poi+1,poi+2*n+1,cmp);
	set<data>::iterator it;
	for(int i = 1;i<= 2*n;i++)
	{
		T = poi[i].x;
		if(poi[i].o==1)
		{
			it = S.upper_bound(data(poi[i].num,0,-1));
			if(it==S.end())f[poi[i].num] = 1;
			else
			{
				if((*it).o==1)f[poi[i].num] = -f[(*it).num];
				else f[poi[i].num] = f[(*it).num];
			}
			S.insert(data(poi[i].num,0,-1));
			S.insert(data(poi[i].num,0,1));
		}else
		{
			S.erase(data(poi[i].num,0,-1));
			S.erase(data(poi[i].num,0,1));
		}
	}
	ll ans = 0;
	for(int i = 1;i<= n;i++)
		ans = ans+f[i]*sqr(c[i].r);
	printf("%lld\n",ans);
	return 0;
}
