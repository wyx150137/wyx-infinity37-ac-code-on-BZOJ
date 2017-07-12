
#include<stdio.h>
int pos[20005][6];
int dna2[100005];
int cnt[20005];
int a[1000005];
int f[100005];
int find(int x,int end)
{
	int l=1,r = end+1,mid;
	while(l<r)
	{
		mid = (l+r)/2;
		if(f[mid]>=x)
		{
			r = mid;
		}else
		{
			l = mid+1;
		}
	}
	return l;
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i = 1;i<= 5*n;i++)
	{
		int x;
		scanf("%d",&x);
		pos[x][5-cnt[x]] = i;
		cnt[x]++;
	}
	for(int i = 1;i<= 5*n;i++)
	{
		scanf("%d",&dna2[i]);
		for(int j = 1;j<=5;j++)
		{
			a[(i-1)*5+j] = pos[dna2[i]][j];
		}
	}
	int ans = 0;
	for(int i = 1;i<= 25*n;i++)
	{
		if(a[i]>f[ans])
		{
			ans++;
			f[ans] = a[i];
		}else
		{
			f[find(a[i],ans)] = a[i];
		}
	}
	printf("%d",ans);
	return 0;
}
