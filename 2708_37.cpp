
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;
int a[55],f[55];
int calc(int x,int y)
{
	for(int k = 1;k<= y-x+1;k++)
	{
		for(int j = x;j<= y-k;j++)
			if(abs(a[j]-a[j+k])>1)return k-1;
		if(abs(a[x+k-1]-a[y-k+1])<=1)return k-1;
	}
	return y-x+1;
}
int main()
{
	int n;
	while(scanf("%d",&n)!=EOF)
	{
		for(int i = 1;i<= n;i++)
			scanf("%d",&a[i]);
		sort(a+1,a+n+1);
		memset(f,0,sizeof(f));
		for(int i = 1;i<= n;i++)
			for(int j = 0;j<i;j++)
				f[i] = max(f[i],f[j]+calc(j+1,i));
		printf("%d\n",f[n]);
	}
	return 0;
}
