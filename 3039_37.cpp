
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1005;
bool map[N][N];
int l[N][N],r[N][N],h[N][N];
char s[3];
int ans = 0,n,m;
void work()
{
	for(int i = 1;i<= n;i++)
	{
		int t = 1;
		for(int j = 1;j<= m;j++)
			if(map[i][j])l[i][j] = t;
			else l[i][j] = 1,t = j+1;
		t = m;
		for(int j = m;j>=1;j--)
			if(map[i][j])r[i][j] = t;
			else r[i][j] = m,t = j-1;
	}
	for(int j = 1;j<= m;j++)l[0][j] = 1,r[0][j] = m;
	for(int i = 1;i<= n;i++)
		for(int j = 1;j<= m;j++)
			if(map[i][j])
			{
				h[i][j] = h[i-1][j]+1;
				l[i][j] = max(l[i-1][j],l[i][j]);
				r[i][j] = min(r[i-1][j],r[i][j]);
				ans = max(ans,(r[i][j]-l[i][j]+1)*h[i][j]);
			}
	printf("%d\n",ans*3);
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= n;i++)
	{
		for(int j = 1;j<=m;j++)
		{
			scanf("%s",s);
			map[i][j] = s[0]=='F';
		}
	}
	work();
	return 0;
}
