
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 50100;
int n,q,size;
int pos[N],c[N];
ll s[N];
ll sqr(ll x){return x*x;}
ll gcd(ll x,ll y)
{
	if(y==0)return x;
	return gcd(y,x%y);
}
struct Ask
{
	int l,r,bel;
	ll up,dwn;
	bool operator <(const Ask &s)const
	{
		if(pos[l]==pos[s.l])return r<s.r;
		else return l<s.l;
	}
}ask[N];
bool cmp(const Ask &a,const Ask &b)
{
	return a.bel<b.bel;
}
ll ans;
void update(int x,int add)
{
	ans-=sqr(s[c[x]]);
	s[c[x]]+=add;
	ans+=sqr(s[c[x]]);
}

int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= n;i++)
		scanf("%d",&c[i]);
	size = sqrt(n)+1;
	for(int i = 1;i<= n;i++)
		pos[i] = i/size;
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d",&ask[i].l,&ask[i].r);
		ask[i].bel = i;
	}
	sort(ask+1,ask+m+1);
	int l = 1,r = 0;
	for(int i = 1;i<= m;i++)
	{
		while(r<ask[i].r)r++,update(r,1);
		while(r>ask[i].r)update(r,-1),r--;
		while(l>ask[i].l)l--,update(l,1);
		while(l<ask[i].l)update(l,-1),l++;
		if(ask[i].l==ask[i].r)
			ask[i].up = 0,ask[i].dwn = 1;
		else
		{
			ask[i].up = ans-(ask[i].r-ask[i].l+1);
			ask[i].dwn = (ll)(ask[i].r-ask[i].l+1)*(ask[i].r-ask[i].l);
			ll g = gcd(ask[i].up,ask[i].dwn);
			ask[i].up/=g,ask[i].dwn/=g;
		}
	}
	sort(ask+1,ask+m+1,cmp);
	for(int i = 1;i<= m;i++)
		printf("%lld/%lld\n",ask[i].up,ask[i].dwn);
	return 0;
}
