
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
int n,m;
double f[55][55];
int a[55];
int main()
{
	scanf("%d%d",&n,&m);
	for(int i= 1;i<= m;i++)scanf("%d",&a[i]);
	f[1][1] = 1;
	for(int i = 2;i<= n;i++)
	{
		for(int j = 1;j<= i;j++)
		{
			for(int k = 1;k<= m;k++)
			{
				int tmp = a[k]%i;
				if(tmp==0)tmp = i;
				if(tmp==j)continue;
				if(tmp>j)tmp = i-tmp+j;
				else tmp = j-tmp;
				f[i][j] += f[i-1][tmp]/(double)m;
			}
		}
	}
	for(int i = 1;i< n;i++)
		printf("%.2lf%c ",f[n][i]*100.0,'%');
	printf("%.2lf%c",f[n][n]*100.0,'%');
	return 0;
}
