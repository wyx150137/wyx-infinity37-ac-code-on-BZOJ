
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
ll f[100];
int main()
{
	ll n;
	scanf("%lld",&n);
	f[0] = 0,f[1] = 1;
	int cnt = 1;
	while(f[cnt]<=n)
	{
		++cnt;
		f[cnt] = f[cnt-1]+f[cnt-2];
	}
	while(cnt)
	{
		if(f[cnt]==n)
			return printf("%lld\n",n),0;
		if(n>f[cnt])
			n-=f[cnt];
		cnt--;
	}
	return 0;
}
