
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int INF = 0x3f3f3f3f;
const int N = 1e5+5;
const int M = 1e6+5;
int f[2][M][2],mn[M],a[N];
int main()
{
	int cas;
	scanf("%d",&cas);
	while(cas--)
	{
		int n;
		scanf("%d",&n);
		for(int i = 1;i<= n;i++)scanf("%d",&a[i]);
		f[0][0][0] = 0,f[0][0][1] = INF;
		int now = 0,nxt = 1,i,j,s,k;
		for(i = 0;i< n;i++)
		{
			for(j = 0;j<= a[i+1];j++)
				f[nxt][j][0]=f[nxt][j][1]=INF;
			for(j = a[i];j>= 0;j--)
			{
				mn[j] = min(f[now][j][0],j==a[i]?INF:mn[j+1]);
				if(j<=a[i+1])
				{
					for(s = 0;s<2;s++)
					f[nxt][a[i+1]-j][0] = min(f[nxt][a[i+1]-j][0],f[now][j][s]+j);
				}else
					f[nxt][0][1] = min(f[nxt][0][1],f[now][j][0]+a[i+1]);
			}
			for(k = a[i+1];k>=0;k--)
				f[nxt][a[i+1]-k][1] = min(f[nxt][a[i+1]-k][1],(k+1>a[i])?INF:(mn[k+1]+k));
			swap(nxt,now);
		}
		int ans1 = min(f[now][0][0],f[now][0][1]);
		for(j = 0;j<= a[n];j++)
			ans1 = min(ans1,f[now][j][0]);
		f[0][0][0] = 0,f[0][0][1] = -INF;
		now = 0,nxt = 1;
		for(i = 0;i< n;i++)
		{
			for(j = 0;j<= a[i+1];j++)
				f[nxt][j][0]=f[nxt][j][1]=-INF;
			for(j = a[i];j>= 0;j--)
			{
				mn[j] = max(f[now][j][0],j==a[i]?-INF:mn[j+1]);
				if(j<=a[i+1])
				{
					for(s = 0;s<2;s++)
					f[nxt][a[i+1]-j][0] = max(f[nxt][a[i+1]-j][0],f[now][j][s]+j);
				}else
					f[nxt][0][1] = max(f[nxt][0][1],f[now][j][0]+a[i+1]);
			}
			for(k = a[i+1];k>=0;k--)
				f[nxt][a[i+1]-k][1] = max(f[nxt][a[i+1]-k][1],(k+1>a[i])?-INF:(mn[k+1]+k));
			swap(nxt,now);
		}
		int ans2 = max(f[now][0][0],f[now][0][1]);
		for(j = 0;j<= a[n];j++)
			ans2 = max(ans2,f[now][j][0]);
		printf("%d %d\n",ans1,ans2);
	}
	return 0;
}
