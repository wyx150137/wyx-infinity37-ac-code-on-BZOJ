
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int N = 505;
const double eps = 1e-8;
struct E
{int next,to;}e[N*N];
int head[N],tot,n,m;
void add(int x,int y)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	head[x] = tot;
}
double f[N][N],cnt[N];
double Ans[N*N],ans[N];
void work()
{
	for(int i = 1;i< n;i++)
	{
		int xn = i;
		while(fabs(f[xn][i])<eps)xn++;
		if(xn!=i)swap(xn,i);
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
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= m;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);add(v,u);
		cnt[u]+=1.0;cnt[v]+=1.0;
	}
	for(int i = 1;i< n;i++)
	{
		for(int j = head[i];j;j = e[j].next)
			f[i][e[j].to] += 1.0/cnt[e[j].to];
		f[i][i]-=1.0;
	}
	f[1][n+1]-=1.0;
	work();
	int tmp = 0;
	for(int i = 1;i< n;i++)
	{
		for(int j = head[i];j;j = e[j].next)
			if(e[j].to>i)
				Ans[++tmp] = ans[i]/cnt[i]+ans[e[j].to]/cnt[e[j].to];
	}
	sort(Ans+1,Ans+tmp+1);
	double t_ans = 0;
	for(int i = 1;i<= tmp;i++)
		t_ans+=Ans[i]*(m-i+1);
	printf("%.3f\n",t_ans);
	return 0;
}
