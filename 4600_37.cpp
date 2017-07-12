
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 505;
bool vis[N];
int sg[25][25];
void init(int n,int maxQ)
{
	int tmp,x = 0,y = 0;
	tmp = n;while(tmp>=2)x++,tmp/=2;
	tmp = n;while(tmp>=3)y++,tmp/=3;
	for(int i = 0;i<= x;i++)
		for(int j = 0;j<= y;j++)
		{
			memset(vis,0,sizeof(vis));
			for(int p = 1;p<= i;p++)
				for(int q = 1;q*p<=i&&q<=maxQ;q++)
				{
					tmp = -1;
					for(int k = 1;k<= q;k++)
						if(tmp==-1)tmp = sg[i-k*p][j];
						else tmp = tmp^sg[i-p*k][j];
					if(tmp!=-1)vis[tmp] = true;
				}
			for(int p = 1;p<= j;p++)
				for(int q = 1;q*p<=j&&q<=maxQ;q++)
				{
					tmp = -1;
					for(int k = 1;k<= q;k++)
						if(tmp==-1)tmp = sg[i][j-p*k];
						else tmp = tmp^sg[i][j-p*k];
					if(tmp!=-1)vis[tmp] = true;
				}
			for(int k=0;;k++)
				if(!vis[k])
					{sg[i][j] =k;break;}
		}
}
int main()
{
	int cas;
	scanf("%d",&cas);
	while(cas--)
	{
		int n,maxQ;
		scanf("%d%d",&n,&maxQ);
		init(n,maxQ);
		int ans = 0;
		int s;
		for(int i = 1;i<= n;i++)
		{
			scanf("%d",&s);
			if(!s)
			{
				int x,y,tmp;
				x = y = 0;
				tmp = i;while(tmp%2==0)x++,tmp/=2;
				tmp = i;while(tmp%3==0)y++,tmp/=3;
				ans = ans^sg[x][y];
			}
		}
		if(!ans)printf("lose\n");
		else printf("win\n");
	}
	return 0;
}
