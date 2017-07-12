
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 3000005;
int q1[N],q2[N],l1,l2,r1,r2;
int a[N];
int main()
{
	int n,k,ans = 0;
	scanf("%d%d",&k,&n);
	for(int i = 1;i<= n;i++)
		scanf("%d",&a[i]);
	int j = 1;
	r1 = r2 = -1;
	for(int i = 1;i<= n;i++)
	{
		while(l1<=r1&&a[q1[r1]]<a[i])r1--;q1[++r1] = i;
		while(l2<=r2&&a[q2[r2]]>a[i])r2--;q2[++r2] = i;
		while(a[q1[l1]]-a[q2[l2]]>k)
		{
			j++;
			while(l1<=r1&&q1[l1]<j)l1++;
			while(l2<=r2&&q2[l2]<j)l2++;
		}
		ans = max(ans,i-j+1);
	}
	printf("%d\n",ans);
	return 0;
}
