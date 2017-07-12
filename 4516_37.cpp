
#include <stdio.h>
#include <map>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 2e5+5;
struct SAM
{
	map<int,int>trs[N];
	int fa[N],len[N];
	int cnt,last;
	long long ans;
	void init(){cnt = last = 1,ans = 0;}
	void insert(int x)
	{
		int p = last,newp = ++cnt,q,newq;
		last = newp,len[newp] = len[p]+1;
		for(;p&&!trs[p][x];p=fa[p])trs[p][x] = newp;
		if(!p)fa[newp] = 1;
		else
		{
			q = trs[p][x];
			if(len[q]==len[p]+1)fa[newp] = q;
			else
			{
				fa[newq=++cnt]=fa[q];
				len[newq] = len[p]+1;
				trs[newq] = trs[q];
				fa[newp] = fa[q] = newq;
				for(;p&&trs[p][x]==q;p=fa[p])trs[p][x]=newq;
			}
		}
		ans+=len[newp]-len[fa[newp]];
	}
}sam;
int d[N];
int main()
{
	int n;
	scanf("%d",&n);
	sam.init();
	for(int i = 1;i<= n;i++)
	{
		scanf("%d",&d[i]);
		sam.insert(d[i]);
		printf("%lld\n",sam.ans);
	}
	return 0;
}
