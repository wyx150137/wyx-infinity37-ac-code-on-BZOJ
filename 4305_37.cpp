
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mod = 1e9+7;
const int N = 3e5+5;
int quick_pow(int x,int y)
{
	int res = 1;
	while(y)
	{
		if(y&1)res = (ll)res*x%mod;
		x = (ll)x*x%mod;
		y>>=1;
	}
	return res;
}
int fac[N],inv[N];
void init()
{
	fac[0] = inv[0] = 1;
	for(int i = 1;i<N;i++)fac[i]=(ll)fac[i-1]*i%mod;
	inv[N-1] = quick_pow(fac[N-1],mod-2);
	for(int i = N-2;i>= 1;i--)inv[i] = (ll)inv[i+1]*(i+1)%mod;
}
int a[N],cnt[N],ans[N];
int C(int n,int m)
{
	if(m>n)return 0;
	return (ll)fac[n]*inv[n-m]%mod*inv[m]%mod;
}
int main()
{
	int n,m,k;
	init();
	scanf("%d%d%d",&n,&m,&k);
	for(int i = 1;i<= n;i++)
		scanf("%d",&a[i]),cnt[a[i]]++;
	for(int i = 1;i<= m;i++)
		for(int j = i+i;j<= m;j+=i)
			cnt[i]+=cnt[j];
	for(int i = 1;i<= m;i++)
		if(cnt[i]>=n-k)
			ans[i] = (ll)C(cnt[i],n-k)*quick_pow(m/i-1,cnt[i]-n+k)%mod*quick_pow(m/i,n-cnt[i])%mod;
	for(int i = m;i>= 1;i--)
		for(int j = i+i;j<= m;j+=i)
			(ans[i]+=mod-ans[j])%=mod;
	for(int i = 1;i< m;i++)printf("%d ",ans[i]);
	printf("%d\n",ans[m]);
	return 0;
}
