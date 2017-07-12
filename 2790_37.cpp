
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e5+5;
const int M = 1e6+5;
const int INF = 0x3f3f3f3f;
int f[M],a[N],pre[M],sec[M];
int prime[N],cnt,v[M];
void init(int x)
{
	for(int i = 2;i<= x;i++)
	{
		if(!v[i])
		{
			prime[++cnt] = i;
			f[i] = 1;
		}
		for(int j = 1;j<= cnt&&prime[j]*i<= x;j++)
		{
			v[prime[j]*i]= true;
			f[i*prime[j]] = f[i]+1;
			if(i%prime[j]==0)break;
		}
	}
}
int main()
{
	//freopen("odl.in","r",stdin);
	//freopen("odl.out","w",stdout);
	f[0] = INF;
	int n;
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
		scanf("%d",&a[i]);
	init(1000000);
	for(int i = 1;i<= n;i++)
	{
		for(int j = 1;j*j<= a[i];j++)
		{
			if(a[i]%j==0)
			{
				if(f[a[i]]<f[a[pre[j]]])sec[j] = pre[j],pre[j] = i;
				else if(f[a[i]]<f[a[sec[j]]])sec[j] = i;
				if(f[a[i]]<f[a[pre[a[i]/j]]])sec[a[i]/j] = pre[a[i]/j],pre[a[i]/j] = i;
				else if(f[a[i]]<f[a[sec[a[i]/j]]]&&pre[a[i]/j]!=i)sec[a[i]/j] = i;
			}
		}
	}
	
	for(int i = 1;i<= n;i++)
	{
		int ans1 = 0x3f3f3f3f,ans2 = 0;
		for(int j = 1;j*j<= a[i];j++)
		{
			if(a[i]%j==0)
			{
				if(pre[j]&&sec[j]&&f[a[i]]-2*f[j]+f[a[pre[j]==i?sec[j]:pre[j]]]<ans1)
				{
					ans1 = f[a[i]]-2*f[j]+f[a[pre[j]==i?sec[j]:pre[j]]];
					ans2 = pre[j]==i?sec[j]:pre[j];
				}else if(f[a[i]]-2*f[j]+f[a[pre[j]==i?sec[j]:pre[j]]]==ans1)
					ans2 = min(ans2,pre[j]==i?sec[j]:pre[j]);
				if(pre[a[i]/j]&&sec[a[i]/j]&&f[a[i]]-2*f[a[i]/j]+f[a[pre[a[i]/j]==i?sec[a[i]/j]:pre[a[i]/j]]]<ans1)
				{
					ans1 = f[a[i]]-2*f[a[i]/j]+f[a[pre[a[i]/j]==i?sec[a[i]/j]:pre[a[i]/j]]];
					ans2 = pre[a[i]/j]==i?sec[a[i]/j]:pre[a[i]/j];
				}else if(f[a[i]]-2*f[a[i]/j]+f[a[pre[a[i]/j]==i?sec[a[i]/j]:pre[a[i]/j]]]==ans1)
					ans2 = min(ans2,pre[a[i]/j]==i?sec[a[i]/j]:pre[a[i]/j]);
			}
		}
		printf("%d\n",ans2);
	}
	return 0;
}
