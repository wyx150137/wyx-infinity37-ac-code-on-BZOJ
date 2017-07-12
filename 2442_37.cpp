
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e5+5;
typedef long long LL;
LL sum[N],f[N];
int line[N],l,r;
int main()
{
	int n,k,x;
	scanf("%d%d",&n,&k);
	for(int i = 1;i<= n;i++)
	{
		scanf("%d",&x);
		sum[i] = sum[i-1]+x;
	}
	line[0] = 0;
	for(int i = 1;i<= n+1;i++)
	{
		while(l<=r&&i-line[l]-1>k)l++;
		if(l<=r)
			f[i] = max(f[i],f[line[l]]-sum[line[l]]+sum[i-1]);
		while(l<=r&&f[i]-sum[i]>f[line[r]]-sum[line[r]])
			r--;
		line[++r] = i;
	}
	printf("%lld\n",f[n+1]);
	return 0;
}
