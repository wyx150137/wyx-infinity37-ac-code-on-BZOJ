
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 5e4+5;
int ans[N<<1],num[N<<1];
int main()
{
	int n,k;
	scanf("%d%d",&n,&k);
	for(int i = 1;i<= n;i++)
		scanf("%d",&num[i]);
	sort(num+1,num+n+1);
	int j = 0;
	for(int i = 1;i<=n;i++)
	{
		while(num[j]-num[i]<=k&&j<=n)j++;
		ans[i] = j-i;
	}
	int Tans = 0;
	for(int i = n;i>=1;i--)
	{
		Tans = max(Tans,ans[i]+ans[i+ans[i]]);
		ans[i] = max(ans[i],ans[i+1]);
	}
	printf("%d\n",Tans);
	return 0;
}
