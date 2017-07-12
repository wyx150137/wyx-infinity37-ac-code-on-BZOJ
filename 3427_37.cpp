
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1000005;
const int INF = 707185547;
int f[N][3];
int a[N];
int main()
{
	int n;
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
		scanf("%d",&a[i]);
	f[1][0] = f[1][1] = f[1][2] = INF;
	if(a[1]==-1)f[1][0] = 0;
	else if(a[1]==0)f[1][1] = 0;
	else f[1][2] = 0;
	for(int i = 2;i<= n;i++)
	{
		f[i][0] = f[i-1][0]+a[i]+1;
		if(a[i]==-1)
		{
			if(a[i-1]==1)f[i][1] = min(f[i-1][1],f[i-1][0])+1;
			else f[i][1] = INF;
		}else if(a[i]==0)f[i][1] = min(f[i-1][1],f[i-1][0]);
		else
		{
			if(a[i-1]==-1)f[i][1] = min(f[i-1][1],f[i-1][0])+1;
			else f[i][1] = f[i-1][0]+1;
		}
		if(a[i]==-1)
		{
			if(a[i-1]==1)f[i][2] = min(f[i-1][0],min(f[i-1][1],f[i-1][2]))+2;
			else f[i][2] = f[i-1][2]+2;
		}else if(a[i]==0)
		{
			if(a[i-1]==1)f[i][2] = min(f[i-1][0],min(f[i-1][1],f[i-1][2]))+1;
			else f[i][2] = f[i-1][2]+1;
		}else f[i][2] = min(f[i-1][0],min(f[i-1][1],f[i-1][2]));
	}
	int ans = min(f[n][0],min(f[n][1],f[n][2]));
	if(ans>=INF)printf("BRAK\n");
	else printf("%d\n",ans);
	return 0;
}
