
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1005;
long long f[N][N][2];
int pos[N],n,s;
int find(int x)
{
	int l = 1,r = n+1;
	while(l<r)
	{
		int mid = (l+r)>>1;
		if(pos[mid]<x)l = mid+1;
		else r = mid;
	}
	return l;
}
int main()
{
	scanf("%d%d",&n,&s);
	for(int i = 1;i<= n;i++)
		scanf("%d",&pos[i]);
	pos[++n] = s;
	sort(pos+1,pos+n+1);
	s = find(s);
	memset(f,0x3f,sizeof(f));
	f[s][1][0] = f[s][1][1] = 0;
	for(int len = 2;len <= n;len++)
	{
		for(int l = 1;l+len-1<= n;l++)
		{
			int r = l+len-1;
			f[l][len][1] = min(f[l][len][1],min(f[l+1][len-1][1]+(n-len+1)*(pos[l+1]-pos[l]),f[l+1][len-1][0]+(n-len+1)*(pos[r]-pos[l])));
			f[l][len][0] = min(f[l][len][0],min(f[l][len-1][0]+(n-len+1)*(pos[r]-pos[r-1]),f[l][len-1][1]+(n-len+1)*(pos[r]-pos[l])));
		}
	}
	printf("%lld\n",min(f[1][n][0],f[1][n][1]));
	return 0;
}
