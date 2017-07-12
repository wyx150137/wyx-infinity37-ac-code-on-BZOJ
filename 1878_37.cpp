
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 50005;
const int M = 200005;
int a[N],last[1000005],next[N];
int num[N],c[N];
struct ask{int x,y,ans,no;}A[M];
bool cmp(ask a,ask b)
{
	if(a.x==b.x)return a.y<b.y;
	return a.x<b.x;
}
bool cmp1(ask a,ask b){return a.no<b.no;}
void update(int x)
{
	if(x==0)return ;
	for(int i = x;i<=N;i+=i&(-i))
		c[i]++;
}
int getans(int x)
{
	int ans = 0;
	for(int i = x;i>0;i-=i&(-i))
		ans+=c[i];
	return ans;
}
int main()
{
	int n,m;
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
	{
		scanf("%d",&a[i]);
		if(last[a[i]]!=0)next[last[a[i]]] = i;
		else update(i);
		last[a[i]] = i;
	}
	scanf("%d",&m);
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d",&A[i].x,&A[i].y);
		A[i].no = i;
	}
	sort(A+1,A+m+1,cmp);
	int l = 1;
	for(int i = 1;i<= m;i++)
	{
		while(l<A[i].x)
		{
			update(next[l]);
			l++;
		}
		int tmp = getans(A[i].y);
		A[i].ans = tmp-getans(A[i].x-1);
	}
	sort(A+1,A+m+1,cmp1);
	for(int i = 1;i<= m;i++)
		printf("%d\n",A[i].ans);
	return 0;
}
