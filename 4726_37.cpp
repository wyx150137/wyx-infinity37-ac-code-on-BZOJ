
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 5e5+5;
const double eps = 1e-7;
struct E
{int next,to;}e[N<<1];
double f[N],ans;
int head[N],tot,n,k;
void add(int x,int y)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	head[x] = tot;
}
int size[N];
void get_size(int x)
{
	size[x] = 1;
	bool lef = true;
	for(int i = head[x];i;i=e[i].next)
	{
		lef = false;
		get_size(e[i].to);
		size[x]+=size[e[i].to];
	}
	if(lef)f[x] = 1;
	else
	{
		for(int i = head[x];i;i=e[i].next)
			f[x] = max(f[x],min(1.0*size[e[i].to]/(size[x]-1),f[e[i].to]));
	}
	if(size[x]>k)ans = max(ans,f[x]);
}
int main()
{
	scanf("%d%d",&n,&k);
	for(int i = 2;i<=n;i++)
	{
		int x;scanf("%d",&x);
		add(x,i);
	}
	get_size(1);
	printf("%.7lf",ans);
	return 0;
}
