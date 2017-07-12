
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1005;
typedef long long ll;
struct B
{
	ll no,val;
	bool operator <(const B &s)const
	{
		return val>s.val;
	}
}stone[N];
ll a[N],p[70];
int main()
{
	int n;
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
	{
		ll x,y;
		scanf("%lld%lld",&x,&y);
		stone[i].no = x,stone[i].val = y;
	}
	sort(stone+1,stone+1+n);
	for(int i = 1;i<= n;i++)a[i]=stone[i].no;
	ll ans = 0;
	for(int i = 1;i<= n;i++)
	{
		for(int j = 63;j>=0;j--)
			if((a[i]>>j)&1)
			{
				if(!p[j]){p[j] = a[i];break;}
				else a[i]^=p[j];
			}
		if(a[i])ans+=stone[i].val;
	}
	printf("%lld\n",ans);
	return 0;
}
