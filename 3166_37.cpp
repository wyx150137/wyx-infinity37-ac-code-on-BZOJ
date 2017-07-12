
#include <stdio.h>
#include <set>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 50005;
const int M = 35*N;
const int INF = 1e9+1;
int root[N];
set<int>q;
struct Data{int pos,val;}a[N];
bool operator<(Data a,Data b)
{
	return a.val>b.val;
}
struct Trie
{
	int ch[M][2],cnt,sum[M];
	int insert(int x,int num)
	{
		int tmp,y;
		tmp=y=++cnt;
		for(int i=30;i>=0;i--)
		{
			int t = num&(1<<i);t=t>>i;
			ch[y][0] = ch[x][0];
			ch[y][1] = ch[x][1];
			x = ch[x][t];
			y = ch[y][t] = ++cnt;
			sum[y]=sum[x]+1;
		}
		return tmp;
	}
	int getans(int l,int r,int val)
	{
		int ans = 0;
		for(int i = 30;i>= 0;i--)
		{
			int t = val&(1<<i);t=t>>i;
			if(sum[ch[r][t^1]]-sum[ch[l][t^1]]>0)
				l=ch[l][t^1],r = ch[r][t^1],ans+=(1<<i);
			else l = ch[l][t],r = ch[r][t];
		}
		return ans;
	}
}trie;
int main()
{
	int n;
	scanf("%d",&n);
	for(int i= 1;i<= n;i++)
	{
		scanf("%d",&a[i].val);
		a[i].pos = i;
	}
	for(int i = 1;i<= n;i++)
		root[i] = trie.insert(root[i-1],a[i].val);
	q.insert(-2),q.insert(-1),q.insert(INF),q.insert(INF+1);
	sort(a+1,a+n+1);
	q.insert(a[1].pos);
	int ans = 0;
	for(int i = 2;i<= n;i++)
	{
		int l = a[i].pos,r = a[i].pos,x = a[i].pos;
		set<int>::iterator t,p;
		p=q.lower_bound(x);
		t = p;
		r = *t;t++;r = *t-1;
		l = *--p;p--;l=*p+1;
		l = max(1,l),r = min(r,n);
		if(l!=r)ans = max(ans,trie.getans(root[l-1],root[r],a[i].val));
		q.insert(x);
	}
	printf("%d\n",ans);
	return 0;
}
