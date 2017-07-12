
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1000005;
int q1[N],q2[N],l1,l2,r1,r2;
int m[N],x[N];
int main()
{
	int n,ans = 0;
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
		scanf("%d%d",&m[i],&x[i]);
	int j = 1;
	r1 = r2 = -1;
	for(int i = 1;i<= n;i++)
	{
		while(l1<=r1&&m[i]>m[q1[r1]])r1--;q1[++r1] = i;
		//while(l2<=r2&&x[i]<x[q2[r2]])r2--;q2[++r2] = i;
		while(m[q1[l1]]>x[i]&&j<=n)
		{
			j++;
			while(l1<=r1&&q1[l1]<j)l1++;
			//while(l2<=r2&&q2[l2]<j)l2++;
		}
		ans = max(ans,i-j+1);
	}
	printf("%d\n",ans);
	return 0;
}
