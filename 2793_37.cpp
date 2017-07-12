
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e6+5;
const int INF = 1e6;
bool is_luck[N],v[N];
int mn[N],cnt;
long long ans[N];
int main()
{
	int m,x;
	scanf("%d",&m);
	for(int i = 1;i<= m;i++)
	{
		scanf("%d",&x);
		is_luck[x] = true;
	}
	int n;
	long long tot = 0;
	scanf("%d",&n);
	v[0] = true;
	for(int i = 1;i<= n;i++)
	{
		scanf("%d",&x);
		for(int j = 1;j<= x;j++)
		{
			while(mn[x]*x<=INF&&v[mn[x]*x])mn[x]++;
			if(mn[x]*x>INF)break;
			v[mn[x]*x] = true;
			if(is_luck[mn[x]*x])ans[++cnt] = tot+j;
		}
		tot+=x;
	}
	printf("%d\n",cnt);
	for(int i = 1;i<= cnt;i++)
		printf("%lld\n",ans[i]);
	return 0;
}
