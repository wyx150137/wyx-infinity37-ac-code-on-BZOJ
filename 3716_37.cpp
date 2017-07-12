
#include <stdio.h>
#include <set>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 200005;
int n,m;
ll w,h,x,y,v,ans;
struct data
{
	ll x,y,v;
	bool operator<(const data &s)const
	{
		if(x==s.x)return y<s.y;
		return x<s.x;
	}
}p[N<<1];
struct Data
{
	ll y,v;
	bool operator<(const Data &s)const
	{
		return y<=s.y;
	}
};
set<Data>s;
set<Data>::iterator it;
int main()
{
	scanf("%d%d%lld%lld",&n,&m,&w,&h);
	for(int i = 1;i<= n;i++)
	{
		scanf("%lld%lld%lld",&x,&y,&v);
		x = x*h,y = y*w;
		p[i].x = x+y,p[i].y = y-x,p[i].v=v;
	}
	for(int i = 1;i<= m;i++)
	{
		scanf("%lld%lld%lld",&x,&y,&v);
		x = x*h,y = y*w;
		p[n+i].x = x+y,p[n+i].y = y-x,p[n+i].v=-v;
	}
	sort(p+1,p+m+n+1);
	for(int i = 1;i<= n+m;i++)
		for(y=p[i].y,v=p[i].v;v;ans-=it->v,v+=it->v,s.erase(it))
		{
			it = s.lower_bound((Data){y,0});
			if(it==s.end()||it->y!=y)
			{
				if(v>0){s.insert((Data){y,v});ans+=v;break;}
				else if(it==s.begin())break;
				else y = (--it)->y;
			}
		}
	printf("%lld\n",ans);
	return 0;
}
