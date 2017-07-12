
#include <stdio.h>
int main()
{
	double x;
	scanf("%lf",&x);
	printf("%.9lf",x*(x+1)/2/(2*x-1));
}
