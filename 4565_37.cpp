
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int S = 1<<8;
const int N = 305;
ll f[N][N][S];
ll inf;
int val[S],c[S];
char s[N];
int main()
{
	int n,k;
	scanf("%d%d",&n,&k);
	scanf("%s",s+1);
	for(int i = 0;i<1<<k;i++)scanf("%d%d",&c[i],&val[i]);
	memset(f,0xef,sizeof(f));inf = f[0][0][0];
	for(int i = 1;i<= n;i++)f[i][i][s[i]-'0'] = 0;
	for(int lth = 2;lth<= n;lth++)
	{
		for(int i = 1;i+lth-1<=n;i++)
		{
			int j = i+lth-1;
			int len = j-i;ll now,t;
			while(len>=k)len-=k-1;
			for(int m = j;m>i;m-=k-1)
				for(int S = 0;S<(1<<len);S++)
					if(f[i][m-1][S]!=inf)
					{
						if(f[m][j][0]!=inf)f[i][j][S<<1] = max(f[i][j][S<<1],f[i][m-1][S]+f[m][j][0]);
						if(f[m][j][1]!=inf)f[i][j][S<<1|1] = max(f[i][j][S<<1|1],f[i][m-1][S]+f[m][j][1]);
					}
			if(len==k-1)
			{
				ll g[2];
				g[0] = g[1] = inf;
				for(int S = 0;S<1<<k;S++)
					if(f[i][j][S]!=inf)
						g[c[S]]=max(g[c[S]],f[i][j][S]+val[S]);
				memcpy(f[i][j],g,sizeof(g));
			}
		}
	}
	ll ans = 0;
	for(int i = 0;i<1<<k;i++)
		ans = max(ans,f[1][n][i]);
	printf("%lld\n",ans);
	return 0;
}
