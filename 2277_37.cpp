
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = 250005;
LL gcd(LL x,LL y)
{
	if(y==0)return x;
	return gcd(y,x%y);
}
LL stack[N],top,a[N],n,k;
int main()
{
	scanf("%lld%lld",&n,&k);
	for(int i = 1;i<= k;i++)
	{
		scanf("%lld",&a[i]);
		if(i!=k)stack[++top] = gcd(a[i],n);
	}
	sort(stack+1,stack+top+1);
	int tmp = top,top = 0;
	for(int i = 1;i<= tmp;i++)
		if(stack[top]!=stack[i])
			stack[++top] = stack[i];
	LL m = gcd(n,a[k]);
	LL ans = m;
	for(LL i = 1;i*i<=m;i++)
	{
		if(m%i==0)
		{
			int j;
			for(j = 1;j<= top;j++)
				if(stack[j]%i==0)
					break;
			if(j==top+1){ans = min(ans,i);break;}
			LL k = m/i;
			for(j = 1;j<= top;j++)
				if(stack[j]%k==0)
					break;
			if(j==top+1)ans = min(ans,k);
		}
	}
	printf("%lld\n",n/ans);
	return 0;
}
