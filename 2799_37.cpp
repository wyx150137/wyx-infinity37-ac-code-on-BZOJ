
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e6+5;
int p[N],z[N],mn[N],fa[N],num[N],id[N],sum[N],cnt;
int getfa(int x)
{
	if(fa[x]==x)return fa[x] = x;
	else return fa[x] = getfa(fa[x]);
}
void dfs(int x)
{
	if(mn[x])return ;
	dfs(p[x]);
	mn[x] = getfa(mn[p[x]]-1);
	if(++num[mn[x]]==1)
		id[mn[x]] = x;
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)fa[i] = i;
	for(int i = 1;i<= n;i++)
	{
		scanf("%d%d",&p[i],&z[i]);
		if(p[i]==i)z[i] = n;
		if(z[i])
		{
			fa[z[i]] = z[i]-1;
			mn[i] = z[i];
		}
	}
	for(int i = 1;i<= n;i++)
		if(!mn[i])dfs(i);
	for(int i = 1;i<= n;i++)
		sum[i] = sum[i-1]+(fa[i]==i);
	for(int i = 1;i<= n;i++)
		if(num[i])
		{
			if(num[i]==1&&sum[i]==cnt+1)
				z[id[i]] = i,cnt++;
			else if(num[i]+cnt==sum[i])
				cnt = sum[i]; 
			else num[i+1]+=num[i];
		}
	for(int i = 1;i<= n;i++)
		printf("%d\n",z[i]);
	return 0;
}
