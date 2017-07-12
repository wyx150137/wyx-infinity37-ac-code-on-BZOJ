
#include <stdio.h>
#include <map>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long LL;
typedef unsigned long long ull;
const int N = 1000005;
const LL seed = 131133;
map<ull,int>id;
LL cnt;
ull pw[N],val[N],sum[N];
int pre[N],next[N],a[N];
bool vis[N];
int stack[N],top,n,k,ans,tot;
int calc(int x,int y)
{
	int t = y-x;
	return abs(t-n+t);
}
int main()
{
	scanf("%d%d",&n,&k);
	pw[0] = 1;
	for(int i = 1;i<= n;i++)pw[i] = pw[i-1]*seed;
	for(int i = 1;i<= n;i++)
	{
		scanf("%d",&a[i]);
		if(pre[a[i]])
		{
			val[pre[a[i]]]+=pw[++tot];
			val[i]-=pw[tot];
		}
		pre[a[i]] = i;
	}
	for(int i = 1;i<= n;i++)
		sum[i] = sum[i-1]+val[i];
	for(int i = 1;i<= n;i++)
	{
		if(id.count(sum[i]))
			next[id[sum[i]]] = i;
		id[sum[i]] = i;
	}
	ans = n;
	for(int i = 1;i<= n;i++)
		if(!vis[i])
		{
			top = 0;
			for(int j = i;j;j = next[j])
				stack[++top] = j,vis[j] = true;
			cnt+=(LL)top*(top-1)>>1;
			int k = 1;
			for(int j = 1;j<= top;j++)
			{
				while(k<j&&calc(stack[k],stack[j])>calc(stack[k+1],stack[j]))k++;
				ans = min(ans,calc(stack[k],stack[j]));
			}
		}
	printf("%lld %d",cnt,ans);
	return 0;
}
