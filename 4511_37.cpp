
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
int pre[7];
int main()
{
	int sum = 0;
	int n,x,ans = 0;
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
	{
		scanf("%d",&x);
		(sum+=x)%=7;
		if(pre[sum])ans = max(ans,i-pre[sum]);
		else pre[sum] = i;
	}
	printf("%d\n",ans);
	return 0;
}
