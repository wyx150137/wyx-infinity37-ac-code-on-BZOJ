
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#define N 1000+5
using namespace std;

int a[N];
int f[N];

int calc(int x,int y)
{
	for(int k=1;k<=y-x+1;k++)
	{
		for(int i=k;i<=y-x;i++)
			if(abs(a[i+x]-a[i+x-k])>1)
				return k-1;
		if(abs(a[x+k-1]-a[y-k+1])<=1)
			return k-1;
	}
    return y-x+1;
}


int main()
{
	
	int n;
	while(~scanf("%d",&n))
	{
		for(int i=1;i<=n;++i)
			scanf("%d",a+i);
		sort(a+1,a+n+1);
		memset(f,0,sizeof f);
		for(int i=1;i<=n;++i)
			for(int j=0;j<i;++j)
				f[i] = max(f[i],f[j] + calc(j+1,i));

		cout<<f[n]<<endl;
	}
}
