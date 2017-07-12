
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 1e7+5;
int a[N];
int main()
{
	int n;
	ll ans = 0;
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
		scanf("%d",&a[i]),ans+=a[i];
	sort(a+1,a+n+1);
	if(n==1)
	{
		if(a[1]%2==1)printf("NIESTETY\n");
		else printf("%d\n",a[1]);
	}
	else
	{
		if(ans%2==0)printf("%lld\n",ans);
		else
		{
			for(int i = 1;i<= n;i++)
				if(a[i]%2==1)
					{ans-=a[i];break;}
			printf("%lld\n",ans);
		}
	}
	return 0;
}
