
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1<<9;
const int M = 31;
const int mod = 1000000007;
int f[M+1][M][N][10];
int main()
{
	int n,m,k;
	scanf("%d%d%d",&n,&m,&k);
	int end = (1<<(k+1))-1;
	f[2][0][0][0] = 1;
	for(int i = 2;i<= n;i++)
	{
		for(int j = 0;j<= m;j++)
		{
			for(int sta = 0;sta<=end;sta++)
			{
				for(int l = 0;l<k;l++)
				{
					(f[i][j][sta][l+1]+=f[i][j][sta][l])%=mod;
					if(j<m&&i-k+l>0)
						(f[i][j+1][sta^(1<<k)^(1<<l)][l]+=f[i][j][sta][l])%=mod;
				}
				if(!(sta&1))(f[i+1][j][sta>>1][0]+=f[i][j][sta][k])%=mod;
			}
		}
	}
	printf("%d\n",f[n+1][m][0][0]);
	return 0;
}
