
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 505;
typedef long long ll;
const int mod = 1e9+7;
int b[N];
int quick_pow(int x,int y)
{
	int res = 1;
	while(y)
	{
		if(y&1)res = (ll)res*x%mod;
		x = (ll)x*x%mod;
		y>>=1;
	}
	return res;
}
struct P
{
	int a[N];
	int val;
	bool operator <(const P &s)const
	{
		return val<s.val;
	}
}p[N];

int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= n;i++)
		for(int j = 1;j<= m;j++)
			scanf("%d",&p[i].a[j]);
	for(int i = 1;i<= n;i++)scanf("%d",&p[i].val);
	sort(p+1,p+n+1);
	int ans = 0,ansv = 0;
	for(int i = 1;i<= n;i++)
		for(int j = 1;j<= m;j++)
			if(p[i].a[j])
			{
				if(!b[j])
				{
					b[j] = i;
					ans++;
					ansv+=p[i].val;
					break;
				}else
				{
					int tmp = (ll)p[i].a[j]*quick_pow(p[b[j]].a[j],mod-2)%mod;
					for(int k = j;k<= m;k++)
						p[i].a[k]=(p[i].a[k]-(ll)p[b[j]].a[k]*tmp%mod+mod)%mod;
				}
			}
	printf("%d %d\n",ans,ansv);
	return 0;
}
