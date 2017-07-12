
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int X = 300005;
const int N = 100005;
struct A{int opt,num;}ask[N];
int ans[N],modn[605],fa[X];
bool v[X];
int getfa(int x)
{
	if(fa[x]==x||!fa[x])return fa[x] = x;
	else return fa[x] = getfa(fa[x]);
}
int main()
{
	int n;
	char x[2];
	scanf("%d",&n);
	memset(ans,-1,sizeof(ans));
	memset(modn,0x3f,sizeof(modn));
	for(int i = 1;i<= n;i++)
	{
		scanf("%s%d",x,&ask[i].num);
		if(x[0]=='A')
		{
			for(int j = 1;j<= 600;j++)
				modn[j] = min(modn[j],ask[i].num%j);
			ask[i].opt = 1;
			v[ask[i].num] = true;
		}
		else 
		{
			if(ask[i].num<=600)ans[i] = modn[ask[i].num];
			ask[i].opt = 2;
		}
	}
	for(int i = 1;i<=X-5;i++)
		if(!v[i])
			fa[i] =i+1;
	for(int i = n;i>= 1;i--)
	{
		if(ask[i].opt==1)fa[ask[i].num] = ask[i].num+1;
		else if(ask[i].num>600)
		{
			int tmp = 0x3f3f3f3f;
			for(int j = 0;j<= X-5;j+=ask[i].num)
			{
				int tt = getfa(max(1,j));
				if(tt<=X-5)tmp = min(tmp,tt%ask[i].num);
			}
			ans[i] = tmp;
		}
	}
	for(int i = 1;i<= n;i++)
		if(ans[i]!=-1)
			printf("%d\n",ans[i]);
	return 0;
}
