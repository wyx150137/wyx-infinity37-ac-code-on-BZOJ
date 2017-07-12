
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = 1e6+5;
int a[N],line[N],l,r;
LL f[N];
double calc(int j,int k)
{
	return ((double)(f[j]-f[k])*2+(double)j*(j+1)-(double)k*(k+1))/(double)(j-k);
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
		scanf("%d",&a[i]);
	for(int i = 1;i<= n;i++)
	{
		while(l<r&&calc(line[l+1],line[l])<2*i)l++;
		if(l<=r)f[i] = f[line[l]]+(LL)(i-line[l]-1)*(i-line[l])/2+a[i];
		while(l<r&&calc(line[r],line[r-1])>calc(i,line[r]))r--;
		line[++r] = i;
	}
	printf("%lld\n",f[n]);
	return 0;
}
