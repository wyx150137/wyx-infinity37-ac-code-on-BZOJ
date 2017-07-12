
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e6+5;
int a[N],b[N],col[N],nxt[N];
int ans[N],tot,j;
inline bool check(int x,int y)
{
	if(b[x]==-1)
	{
		if(y>=x||y==-1)return true;
	}
	return b[x]==y;
}
int main()
{
	int cas,C;
	scanf("%d%d",&cas,&C);
	while(cas--)
	{
		int n,m,x;
		scanf("%d%d",&n,&m);
		memset(col,0,sizeof(col));
		for(int i = 1;i<= n;i++)
		{
			scanf("%d",&x);
			a[i] = i-col[x];
			col[x] = i;
		}
		memset(col,0,sizeof(col));
		for(int i = 1;i<= m;i++)
		{
			scanf("%d",&x);
			if(!col[x])b[i]=-1;
			else b[i]=i-col[x];
			col[x] = i;
		}
		j = tot = 0;
		for(int i = 2;i<= m;i++)
		{
			while(j && !check(j+1,b[i]))j = nxt[j];
			if(check(j+1,b[i]))j++;nxt[i]=j;
		}
		j = 0;
		for(int i = 1;i<= n;i++)
		{
			while(j && !check(j+1,a[i]))j = nxt[j];
			if(check(j+1,a[i]))j++;
			if(j==m)
			{
				ans[++tot] = i-m+1;
				j = nxt[j];
			}
		}
		printf("%d\n",tot);
		for(int i = 1;i<= tot;i++)
			printf("%d ",ans[i]);
		puts("");
	}
	return 0;
}
