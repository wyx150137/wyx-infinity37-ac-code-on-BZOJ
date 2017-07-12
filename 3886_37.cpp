
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
int c[25][1005];
int lth[25];
int f[1<<20];
int find(int no,int x)
{
	int l = 1,r = c[no][0]+1;
	while(l<r)
	{
		int mid= (l+r)>>1;
		if(c[no][mid]<x)l = mid+1;
		else r = mid;
	}
	return l;
}
int main()
{
	int n,l;
	scanf("%d%d",&n,&l);
	int end = 1<<n;
	memset(c,0x3f,sizeof(c));
	for(int i = 1;i<= n;i++)
	{
		scanf("%d%d",&lth[i],&c[i][0]);
		for(int j = 1;j<= c[i][0];j++)
			scanf("%d",&c[i][j]);
	}
	memset(f,-1,sizeof(f));
	f[0] = 0;
	int ans =50;
	for(int i = 0;i<end;i++)
	{
		if(f[i]==-1)continue;
		for(int j = 1;j<= n;j++)
		if(!(i&(1<<(j-1))))
		{
			int tmp = find(j,f[i]);
			if(c[j][tmp]>f[i])tmp--;
			if(tmp>0)f[i|(1<<(j-1))] = max(f[i|(1<<(j-1))],max(f[i],c[j][tmp]+lth[j]));
		}
		if(f[i]>=l)
		{
			int tmp = i,cnt = 0;
			while(tmp){tmp-=tmp&(-tmp);cnt++;}
			ans = min(ans,cnt);
		}
	}
	if(ans!=50)printf("%d\n",ans);
	else printf("-1\n");
	return 0;
}
