
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 500005;
int s[N],a[N<<1];
int no[N<<1],p[N<<1];
long long ans;
int maxp,id;
int main()
{
	int n;
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
		scanf("%1d",&s[i]);
	int len = 0;
	for(int i = 1;i<=n;i++)
	{
		a[++len]=s[i];
		no[len]=i;
		if(i!=n)a[++len]=-1;
	}
	maxp = 1,id = 1;
	for(int i = 1;i<= len;i++)
	{
		if(i<=maxp)p[i]=min(p[id*2-i],maxp-i);
		while(i+p[i]<=len&&i-p[i]>=1&&(a[i+p[i]]+a[i-p[i]]==1||a[i+p[i]]+a[i-p[i]]==-2))p[i]++;
		p[i]--;
		if(i+p[i]>maxp){maxp = i+p[i];id = i;}
		ans+=(no[i+p[i]]?no[i+p[i]]:no[i+p[i]-1])-(no[i]?no[i]:no[i+1])+1;
	}
	printf("%lld\n",ans);
	return 0;
}
