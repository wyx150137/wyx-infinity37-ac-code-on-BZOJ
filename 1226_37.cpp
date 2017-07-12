
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1005;
const int S = 1<<8;
const int INF = 0x3f3f3f3f;
#define f(i,j,k) (f[i][j][k+8])
int t[N],b[N];
int f[N][S][20];
int v(int pos1,int pos2)
{
	if(pos1==0)return 0;
	return (t[pos1]^t[pos2]);
}
void work()
{
int n;
	scanf("%d",&n);
	for(int i = 1;i<=n;i++)
		scanf("%d%d",&t[i],&b[i]);
	for(int i = 1;i<= n+1;i++)
		for(int j = 0;j<1<<8;j++)
			for(int k = -8;k<= 7;k++)
				f(i,j,k) = INF;
	f(1,0,-1) = 0;
	for(int i = 1;i<= n;i++)
		for(int s = 0;s<1<<8;s++)
			for(int k = -8;k<=7;k++)
			{
				if(!(f(i,s,k)<INF))continue;
				if(s&1)f(i+1,s>>1,k-1) = min(f(i,s,k),f(i+1,s>>1,k-1));
				else
				{
					int r = INF;
					for(int l = 0;l<= 7;l++)
						if(!(s&(1<<l)))
						{
							if(i+l>r)break;
							r = min(r,i+b[i+l]+l);
							f(i,s|(1<<l),l)=min(f(i,s|(1<<l),l),f(i,s,k)+v(i+k,i+l));
						}
				}
			}
	int ans = 0x3f3f3f3f;
	for(int i = -8;i<=-1;i++)
		ans = min(ans,f(n+1,0,i));
	printf("%d\n",ans);
	return ;
}
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
		work();
	return 0;
}
