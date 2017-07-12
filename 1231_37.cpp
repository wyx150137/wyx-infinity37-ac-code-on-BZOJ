
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int N = 1<<16;
long long f[2][N][17];
int cnt[N],s[17];
int abs(int x){return x<0?-x:x;}
void init()
{
	for(int i = 0;i<N;i++)
	{
		int tmp = i;
		while(tmp)
		{
			tmp-=tmp&(-tmp);
			cnt[i]++;
		}
	}
	return ;
}
int main()
{
	int n,k;
	init();
	scanf("%d%d",&n,&k);
	for(int i = 1;i<= n;i++)
		scanf("%d",&s[i]);
	for(int i = 0;i< n;i++)
		f[1][1<<i][i+1] = 1;
	for(int i = 2;i<= n;i++)
	{
		int I = i&1,I_=(i-1)&1;
		for(int sta = 0;sta<1<<n;sta++)
		{
			if(cnt[sta]!=i-1)continue;
			for(int l = 1;l<= n;l++)
			{
				if(!(sta&(1<<(l-1))))continue;
				for(int t = 1;t<= n;t++)
				{
					if(sta&(1<<(t-1)))continue;
					if(abs(s[t]-s[l])<=k)continue;
					f[I][sta|(1<<(t-1))][t]+=f[I_][sta][l];
				}
			}
		}
		memset(f[I_],0,sizeof(f[I_]));
	}
	long long ans = 0;
	for(int i = 1;i<= n;i++)
		ans+=f[n&1][(1<<n)-1][i];
	printf("%lld\n",ans);
	return 0;
}
