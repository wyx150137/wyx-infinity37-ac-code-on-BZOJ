
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 1e5;
int n,a[55];
int f[N+5],prime[N],cnt;
bool vis[N+5];
void quick_prime()
{
	for(int i = 2;i<= N;i++)
	{
		if(!vis[i])
			prime[++cnt] = i;
		for(int j = 1;j<= cnt&&i*prime[j]<=N;j++)
		{
			vis[i*prime[j]]=true;
			if(i%prime[j]==0)break;
		}
	}
}
int main()
{
	quick_prime();
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)scanf("%d",&a[i]);
	memset(f,0x3f,sizeof(f));
	f[1] = 0;
	int ans = 0x3f3f3f3f;
	for(int i = 1;i<= N;i++)
	{
		for(int j = 1;j<= cnt&&i*prime[j]<=N;j++)
		{
			int val = i*prime[j];
			ll tmp = 0;
			for(int k = 1;k<= n;k++)
				tmp+=a[k]%val/i;
			if(tmp<=0x3f3f3f3f)
				f[val] = min(f[val],f[i]+(int)tmp);
		}
		ll tmp = f[i];
		for(int k = 1;k<= n;k++)
			tmp+=a[k]/i;
		if(tmp<=0x3f3f3f3f)
			ans = min(ans,(int)tmp);
	}
	printf("%d\n",ans);
	return 0;
}
