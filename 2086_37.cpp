
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e6+5;
typedef long long LL;
int stack[N],top;
int a[N];
LL sum[N];
int main()
{
	int n,m,k;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= n;i++)
		scanf("%d",&a[i]);
	while(m--)
	{
		scanf("%d",&k);
		for(int i = 1;i<= n;i++)
			sum[i] = sum[i-1]+a[i]-k;
		for(int i = 1;i<= n;i++)
			if(sum[i]<sum[stack[top]])
				stack[++top] = i;
		int ans = 0;
		for(int i = n;i>=0;i--)
		{
			while(top&&sum[i]>=sum[stack[top-1]])top--;
			ans = max(ans,i-stack[top]);
		}
		if(m)printf("%d ",ans);
		else printf("%d\n",ans);
	}
	return 0;
}
