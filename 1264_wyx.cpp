
#include <stdio.h>
#include <algorithm>
using namespace std;
int ans2[2600001];
int dp[2600001];
int ans[2600001];
int l1=1;
struct DNA
{
	int name;
	int tmp;
	int a[6];
};
DNA f[100001];
int find(int x)
{
	int l=1;
	int r=l1+1;
	while(l<r)
	{
		int mid;
		mid=l+r;
		mid/=2;
		if(dp[mid]<x)
			l=mid+1;
		else
			r=mid;
	}
	return l;
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		f[i].name=i;
	}
	int q=1;
	int t=1;
	for(int i=1;i<=5*n;i++)
	{
		int k;
		scanf("%d",&k);
		f[k].tmp++;
		f[k].a[f[k].tmp]=q;
		q++;
		ans[t]=k;
		t+=5;
	}
	t=1;
	for(int i=1;i<=25*n;i+=5)
	{
		scanf("%d",&ans2[t]);
		t+=5;	
	}                         
	for(int i=1;i<=25*n;i+=5)
	{
		int w=i;
		ans2[i+1]=f[ans2[w]].a[4];
		ans2[i+2]=f[ans2[w]].a[3];
		ans2[i+3]=f[ans2[w]].a[2];
		ans2[i+4]=f[ans2[w]].a[1];
		ans2[i]=f[ans2[w]].a[5];
	}
	dp[1]=ans2[1];
	for(int i=2;i<=25*n;i++)
	{
		if(dp[l1]<ans2[i])
		{
			l1++;
			dp[l1]=ans2[i];
		}
		else
		{	
			int k=find(ans2[i]);
			dp[k]=ans2[i];
		}
	}
	printf("%d",l1);
	return 0;
}
