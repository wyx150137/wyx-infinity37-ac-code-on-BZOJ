
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int N = 1e4+10;
typedef long long ll;
ll f[N][35];
int fac[N],n,m,k;
bool dfs(int now,int x,int pro)
{
	if(!x)return pro==n;
	x--;
	for(;now+x<=m;now++)
	{
		if(f[now][x]<0)return false;
		if((ll)pro*f[now][x]>n)return false;
		if(dfs(now+1,x,pro*fac[now]))return true;
	}
	return false;
}
int main()
{
	int test;
	scanf("%d",&test);
	while(test--)
	{
		m=0;
		scanf("%d%d",&n,&k);
		for(int i = 1;i*i<=n;i++)
			if(n%i==0)
			{
				fac[++m] = i;
				if(i*i!=n)fac[++m] = n/i;
			}
		sort(fac+1,fac+m+1);
		ll pro = 1;
		for(int i = 1;i<= m;i++)
		{
			pro = 1;
			for(int j = 0;j<k&&i+j<=m;f[i][j++]=pro)
			if(pro>0)
			{
				pro = pro*fac[i+j];
				if(pro>n)pro = -1;
			}
		}
		if(dfs(1,k,1))printf("TAK\n");
		else printf("NIE\n");
	}
	return 0;
}
