
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e5+5;
int l[N],r[N],maxx,minx,n,ans;
void dfs(int x,int dep)
{
	if(x==-1){maxx = max(maxx,dep),minx = min(minx,dep);return ;}
	dfs(l[x],dep+1);
	dfs(r[x],dep+1);
}
int solve(int x,int dep)
{
	int a,b;
	if(x==-1)
	{
		if(dep==minx)return 1;
		else return 2;
	}
	a = solve(l[x],dep+1);
	b = solve(r[x],dep+1);
	if((a==1&&b==2)||(a==1&&b==3)||(a==3&&b==2))ans++;
	if(a==3&&b==3){printf("-1\n");exit(0);}
	return a|b;
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
		scanf("%d%d",&l[i],&r[i]);
	maxx = 0,minx = N*10;
	dfs(1,0);
	if(maxx-minx>=2)printf("-1\n");
	else if(maxx==minx)printf("0\n");
	else
	{
		solve(1,0);
		printf("%d\n",ans);
	}
	return 0;
}
