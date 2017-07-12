
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 105;
ll f[35][1005];
int main()
{
	int n,w,x,v;
	while(scanf("%d%d",&n,&w)!=EOF)
	{
		if(n==-1&&w==-1)break;
		memset(f,0,sizeof(f));
		for(int i = 1;i<= n;i++)
		{
			scanf("%d%d",&x,&v);
			int tmp = 0;
			while(!(x&1))x>>=1,tmp++;
			for(int j = 1000;j>= x;j--)
				f[tmp][j] = max(f[tmp][j],f[tmp][j-x]+v);
		}
		for(int i = 0;i<= 30;i++)
			for(int j = 1;j<= 1000;j++)
				f[i][j]=max(f[i][j],f[i][j-1]);
		ll ans = 0;
		for(int j = 1;j<= min(1000,w);j++)ans = max(ans,f[0][j]);
		for(int i = 1;i<= 30&&(1<<i)<=w;i++)
			for(int j = min(1000,w>>i);j>= 0;j--)
			{
				for(int k = 0;k<= j;k++)
					f[i][j] = max(f[i][j],f[i][j-k]+f[i-1][min(k+k+((w>>i-1)&1),1000)]);
				ans = max(f[i][j],ans);
			}
		printf("%d\n",ans);

	}
	return 0;
}
