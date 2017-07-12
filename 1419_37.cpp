
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 5005;
const double eps = 5e-7;
double f[2][N];
int main()
{
	int a,b;
	scanf("%d%d",&a,&b);
	for(int i = 1;i<=a;i++)
	{
		int I = i&1,I_ = (i-1)&1;
		f[I][0] = i;
		for(int j = 1;j<=b;j++)
		f[I][j] = 
			max(0.0,(double)i/(double)(i+j)*(f[I_][j]+1)+(double)j/(double)(i+j)*(f[I][j-1]-1));
	}
	printf("%.6f",f[a&1][b]-eps);
	return 0;
}
