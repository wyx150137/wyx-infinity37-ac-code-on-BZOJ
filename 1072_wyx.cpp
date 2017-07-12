
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int Maxn = 1<<11;
const int N = 1000+5;
typedef long long LL;
using namespace std;

LL F[Maxn][N];
int a[20],cnt;

int fac[N];

int main()
{
	fac[0] = 1;
	for(int i=1;i<=10;++i) fac[i] = fac[i-1] * i;
	int T ; 
	cin >> T;
	while(T--)
	{
		memset(F,0,sizeof F);
		memset(a,0,sizeof a);
		cnt = 0;
		char str[12];int d;
		scanf("%s%d",str,&d);
		int len = strlen(str); cnt = len;
		for(int i=0;i<len;++i) a[i+1] = str[i] - '0';
		F[0][0] = 1; 
		int Max = (1<<cnt) - 1;
		for(int i=0;i<=Max;++i)
			for(int k=0;k<d;++k)
				for(int j=1;j<=cnt;++j)
				{
					if((1<<(j-1))&i) continue;
					int tt = ((k<<1) + (k<<3) + a[j]) %d;
					F[(1<<(j-1))|i][tt] += F[i][k];
				}
		int Times[11] = {};
		for(int i=1;i<=cnt;++i) Times[a[i]] ++;
		for(int i=0;i<=9;++i) F[Max][0] /= fac[Times[i]];
		cout << F[Max][0] << endl;
	}
}
