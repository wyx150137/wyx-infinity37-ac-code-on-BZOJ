
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = 52;
const int M = 4002;
const int INF = 500000;
int L[M],R[M],c[M],stack[M],pos[N][N][M],val[N][N][M];
LL f[N][N][M],sum[N][N][M];
int pid[N];
void printans(int l,int r,int t)
{
	if(l>r)return ;
	int tmp = val[l][r][t];
	printans(l,pos[l][r][t]-1,tmp);
	printf("%d ",pid[tmp]);
	printans(pos[l][r][t]+1,r,tmp);
}
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d%d",&L[i],&R[i],&c[i]);
		pid[i] = c[i];
	}
	sort(pid+1,pid+m+1);
	for(int lth = 1;lth<=n;lth++)
	{
		for(int l = 1;l+lth-1<= n;l++)
		{
			int r = l+lth-1;
			for(int k = l;k<= r;k++)
			{
				int top = 0;
				for(int t = 1;t<= m;t++)
					if(L[t]>=l&&R[t]<=r&&k>=L[t]&&k<=R[t])
						stack[++top] = c[t];
				sort(stack+1,stack+top+1);
				int head = 1;
				for(int t = 1;t<= m;t++)
				{
					while(head<=top&&stack[head]<pid[t])head++;
					LL tmp = sum[l][k-1][t]+sum[k+1][r][t]+(LL)(top-head+1)*pid[t];
					if(tmp>=f[l][r][t])
					{
						f[l][r][t] = tmp;
						pos[l][r][t] = k;
					}
				}
			}
			for(int k = m;k>=1;k--)
			{
				val[l][r][k] = k;
				if(f[l][r][k]<sum[l][r][k+1])
				{
					val[l][r][k] = val[l][r][k+1];
					pos[l][r][k] = pos[l][r][k+1];
				}
				sum[l][r][k] = max(sum[l][r][k+1],f[l][r][k]);
			}
		}
	}
	printf("%lld\n",sum[1][n][1]);
	printans(1,n,1);
	return 0;
}
