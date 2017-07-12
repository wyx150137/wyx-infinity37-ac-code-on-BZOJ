
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 605;
const int K = 65;
int f[K][N];
int sum[N][N],pre[N][K];
int s(int x1,int y1,int x2,int y2)
{
	return sum[x2][y2]-sum[x1][y2]-sum[x2][y1]+sum[x1][y1];
}
int main()
{
	int n,K;
	scanf("%d%d",&n,&K);
	for(int i = 1;i<n;i++)
		for(int j = 1;i+j<= n;j++)
			scanf("%d",&sum[i][j+i]);
	for(int i = 1;i<= n;i++)
		for(int j = 1;j<= n;j++)
			sum[i][j] += sum[i][j-1];
	for(int i = 1;i<= n;i++)
		for(int j = 1;j<= n;j++)
			sum[i][j]+=sum[i-1][j];
	memset(f,0xef,sizeof(f));
	f[0][0] = 0;
	for(int i = 1;i< n;i++)
		for(int j = 1;j<= K;j++)
			for(int k = 0;k<i;k++)
			{
				//f[i][j][k] = max(f[i][j][k],f[i-1][j][k]);
				int tmp = f[j-1][k]+s(k,i,i,n);
				if(tmp>f[j][i])
				{
					pre[i][j] = k;
					f[j][i] = tmp;
				}
			}
	int ans = 0xefefefef;
	int tmp = 0;
	for(int k = 0;k<= n;k++)
	{
		if(f[K][k]>ans)
			ans = f[K][k],tmp = k;
	}
	int stack[605],top=0;
	while(top<K)
	{
		stack[++top] = tmp;
		tmp = pre[tmp][K-top+1];
	}
	//printf("%d\n",ans);
	for(int i = top;i> 1;i--)
		printf("%d ",stack[i]);
	printf("%d\n",stack[1]);
	return 0;
}
