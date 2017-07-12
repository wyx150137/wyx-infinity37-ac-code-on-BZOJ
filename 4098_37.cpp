
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 505;
const int mod = 1e9+7;
char s[N][N];
int f[2][N][N];
int main()
{
	int n;
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
		scanf("%s",s[i]+1);
	f[0][1][n] = 1;
	for(int i = 1;i<=n;i++)
	{
		int now = i&1,pre = (i-1)&1;
		memset(f[now],0,sizeof(f[now]));
		for(int x1 = 1;x1<= i;x1++)
		{
			int y1 = i-x1+1;
			for(int x2 = n;x2>=n-i;x2--)
			{
				int y2 = n-(i-(n-x2))+1;
				if(s[x1][y1]==s[x2][y2])
					f[now][x1][x2] = ((f[pre][x1][x2]+f[pre][x1-1][x2])%mod+(f[pre][x1][x2+1]+f[pre][x1-1][x2+1])%mod)%mod;
			}
		}
	}
	int ans = 0;
	for(int i = 1;i<= n;i++)
		(ans+=f[n&1][i][i])%=mod;
	printf("%d\n",ans);
	return 0;
}
