
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e5+5;
const int mod = 1e9+7;
int fa[N*20],id[N][20],idx[N*20][2];
int getfa(int x)
{
	if(fa[x]==x||!fa[x])return fa[x]=x;
	else return fa[x]=getfa(fa[x]);
}
void merge(int x,int y)
{
	x = getfa(x),y = getfa(y);
	if(x==y)return ;
	fa[y] = x;
}
int pow2[20];
int main()
{
	pow2[0] = 1;
	for(int i = 1;i<= 18;i++)pow2[i]=pow2[i-1]*2;
	int n,cnt = 0,m;
	scanf("%d",&n);
	if(n==1){printf("10\n");return 0;}
	for(int i = 1;i<= n;i++)
		for(int j = 0;j<=18;j++)
			id[i][j]=++cnt,idx[cnt][0]=i,idx[cnt][1]=j;
	scanf("%d",&m);
	int l1,r1,l2,r2;
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d%d%d",&l1,&r1,&l2,&r2);
		for(int j = 18;j>= 0;j--)
		{
			if(l1+pow2[j]-1<=r1)
			{
				merge(id[l1][j],id[l2][j]);
				l1+=pow2[j],l2+=pow2[j];
			}
		}
	}
	for(int j = 18;j>= 1;j--)
	{
		for(int i = 1;i<= n;i++)
		{
			int k = getfa(id[i][j]);
			int s = idx[k][0];int t = idx[k][1];
			merge(id[s][t-1],id[i][j-1]);
			merge(id[s+pow2[t-1]][t-1],id[i+pow2[j-1]][j-1]);
		}
	}
	int tot = 0;
	for(int i = 1;i<= n;i++)
		if(getfa(id[i][0])==id[i][0])tot++;
	long long ans = 9;
	for(int i = 1;i< tot;i++)ans = ans*10%mod;
	printf("%lld\n",ans);
	return 0;
}
