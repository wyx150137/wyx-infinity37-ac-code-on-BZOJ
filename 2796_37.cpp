
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long LL;
LL f[100];
int solve(LL x)
{
	if(!x)return 0;
	int i = 1;
	while(f[i]<x)i++;
	if(f[i]==x)return 1;
	return solve(min(f[i]-x,x-f[i-1]))+1;
}
int main()
{
	f[1] = f[2] = 1;
	for(int i = 3;i<= 95;i++)f[i] = f[i-1]+f[i-2];
	int T;
	scanf("%d",&T);
	while(T--)
	{
		LL n;
		scanf("%lld",&n);
		printf("%d\n",solve(n));
	}
	return 0;
}
