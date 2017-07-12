
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 500+5;
typedef long long LL;
using namespace std;

int F[2][N][N];
char str[N][N];
const int mod = 1e9+7;
int n;
LL ans;

int main()
{
	int n;
	cin >> n;
	for(int i=1;i<=n;++i) scanf("%s",str[i]+1);
	F[0][1][n] = 1;
	for(int i=1;i<=n;++i)
	{
		int o = i & 1;
		int op = (i+1) & 1;
		memset(F[o],0,sizeof F[o]);
		for(int x1=1;x1<=n;++x1)
			if(i+1-x1 >= 1 && i+1-x1 <= n)
			{
				int y1 = i+1-x1;
				for(int x2=1;x2<=n;++x2)
				{
					int y2 = (n+1)*2 -x1 - y1 - x2;
					if(y2 >= 1 && y2 <= n)
						if(str[x1][y1] == str[x2][y2])
							F[o][x1][x2] = ((LL)F[op][x1-1][x2+1]+F[op][x1-1][x2]+F[op][x1][x2]+F[op][x1][x2+1]) % mod;
				}
			}
	}
	int tt = n & 1;
	for(int i=1;i<=n;++i) ans = (ans + F[tt][i][i])%mod;
	cout << ans << endl;
}
