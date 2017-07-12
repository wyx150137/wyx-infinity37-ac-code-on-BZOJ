
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#define N 100+5
using namespace std;
int map[N][N];
int main()
{
	//freopen("contest.in","r",stdin);
	//freopen("contest.out","w",stdout);
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;++i)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		map[x][y]=1;
	}
	for(int k=1;k<=n;++k)
		for(int i=1;i<=n;++i)
			for(int j=1;j<=n;++j)
				map[i][j]=(map[i][k] && map[k][j])||map[i][j];
	int ans = 0;
	for(int i=1;i<=n;++i)
	{
		int cnt = 0;
		for(int j=1;j<=n;++j)
			if(map[i][j]||map[j][i])
				++cnt;
		if(cnt == n-1)
			ans++;
	}
	cout<<ans<<endl;
}
