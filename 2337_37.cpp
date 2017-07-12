
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef unsigned int UI;
const int N = 105;
const double eps = 1e-8;
int n;
double f[N][N],ans[N],cnt[N];
struct E
{int next,to,val;}e[N*N*2];
int head[N],tot;
void add(int x,int y,int f)
{
	cnt[x]++;
	e[++tot].to = y;
	e[tot].next = head[x];
	e[tot].val = f;
	head[x] = tot;
}
void work()
{
	for(int i = 1;i< n;i++)
	{
		int xn = i;
		while(fabs(f[xn][i])<eps)xn++;
		if(xn!=i)swap(f[xn],f[i]);
		for(int line = i+1;line<= n;line++)
		{
			double tmp = f[line][i]/f[i][i];
			for(int j = 1;j<= n+1;j++)
				f[line][j]-=f[i][j]*tmp;
		}
	}
	for(int i = n-1;i>= 1;i--)
	{
		for(int j = i+1;j<= n;j++)
			f[i][n+1]-=f[i][j]*ans[j];
		ans[i] = f[i][n+1]/f[i][i];
	}
}
int main()
{
	int m,x,y;
	UI c;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d%u",&x,&y,&c);
		add(x,y,c);
		if(x!=y)add(y,x,c);
	}
	double t_ans = 0;
	for(int pos = 0;pos<32;pos++)
	{
		memset(f,0,sizeof(f));
		for(int i = 1;i< n;i++)
			for(int j = head[i];j;j = e[j].next)
			{
				if(e[j].val&(1<<pos))f[i][e[j].to]+=1.0,f[i][n+1]+=1.0;
				else f[i][e[j].to]-=1.0;
			}
		for(int i = 1;i< n;i++)
			f[i][i]+=cnt[i];
		memset(ans,0,sizeof(ans));
		work();
		t_ans+=ans[1]*(1<<pos);
	}
	printf("%.3f\n",t_ans);
	return 0;
}
