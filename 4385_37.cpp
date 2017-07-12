
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = 2e6+5;
LL sum[N];
int a[N];
int line[N],L,R;
int main()
{
	int n,d;
	LL p;
	scanf("%d%lld%d",&n,&p,&d);
	for(int i = 1;i<= n;i++)
	{
		scanf("%d",&a[i]);
		sum[i] = sum[i-1]+a[i];
	}
	int i = 0,ans = 0;
	L = 0,R = -1;
	for(int j = d;j<= n;j++)
	{
		while(L<=R&&sum[j]-sum[j-d]>sum[line[R]]-sum[line[R]-d])R--;
		line[++R] = j;
		while(sum[j]-sum[i]-sum[line[L]]+sum[line[L]-d]>p)
		{
			i++;
			if(line[L]-d<i)L++;
		}
		ans = max(ans,j-i);
	}
	printf("%d\n",ans);
	return 0;
}
