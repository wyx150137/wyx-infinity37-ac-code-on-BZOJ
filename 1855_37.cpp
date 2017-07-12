
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int T = 2005;
const int P = 2005;
int asi[T],bsi[T],api[T],bpi[T];
int f[T][P];
int line[P],L,R;
int main()
{
	memset(f,128,sizeof(f));
	int t,maxp,w;
	scanf("%d%d%d",&t,&maxp,&w);
	for(int i = 1;i<= t;i++)
		scanf("%d%d%d%d",&api[i],&bpi[i],&asi[i],&bsi[i]);
	for(int i = 1;i<= t;i++)
	{
		
		for(int j = 0;j <= asi[i];j++)f[i][j] = -api[i]*j;
		for(int j = 0;j <= maxp;j++)
			f[i][j] = max(f[i][j],f[i-1][j]);
		int t = i-w-1;
		if(t>=0)
		{
			L = 1,R = 0;
			for(int j = 0;j<=maxp;j++)
			{
				while(L<=R&&j-line[L]>asi[i])L++;
				int tmp = f[t][j]+j*api[i];
				while(L<=R&&tmp>=f[t][line[R]]+line[R]*api[i])
					R--;
				line[++R]= j;
				if(L<=R)f[i][j] = max(f[i][j],f[t][line[L]]+line[L]*api[i]-j*api[i]);
			}
			L = 1,R = 0;
			for(int j = maxp;j>= 0;j--)
			{
				while(L<=R&&line[L]-j>bsi[i])L++;
				int tmp = f[t][j]+j*bpi[i];
				while(L<=R&&tmp>=f[t][line[R]]+line[R]*bpi[i])
					R--;
				line[++R]= j;
				if(L<=R)f[i][j] = max(f[i][j],f[t][line[L]]+line[L]*bpi[i]-j*bpi[i]);
			}
		}
	}
	int ans = -1e9;
	for(int i = 0;i<= maxp;i++)
		ans = max(ans,f[t][i]);
	printf("%d",ans);
	return 0;
}
