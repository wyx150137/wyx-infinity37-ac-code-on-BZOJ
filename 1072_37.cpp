
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = 1005;
const int M = 1<<10;
int f[M][N],buk[10],cnt[M];
LL p10[11];
char str[20];
void init()
{
	for(int i = 0;i<M;i++)
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
	int d,n,t;
	init();
	p10[0] = 1;
	for(int i = 1;i<= 10;i++)
		p10[i] = p10[i-1]*10;
	scanf("%d",&t);
	while(t--)
	{
		memset(buk,0,sizeof(buk));
		memset(f,0,sizeof(f));
		scanf("%s%d",str+1,&d);
		n = strlen(str+1);
		for(int i = 1;i<= n;i++)
			buk[str[i]-'0']++;
		f[0][0] = 1;
		for(int i = 1;i<= n;i++)
		{
			for(int sta = 0;sta<1<<n;sta++)
			{
				if(cnt[sta]!=i-1)continue;
				for(int s = 1;s<= n;s++)
				{
					if((1<<(s-1))&sta)continue;
					for(int yu = 0;yu<d;yu++)
					{
						LL nm = ((str[s]-'0')*p10[i-1]+yu)%d;
						f[sta|(1<<(s-1))][nm]+=f[sta][yu];
					}
				}
			}
		}
		int ans = f[(1<<n)-1][0];
		for(int i = 0;i<=9;i++)
			for(int j = buk[i];j>=1;j--)
				ans/=j;
		printf("%d\n",ans);
	}
	return 0;
}
