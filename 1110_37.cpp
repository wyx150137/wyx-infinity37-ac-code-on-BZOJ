
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e5+5;
int a[N],w[N],cnt[N],stack[N],top;
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= n;i++)scanf("%d",&w[i]);
	for(int i = 1;i<= m;i++)scanf("%d",&a[i]);
	sort(a+1,a+m+1);
	int top = 0;
	for(int i = 1;i<= m;i++)
		if(i==1||a[i]!=a[i-1])
			stack[++top] = a[i];
	for(int i = 1;i<= n;i++)
		for(int j = top;j;j--)
			cnt[j]+=w[i]/stack[j],w[i]%=stack[j];
	int i,j,k;
	int ans = 0;
	for(i=1,j=1;i<=top;i++)
	{
		for(;j<=m&&a[j]==stack[i];j++)
		{
			if(cnt[i])
			{
				ans++,cnt[i]--;
				continue;
			}
			for(k=i+1;k<= top;k++)
				if(cnt[k])
					break;
			if(k==top+1)
			{
				printf("%d\n",ans);
				return 0;
			}
			for(;k>i;k--)  
                cnt[k]--,cnt[k-1]+=stack[k]/stack[k-1];  
            ++ans;--cnt[i];  
		}	
	}
	printf("%d\n",ans);
	return 0;
}
