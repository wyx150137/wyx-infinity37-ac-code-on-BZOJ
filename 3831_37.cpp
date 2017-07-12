
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e6+5;
int line[N],L,R,a[N],f[N];
bool smaller(int i,int j)
{
	if(f[i]!=f[j])
		return f[i]<f[j];
	return a[i]>a[j];
}
int main()
{
	int n,k,t;
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
		scanf("%d",&a[i]);
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&k);
		memset(f,0x3f,sizeof(f));
		L = 0,R = 0;line[R] = 1;
		f[1] = 0;
		for(int i = 2;i<= n;i++)
		{
			while(L<=R&&line[L]<i-k)L++;
			f[i] = min(f[i],f[line[L]]+(a[line[L]]<=a[i]));
			while(L<=R&&smaller(i,line[R]))R--;
			line[++R] = i;
		}
		printf("%d\n",f[n]);
	}
	return 0;
}
