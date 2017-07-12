
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 17;
const int S = 1<<16;
int w[N],t[N],cnt,v[S],f[S];
int gt[S],n,W;
void init()
{
	for(int i = 0;i<1<<n;i++)
	{
		int Gw = 0,Gt = 0;
		for(int j = 0;j<n;j++)
			if(i&(1<<j))
			{
				Gw+=w[j+1];
				Gt = max(Gt,t[j+1]);
			}
		if(Gw<=W)
		{
			gt[++cnt] = Gt;
			v[i] = cnt;
		}
	}
}
int main()
{
	memset(f,0x3f,sizeof(f));
	scanf("%d%d",&W,&n);
	for(int i = 1;i<= n;i++)
		scanf("%d%d",&t[i],&w[i]);
	init();
	f[0] = 0;
	for(int i = 0;i<1<<n;i++)
	{
		for(int k = i;k;k = (k-1)&i)
			if(v[k])
				f[i] = min(f[i],f[i-k]+gt[v[k]]);
	}
	printf("%d\n",f[(1<<n)-1]);
	return 0;
}
