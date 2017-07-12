
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = 1e5+5;
int c[N<<1];
int q[N],l,r;
int main()
{
	int n;
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
	{
		scanf("%d",&c[i]);
		c[i+n] = c[i];
	}
	int last = 0,sum = 0,st = 0,beg = 0;
	for(int i = 1;i<= 2*n;i++)
	{
		if(last<0)
			last = 0,beg = i;
		last+=c[i]-1;
		if(last>sum)
			sum = last,st = beg;
	}
	LL ans = 0;
	r = -1;
	for(int i = st;i<st+n;i++)
	{
		while(c[i]--)
			q[++r] = i;
		ans+=(LL)(i-q[l])*(i-q[l]);
		l++;
	}
	printf("%lld",ans);
	return 0;
}
