
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e5+5;
struct E
{
	int next,to;
}e[N<<1];
int head[N],tot;
void add(int x,int y)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	head[x] = tot;
}
int stack[N],cnt,a[N];
bool cmp(int a,int b){return a>b;}
int dp(int x,int fa,int lim)
{
	int top = 0;
	for(int i = head[x];i;i = e[i].next)
		if(e[i].to!=fa)
			a[e[i].to] = dp(e[i].to,x,lim);
	for(int i = head[x];i;i = e[i].next)
		if(e[i].to!=fa)
			stack[++top] = a[e[i].to];
	sort(stack+1,stack+top+1,cmp);
	int max_dep = 0;
	if(top)
	{
		int i;
		for(i = 1;i<= top;i++)
		{
			if(stack[i]+1>lim)
				cnt++;
			else if(i<top&&stack[i]+stack[i+1]+2>lim)
				cnt++;
			else break;
		}
		if(i<=top)max_dep = stack[i]+1;
	}
	return max_dep;
}
int main()
{
	int n,k;
	scanf("%d%d",&n,&k);
	int x,y;
	for(int i = 1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y),add(y,x);
	}
	int L = 0,R = n+1;
	while(L<R)
	{
		int mid = (L+R)>>1;
		cnt = 0;
		dp(1,0,mid);
		if(cnt>k)L = mid+1;
		else R = mid;
	}
	printf("%d\n",L);
	return 0;
}
