
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 300005;
char m[N];
double l[N],f[N];
int main()
{
	int n;
	scanf("%d",&n);
	scanf("%s",m+1);
	for(int i = 1;i<= n;i++)
	{
		if(m[i]=='o')
		{
			l[i] = l[i-1]+1;
			f[i] = f[i-1]+2*l[i-1]+1;
		}else if(m[i]=='x')
		{
			l[i] = 0;
			f[i] = f[i-1];
		}else
		{
			l[i] = 0.5*(l[i-1]+1);
			f[i] = 0.5*(f[i-1])+0.5*(f[i-1]+2*l[i-1]+1);
		}
	}
	printf("%.4f\n",f[n]);
	return 0;
}
