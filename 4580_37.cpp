
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
int num[250];
int f[250][250];
int uni(int l,int r)
{
	if(f[l][r]!=0)return f[l][r];
	for(int i = l;i<r;i++)
		if(uni(l,i)==uni(i+1,r))
			f[l][r] = max(f[l][i]+1,f[l][r]);
	if(f[l][r]==0)f[l][r] = -1;
	return f[l][r];
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i = 1;i<=n;i++)
	{
		scanf("%d",&num[i]);
		f[i][i] = num[i];
	}
	int ans = 0;
	for(int i = 1;i<= n;i++)
		for(int j = i;j<= n;j++)
			ans = max(ans,uni(i,j));
	printf("%d\n",ans);
	return 0;
}
