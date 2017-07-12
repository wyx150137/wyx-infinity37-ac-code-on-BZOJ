
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 305;
struct E
{int next,to,val;}e[N*N];
int head[N],tot;
void add(int x,int y,int f)
{e[++tot].to = y;e[tot].next = head[x];head[x] = tot;e[tot].val = f;}
int f[2][N][N];
int main()
{
	int n,m,x,y,z;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		add(x,y,z);
	}
	memset(f,0x3f,sizeof(f));
	int now = 0,pre = 1;
	for(int i = 1;i<= n;i++)f[pre][i][i]=0;
	for(int ans = 1;ans<= n;ans++)
	{
		memset(f[now],0x3f,sizeof(f[now]));
		for(int st = 1;st<= n;st++)
			for(int pe = 1;pe<= n;pe++)
				for(int i = head[pe];i;i=e[i].next)
					f[now][st][e[i].to] = min(f[now][st][e[i].to],f[pre][st][pe]+e[i].val);
		for(int i = 1;i<= n;i++)
			if(f[now][i][i]<0)
			{
				printf("%d\n",ans);
				return 0;
			}
		swap(now,pre);
	}
	printf("0");
	return 0;
}
