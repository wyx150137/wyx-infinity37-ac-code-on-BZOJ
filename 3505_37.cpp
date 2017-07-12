
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long LL;
int gcd(int x,int y)
{
	if(x==0)return y;
	return gcd(y%x,x);
}
int main()
{
	LL n,m;
	scanf("%lld%lld",&n,&m);
	n++;m++;
	LL ans = n*m*(n*m-1)*(n*m-2);
	ans = ans/(LL)6;
	for(int i = 0;i< n;i++)
	{
		for(int j = 0;j< m;j++)
		{
			LL len = min(i,j);
			if(!i)len = j-1;
			if(!j)len = i-1;
			if(i&&j)len = gcd(i,j)-1;
			len = max(0ll,len);
			if(len==0)continue;
			if(i&&j)ans-=len*(n-i)*(m-j)*2;
			else ans-=len*(n-i)*(m-j);
		}
	}
	printf("%lld\n",ans);
	return 0;
}
