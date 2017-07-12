
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1<<20;
const double eps = 1e-8;
double a[N+5];
int f[N+5];
int main()
{
	int n;
	scanf("%d",&n);
	f[0] = ((n+1)&1)?-1:1;
	for(int i = 0;i<(1<<n);i++)
	{
		scanf("%lf",&a[i]);
		if(i>0)f[i] = -f[i-(i&(-i))];
	}
	for(int k = 1;k<(1<<n);k<<=1)
		for(int i = 0;i<(1<<n);i++)
		{
			if(i&k)continue;
			a[i+k]+=a[i];
		}
	bool flag = true;
	for(int i = 0;flag&&i<(1<<n)-1;i++)
		if(a[i]+eps>1)
			flag = false;
	if(!flag)printf("INF\n");
	else
	{
		double ans = 0;
		for(int i = 0;i<(1<<n)-1;i++)
			ans+=f[i]/(1-a[i]);
		printf("%.7lf\n",ans);
	}
	return 0;
}
