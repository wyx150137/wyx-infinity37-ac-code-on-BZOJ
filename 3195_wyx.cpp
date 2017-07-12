
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int mod = 1000000007;
int F[32][31][1<<11][10];
int main()
{
	int n,m,k;
	cin >> n >> m >> k;
	int Max = (1<<(k+1)) - 1;
	F[2][0][0][0] = 1;
	for(int i=2;i<=n;++i)
		for(int j=0;j<=m;++j)
			for(int sta=0;sta<=Max;++sta)
			{
				for(int l=0;l<k;++l)
					if(F[i][j][sta][l])
					{
						(F[i][j][sta][l+1] += F[i][j][sta][l])%=mod;
						if( i+l-k>0 && j+1 <= m)
							(F[i][j+1][sta^(1<<l)^(1<<k)][l] += F[i][j][sta][l])%=mod;
					}
				if(!(sta&1) && F[i][j][sta][k])
					F[i+1][j][sta>>1][0] = F[i][j][sta][k];
			}
	cout << F[n+1][m][0][0] << endl;
}
