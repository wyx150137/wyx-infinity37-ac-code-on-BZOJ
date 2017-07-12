
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 100000+5;
double f[N],l1[N],l2[N];
double p[N];
int main()
{
	int n;
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
		scanf("%lf",&p[i]);
	for(int i = 1;i<= n;i++)
	{
		l1[i] = p[i]*(l1[i-1]+1);
		l2[i] = p[i]*(l2[i-1]+2*l1[i-1]+1);
		f[i] = p[i]*(f[i-1]+3.0*l2[i-1]+3.0*l1[i-1]+1)+(1-p[i])*f[i-1];
	}
	printf("%.1f",f[n]);
	return 0;
}
