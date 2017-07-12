
#include <bitset>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 2000+5;
using namespace std;

bool up[N][N],ri[N][N];
bool vis[N][N];
char str[N];
int x = 1000+5;
int y = 1000+5;

int main()
{
	int n;  cin >> n;
	scanf("%s",str+1);
 	int ans = 0;
	for(int i=1;i<=n;++i)
	{
		vis[x][y] = 1;

		if(str[i] =='E')
		{
			++ x;
			if(!ri[x-1][y] && vis[x][y]) ans ++;
			ri[x-1][y] = 1;
		}

		if(str[i] == 'W')
		{
			-- x;
			if(!ri[x][y] && vis[x][y]) ans ++;
			ri[x][y] = 1;
		}

		if(str[i] == 'N')
		{
			++ y;
			if(!up[x][y-1] && vis[x][y]) ans ++;
			up[x][y-1] = 1;
		}

		if(str[i] == 'S')
		{
			-- y;
			if(!up[x][y] && vis[x][y]) ans ++;
			up[x][y] = 1;
		}	
	}
	cout << ans << endl;
}
