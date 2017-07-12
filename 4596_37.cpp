
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mod = 1e9+7;
const int N = 20;
const int M = 1005;
ll d[N][N];
int m[N];
int v1[N][N*N],v2[N][N*N];
int n;ll ans;
ll Gauss()
{
	ll res = 1,f = 1;
	for(int i = 1;i<n;i++)
		for(int j = 1;j<n;j++)
			(d[i][j]+=mod)%=mod;
	for(int i = 1;i<n;i++)
	{
		for(int j = i+1;j<n;j++)
		{
			ll A = d[i][i],B = d[j][i];
			while(B)
			{
				ll C = A/B;
				A%=B;
				swap(A,B);
				for(int k = i;k<n;k++)
					d[i][k] = (d[i][k]-C*d[j][k]%mod+mod)%mod;
				for(int k = i;k<n;k++)
					swap(d[i][k],d[j][k]);
				f = -f;
			}
		}
		if(!d[i][i])return 0;
		res = res*d[i][i]%mod;
	}
	return (mod+f*res)%mod;
}
int main()
{
	scanf("%d",&n);
	for(int i = 0;i< n-1;i++)
	{
		scanf("%d",&m[i]);
		for(int j = 1;j<= m[i];j++)
			scanf("%d%d",&v1[i][j],&v2[i][j]);
	}
	for(int sta = 1;sta<1<<(n-1);sta++)
	{
		memset(d,0,sizeof(d));
		int cnt = 0;
		for(int i = 0;i< n-1;i++)
			if(sta&(1<<i))
			{
				cnt++;
				for(int k = 1;k<= m[i];k++)
					d[v1[i][k]][v2[i][k]]--,  
                    d[v2[i][k]][v1[i][k]]--,  
                    d[v1[i][k]][v1[i][k]]++,  
                    d[v2[i][k]][v2[i][k]]++; 
			}
		if((n-cnt)&1)(ans+=Gauss())%=mod;
		else (ans+=mod-Gauss())%=mod;
	}
	printf("%lld\n",ans);
	return 0;
}
