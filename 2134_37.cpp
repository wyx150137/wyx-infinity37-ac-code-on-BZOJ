
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 10000005;
int a[N];
int main()
{
	int n,A,B,C;
	scanf("%d%d%d%d%d",&n,&A,&B,&C,a+1); 
	for(int i=2;i<=n;i++) 
		a[i] = ((long long)a[i-1]*A+B)%100000001; 
	for(int i=1;i<=n;i++) 
		a[i] = a[i]%C+1; 
	double ans = 1.0/(double)max(a[1],a[n]);
	for(int i = 2;i<= n;i++)
		ans+=1.0/(double)max(a[i],a[i-1]);
	printf("%.3f\n",ans);
	return 0;
}
