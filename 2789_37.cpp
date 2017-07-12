
#include <stdio.h>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e6+5;
int last[30],next[N],val[N],c[N];
char s1[N],s2[N];
queue <int>Q[30];
void update(int x,int t)
{
	for(int i = x;i<N;i+=i&(-i))
		c[i]+=t;
}
int getans(int x)
{
	int sum = 0;
	for(int i = x;i>0;i-=i&(-i))
		sum+=c[i];
	return sum;
}
int main()
{
	int n;
	scanf("%d",&n);
	scanf("%s",s1+1);
	scanf("%s",s2+1);
	for(int i = 1;i<= n;i++)
		Q[s1[i]-'A'].push(i);
	for(int i = 1;i<= n;i++)
	{
		val[i] = Q[s2[i]-'A'].front();
		Q[s2[i]-'A'].pop();
	}
	long long ans = 0;
	for(int i = 1;i<= n;i++)
	{
		ans+=getans(n)-getans(val[i]);
		update(val[i],1);
	}
	printf("%lld",ans);
	return 0;
}
