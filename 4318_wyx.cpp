
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
	double tmp1 = 0 ,tmp2 = 0,tmp3 = 0,p;
	int n;cin >> n;
	for(int i=1;i<=n;++i)
	{
		scanf("%lf",&p);
		tmp3 = p*(tmp3+3.0*tmp2+3.0*tmp1+1)+(1.0-p)*(tmp3);
		tmp2 = p*(tmp2+2.0*tmp1+1);
		tmp1 = p*(tmp1+1);
	}
	printf("%.1lf",tmp3);
}
