
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
int stack[50005],ans[10000005];
int main()
{
	int top = 0,cnt = 0;
	ll n;
	scanf("%lld",&n);
	for(ll i = 1;i*i<=n;i++)
		if(n%i==0)
			stack[++top]=n/i;
	for(int i = 1;i<= top;i++)
	{
		for(ll j = stack[i];j<=n;j+=stack[i])
		{
			if((j-2)%(n/stack[i])==0)
				ans[++cnt] = (j-1)%n;
			if((j+2)%(n/stack[i])==0)
				ans[++cnt] = (j+1)%n;
		}
	}
	sort(ans+1,ans+cnt+1);
	top = 0;
	for(int i = 1;i<= cnt;i++)
		if(ans[i]!=ans[top])
			ans[++top]=ans[i];
	for(int i = 1;i<= top;i++)
		printf("%d\n",ans[i]);
	return 0;
}
