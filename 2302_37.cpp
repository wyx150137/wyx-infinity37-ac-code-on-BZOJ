
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 305;
typedef long long ll;
int f[N][N];
int cnt[N],sum[N];
int C[N][N],n,m,x,y,mod;
void Init()
{
	memset(f,0,sizeof(f));
	memset(cnt,0,sizeof(cnt));
	memset(sum,0,sizeof(sum));
	C[0][0] = 1;
	for(int i = 1;i<N;i++)
	{
		C[i][0] = 1;
		for(int j = 1;j<=i;j++)
			C[i][j] = (C[i-1][j-1]+C[i-1][j])%mod;
	}
}
int main()
{
	int cas;
	scanf("%d",&cas);
	//init();
	while(cas--)
	{
		scanf("%d%d%d",&n,&m,&mod);
		Init();
		sum[0] = n-m;
		for(int i = 1;i<= m;i++)
		{
			scanf("%d%d",&x,&y);
			cnt[y]++;
		}
		bool flag = false;
		for(int i = 1;i<= n;i++)
		{
			sum[i] = sum[i-1]+cnt[i];
			if(sum[i]<i)
			{
				puts("NO");
				flag = true;
				break;
			}
		}
		if(flag)continue;
		f[0][0]=1;
		for(int i = 1;i<= n;i++)
			for(int j = i;j<= sum[i];j++)
				for(int k = j-i+1;k>= cnt[i];k--)
					(f[i][j]+=(ll)f[i-1][j-k]*C[sum[i]-cnt[i]-j+k][k-cnt[i]]%mod)%=mod;
		printf("YES %d\n",f[n][n]);
	}
	return 0;
}
