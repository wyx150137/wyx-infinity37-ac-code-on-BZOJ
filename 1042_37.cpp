
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
int c[5],n[5],s;
long long f[100005],w[5];
long long getans(int sta)
{
	int tmp = s;
	long long fh = 1;
	for(int i = 0;i<4;i++)
		if((sta&(1<<i))!=0)
			{tmp-=w[i+1];fh = -fh;}
	if(tmp>=0)return fh*f[tmp];
	else return 0;
}
int main()
{
	int tot;
	for(int i = 1;i<= 4;i++)
		scanf("%d",&c[i]);
	scanf("%d",&tot);
	while(tot--)
	{
		memset(f,0,sizeof(f));
		for(int i = 1;i<= 4;i++)
			scanf("%d",&n[i]);
		scanf("%d",&s);
		for(int i = 1;i<= 4;i++)
			w[i] = c[i]*(n[i]+1);
		f[0] = 1;
		for(int i = 1;i<= 4;i++)
			for(int j = 0;j<= s;j++)
				if(j-c[i]>=0)f[j] += f[j-c[i]];
		long long ans = f[s];
		for(int i = 1;i<1<<4;i++)
			ans+=getans(i);
		printf("%lld\n",ans);
	}
	return 0;
}
