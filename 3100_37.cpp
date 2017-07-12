
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 1e6+2;
ll a[N];
int last[N];
int i,n,ans,mx,wz;
void calc()
{
	int j,l;
	ans = max(ans,1);
	mx = 1;
	l = last[a[i]-a[i-1]];
	last[a[i]-a[i-1]] = i;
	wz = l+1;
	for(j = i+1;j<= n+1;j++)
	{
		if(j>n||a[j]-a[j-1]==1)break;
		l = last[a[j]-a[j-1]];
		last[a[j]-a[j-1]] = j;
		wz = max(wz,l);
		mx = max(mx,int(a[j]-a[j-1]));
		if(wz<=j-mx+1)
			if(a[j]-a[j-mx]==(ll)mx*(mx+1)/2)
				ans = max(ans,mx);
	}
	i = j;
}
int main()
{
	scanf("%d",&n);
	for(i = 1;i<= n;i++)
		scanf("%lld",&a[i]);
	for(i = 1;i<= n;i++)a[i]+=a[i-1];
	for(i = 1;i<= n;i++)
	{
		if(a[i]-a[i-1]==1)break;
		last[a[i]-a[i-1]]=i;
	}
	while(i<=n)calc();
	for(i = n;i>= 1;i--)a[i]-=a[i-1];
	for(i = 1;i<= n/2;i++)swap(a[i],a[n-i+1]);
	for(i = 1;i<= n;i++)a[i]+=a[i-1];
	for(i = 1;i<= n;i++)last[i]=0;
	for(i = 1;i<= n;i++)
	{
		if(a[i]-a[i-1]==1)break;
		last[a[i]-a[i-1]]=i;
	}
	while(i<=n)calc();
	printf("%d\n",ans);	
	return 0;
}
