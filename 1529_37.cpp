
#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1000005;
int fa[N];
int getfa(int x)
{
	if(fa[x]==x)return fa[x] = x;
	else return fa[x] = getfa(fa[x]);
}
void uni(int x,int y)
{
	int fx = getfa(x),fy = getfa(y);
	if(fx!=fy)
		fa[fx] = fy;
}
int main()
{
	int n,x;
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)fa[i] = i;
	for(int i = 1;i<= n;i++)
	{
		scanf("%d",&x);
		uni(x,i);
	}
	int ans = 0;
	for(int i = 1;i<= n;i++)
		if(fa[i]==i)
			ans++;
	printf("%d\n",ans);
	return 0;
}
