
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
typedef double DD;
const int N = 5000+10;
int n , m;
DD f[2][N];
int main()
{
	cin >> n >> m;
	for(int i=0,now=0;i<=n;++i,now^=1)
	{
		f[now][0] = i;
		int op = now ^ 1;
		for(int j=1;j<=m;++j)
			f[now][j] = max(0.0,(DD)(i)/(i+j)*(f[op][j]+1)+(DD)(j)/(i+j)*(f[now][j-1]-1));
	}
	printf("%.6lf\n",f[n&1][m]-5e-7);
		
}
