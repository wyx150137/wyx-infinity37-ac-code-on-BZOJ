
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
int n,m;
const int N = 10;
const int M = 1e4+5;
const ll INF = 1e18;
int E1[M][N],E2[M][N];
int A[M][N],B[M][N],a[M][N];
ll f[M][1<<5],trs[M][1<<5][1<<5];
ll calc(int line,int sta)
{
	ll res = 0;
	int d[10]={0};
	for(int i = 1;i<= n;i++)
		d[i] = (sta>>(i-1))&1;
	for(int i = 1;i<= n;i++)
		res+=(d[i]^a[line][i])*B[line][i];
	for(int i = 1;i<= n;i++)
		res+=(d[i]^d[i%n+1])*E1[line][i];
	return res;
}
int main()
{
	int maxx=0;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= n;i++)
		for(int j = 1;j<= m;j++)
			scanf("%d",&A[j][i]),maxx = max(maxx,A[j][i]);
	for(int i = 1;i<= n;i++)
		for(int j = 1;j<= m;j++)
			scanf("%d",&B[j][i]),maxx = max(maxx,B[j][i]);
	for(int i = 1;i<= n;i++)
		for(int j = 2;j<=m;j++)
			scanf("%d",&E2[j][i]),maxx = max(maxx,E2[j][i]);
	for(int i = 1;i<= n;i++)
		for(int j = 1;j<= m;j++)
			scanf("%d",&E1[j][i]),maxx = max(maxx,E1[j][i]);
	int l = 1,cnt=0;
	while(l<=maxx)l<<=1,cnt++;
	//cnt--;
	ll Ans = 0;
	for(int j = 2;j<= m;j++)
		for(int sta = 0;sta<1<<n;sta++)
		{
			for(int pre = 0;pre<1<<n;pre++)
			{
				ll sum = 0;
				for(int i = 0;i< n;i++)
					if(((sta>>i)&1)^((pre>>i)&1))
						sum+=E2[j][i+1];
				trs[j][sta][pre] = sum;
			}
		}
	for(int s = 0;s<cnt;s++)
	{
		for(int j = 1;j<= m;j++)
			for(int i = 1;i<= n;i++)
				a[j][i]=(A[j][i]>>s)&1;
		for(int sta = 0;sta<1<<n;sta++)
			f[1][sta] = calc(1,sta);
		for(int j = 2;j<= m;j++)
			for(int sta = 0;sta<1<<n;sta++)
			{
				f[j][sta] = INF;
				ll tmp = calc(j,sta);
				for(int pre = 0;pre<1<<n;pre++)
					f[j][sta] = min(f[j][sta],f[j-1][pre]+trs[j][sta][pre]+tmp);
			}
		ll tmp = INF;
		for(int i = 0;i<1<<n;i++)
			tmp = min(tmp,f[m][i]);
		Ans += tmp*(1<<s);
	}
	printf("%lld\n",Ans);
	return 0;
}
