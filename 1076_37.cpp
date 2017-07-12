
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int P = 1<<15;
const int N = 105;
double f[N][P];
int pre[N],val[N];
int main()
{
	int k,n,t,x;
	scanf("%d%d",&k,&n);
	for(int i = 1;i<= n;i++)
	{
		scanf("%d%d",&val[i],&t);
		while(t)
		{
			pre[i]|=1<<(t-1);
			scanf("%d",&t);
		}
	}
	double p = 1.0/(double)n;
	for(int i = k;i>= 1;i--)
		for(int j = 0;j<1<<n;j++)
		{
			//double ans = 0;
			for(int k = 1;k<= n;k++)
				if((j&pre[k])==pre[k])
					f[i][j]+=max(f[i+1][j],f[i+1][j|(1<<(k-1))]+val[k]);
				else f[i][j]+=f[i+1][j];
			f[i][j]*=p;
		}
	printf("%.6f\n",f[1][0]);
	return 0;
}
