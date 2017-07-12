
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int mod = 10007;
int Max_lth,maxn = 0,suml = 0;
int lth[50005],sum[50005];
int f[2][50005],n,m;
int line[50005];
bool check(int x)
{
    int tmp=0,sum=0;
    for(int i=1;i<=n;i++)
    {
        sum+=lth[i];
        if(sum>x){tmp++;sum=lth[i];}
        if(tmp>m)return 0;
        if(lth[i]>x)return 0;
    }
    return 1;
}
void solve()
{
	int l = maxn,r = suml+1;
	while(l<r)
	{
		int mid = (l+r)>>1;
		if(check(mid))r = mid;
		else l = mid+1;
	}
	Max_lth = l;
	return ;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= n;i++)
	{
		scanf("%d",&lth[i]);
		sum[i] = sum[i-1]+lth[i];
		suml+=lth[i];
		maxn = max(maxn,lth[i]);
	}
	solve();
	int ans = 0;
	f[0][0] = 1;
	for(int i = 1;i<= m;i++)
	{
		int last = (i-1)&1,now = i&1;
		int l = 1,r = 1,tot = f[last][0];line[1] = 0;
		for(int j = 1;j<= n;j++)
		{
			while(l<=r&&sum[j]-sum[line[l]]>Max_lth)
				{tot = (tot-f[last][line[l++]]+mod)%mod;}
			f[now][j] = tot;
			line[++r] = j;
			tot = (f[last][j]+tot)%mod;
		}
		for(int j = n-1;j>=1;j--)
		{
			if(suml-sum[j]>Max_lth)break;
			ans = (ans+f[now][j])%mod;
		}
		memset(f[last],0,sizeof(f[last]));
	}
	printf("%d %d",Max_lth,ans);
	return 0;
}
