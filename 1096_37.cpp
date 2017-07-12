
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = 1000005;
int x[N],p[N],c[N],q[N],l,r;
LL sum[N],os[N],f[N];
double calc(int j,int k)
{
	return (double)(f[k]-f[j]+sum[k]-sum[j])/(double)(os[k]-os[j]);
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
		scanf("%d%d%d",&x[i],&p[i],&c[i]);
	for(int i = 1;i<=n;i++)
		os[i] = os[i-1]+p[i];
	for(int i = 1;i<=n;i++)
		sum[i] = sum[i-1]+(LL)x[i]*p[i];
	for(int i = 1;i<= n;i++)
	{
		while(l<r&&calc(q[l],q[l+1])<x[i])l++;
		if(l<=r)f[i] = f[q[l]]+sum[q[l]]-sum[i]+(os[i]-os[q[l]])*x[i]+c[i];
		while(l<r&&calc(q[r-1],q[r])>calc(q[r],i))r--;
		q[++r] = i;
	}
	printf("%lld\n",f[n]);
	return 0;
}
