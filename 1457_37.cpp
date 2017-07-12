
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int P = 105;
const int C = 10005;
const int N = 1005;
int sg[P][P];
int vis[C];
void Init()
{
	int cnt = 0;
	for(int i = 1;i<= 100;i++)
		for(int j = 1;j<=100;j++)if(i!=j)
		{
			++cnt;
			for(int k = 1;k<i;k++)if(j!=(i-k))vis[sg[i-k][j]]=cnt;
			for(int k = 1;k<j;k++)if(i!=(j-k))vis[sg[i][j-k]]=cnt;
			for(int k = min(i,j)-1;k>=1;k--)vis[sg[i-k][j-k]]=cnt;
			for(int k = 0;k<C;k++)
				if(vis[k]!=cnt)
					{sg[i][j]=k;break;}
		}
}
int main()
{
	Init();
	int cas;
	scanf("%d",&cas);
	while(cas--)
	{
		bool flag = false;
		int n,x,y,ans = 0;
		scanf("%d",&n);
		for(int i = 1;i<= n;i++)
		{
			scanf("%d%d",&x,&y);
			if(!x || !y|| x==y)flag = true;
				ans^=sg[x][y];
		}
		if(flag)printf("^o^\n");
		else 
		{
			if(ans>0)printf("^o^\n");
			else printf("T_T\n");
		}
	}
	return 0;
}
