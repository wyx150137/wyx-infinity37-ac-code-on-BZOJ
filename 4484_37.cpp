
#include <stdio.h>
#include <bitset>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 3e4+5;
const int M = 1e5+5;
bitset<N>bit[N];
struct E
{int next,to;}e[M];
struct data
{
	int en,v;
	bool operator <(const data &a)const
	{
		return v>a.v;
	}
}a[N];
int head[N],tot,d[N],n,m,len[N];
void add(int x,int y)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	head[x] = tot;
	d[y]++;
}
int q[N],s,t,ans=0;
void getans()
{
	s = 1,t = 0;
	for(int i = 1;i<= n;i++)
		if(!d[i])
			q[++t] = i;
	while(s<=t)
	{
		int x = q[s++];
		for(int i = head[x];i;i=e[i].next)
			if(!(--d[e[i].to]))
				q[++t] = e[i].to;
	}
	int num;
	for(int i = t;i>= 1;i--)
	{
		int x = q[i];
		bit[x][x] = 1,num = 0,len[x] = 1;
		for(int j = head[x];j;j=e[j].next)
		{
			a[++num] = (data){e[j].to,len[e[j].to]};
			len[x] = max(len[x],len[e[j].to]+1);
		}
		sort(a+1,a+num+1);
		for(int j = 1;j<= num;j++)
		{
			int y = a[j].en;
			if(bit[x][y])ans++;
			bit[x]|=bit[y];
		}
	}	
}
int main()
{
	int x,y;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y);
	}
	getans();
	printf("%d\n",ans);
	return 0;
}
