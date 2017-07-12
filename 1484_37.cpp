
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = 5005;
const int INF = 0x7f7f7f7f;
LL a[N],b[N];
LL Abs(LL a){return a>0?a:-a;}
void work()
{
	memset(a,0,sizeof(a));
	memset(b,0,sizeof(b));
	int n,d;
	scanf("%d%d",&n,&d);
	for(int i = 1;i<= n;i++)
		scanf("%lld",&a[i]);
	if(Abs(a[n]-a[1])>(LL)(n-1)*d){printf("impossible\n");return ;}
	b[1]=a[1];
	for(int i = 2;i<= n;i++)
		b[i] = b[i-1]-d;
	LL s,x,delta,minx,tmp;
	while(a[n]!=b[n])
	{
		s = 0,minx = INF;
		delta = INF,tmp = -INF;
		for(int i=n;i>1;i--)
		{
			if(a[i]>b[i])s++,minx = min(minx,a[i]-b[i]);
			else s--;
			if(tmp<s&&b[i-1]+d>b[i])
				tmp = s,x = i,delta = minx;
		}
		delta = min(delta,b[x-1]+d-b[x]);
		for(int i = x;i<= n;i++)b[i]+=delta;
	}
	LL ans = 0;
	for(int i = 1;i<= n;i++)
		ans+=Abs(b[i]-a[i]);
	printf("%lld\n",ans);
}
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)work();
	return 0;
}
