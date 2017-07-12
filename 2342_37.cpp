
#include <stdio.h>
#include <set>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 500005;
int p[N],q[N];
char s[N];
set<int>t;
bool cmp(int a,int b)
{
	return a-p[a]<b-p[b];
}
int main()
{
	int n;
	scanf("%d",&n);
	scanf("%s",s+1);
	s[0]='#';
	int maxp = 0,id = 0;
	for(int i = 1;i<= n;i++)
	{
		if(maxp>=i)p[i]=min(p[id*2-i],maxp-i);
		else p[i]=0;
		for(;s[i+p[i]+1]==s[i-p[i]];p[i]++);
		if(p[i]+i>maxp)maxp = p[i]+i,id=i;
	}
	for(int i = 1;i<= n;i++)q[i]=i;
	sort(q+1,q+n+1,cmp);
	int now = 1,ans = 0;
	for(int i = 1;i<= n;i++)
	{
		while(now<=n&&q[now]-p[q[now]]<=i)
		{
			t.insert(q[now]);
			now++;
		}
		set<int>::iterator tmp=t.upper_bound(i+p[i]/2);
		if(tmp!=t.begin())
		{
			ans=max(ans,(*--tmp-i)*4);
		}
	}
	printf("%d\n",ans);
	return 0;
}
