
#include <stdio.h>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e4+5;
const int M = 2e4+5;
const int P = 60;
const int T = 80;
const double eps = 1e-6;
const int INF = 0x3f3f3f3f;
struct Trie
{
	int ch[N*20][T],cnt;
	int lazy[N*20],sign;
	char s[T];
	int insert()
	{
		scanf("%s",s+1);
		int x = 0,alp;
		for(int i = 1;s[i];i++)
		{
			alp = s[i]-'0';
			if(!ch[x][alp])ch[x][alp]=++cnt;
			x = ch[x][alp];
		}
		if(!lazy[x])lazy[x] = ++sign;
		return lazy[x];
	}
	int judge()
	{
		for(int i=1;s[i];i++)
            if(i>=5&&s[i]=='t'&&s[i-1]=='r'&&s[i-2]=='a'&&s[i-3]=='t'&&s[i-4]=='s')return 1;
        for(int i=1;s[i];i++)
        	if(i>=3&&s[i]=='s'&&s[i-1]=='a'&&s[i-2]=='g')return 2;
        for(int i=1;s[i];i++)
        	if(i>=3&&s[i]=='d'&&s[i-1]=='n'&&s[i-2]=='e')return 3;
        return 0;
	}
}trie;
struct E
{
	int u,v,next;
	double val;
}e[M<<1],E[15][P*P*2];
int head[N],tot;
int Head[15][P],cnt[15];
void add(int x,int y,double f)
{
	e[++tot].u = x;
	e[tot].v = y;
	e[tot].next = head[x];
	e[tot].val = f;
	head[x] = tot;
}
void ADD(int l,int x,int y,double f)
{
	E[l][++cnt[l]].u = x;
	E[l][cnt[l]].v = y;
	E[l][cnt[l]].val = f;
	E[l][cnt[l]].next = Head[l][x];
	Head[l][x] = cnt[l];
	//printf("%d %d %d %.5lf\n",l,x,y,f);
}
struct Point
{
	int x,y;
	Point(){}
	Point(int x,int y):x(x),y(y){}
};
queue<Point>Q;
double dis[15][N],aver[N];
bool in[15][N];
int n,m,light,gas,cost;
bool red[N];
int sta[N],gass[N],num;
char tmp[T];
void SPFA(int s)
{
	while(!Q.empty())Q.pop();
	memset(dis,0x7f,sizeof(dis));
	dis[0][s] = 0;
	in[0][s] = true;
	Q.push(Point(0,s));
	while(!Q.empty())
	{
		Point tt = Q.front();
		Q.pop();
		in[tt.x][tt.y] = false;
		for(int i = head[tt.y];i;i=e[i].next)
		{
			int to = e[i].v,temp = tt.x+red[to];
			if(temp<=light&&dis[tt.x][tt.y]+e[i].val+aver[to]<=gas&&dis[temp][to]>dis[tt.x][tt.y]+e[i].val+aver[to])
			{
				dis[temp][to] = dis[tt.x][tt.y]+e[i].val+aver[to];
				if(!in[temp][to])
				{
					in[temp][to] =true;
					Q.push(Point(temp,to));
				}
			}
		}
	}
}
double spfa(int s,int t)
{
	while(!Q.empty())Q.pop();
	memset(dis,0x7f,sizeof(dis));
	dis[0][s] = 0;
	in[0][s] = true;
	Q.push(Point(0,s));
	while(!Q.empty())
	{
		Point tt = Q.front();
		Q.pop();
		in[tt.x][tt.y] = false;
		for(int j = 0;j+tt.x<=light;j++)
		{
			for(int i = Head[j][tt.y];i;i=E[j][i].next)
			{
				int to = E[j][i].v;
				if(dis[j+tt.x][to]>dis[tt.x][tt.y]+cost+E[j][i].val)
				{
					dis[j+tt.x][to] = dis[tt.x][tt.y]+cost+E[j][i].val;
					if(!in[j+tt.x][to])
					{
						in[j+tt.x][to] = true;
						Q.push(Point(j+tt.x,to));
					}
				}
			}
		}
	}
	double ans = 99999999999.999;
	for(int i = 0;i<= light;i++)
		ans = min(ans,dis[i][t]);
	return ans;
}
int main()
{
	scanf("%d%d%d%d%d",&n,&m,&light,&gas,&cost);
	int k,s,t,v,ia,ib;
	double a,b,c;
	for(int i = 1;i<= n;i++)
	{
		trie.insert();
		if(k = trie.judge())
		{
			sta[i] = ++num;
			gass[num] = i;
			if(k==1)s=i;
			if(k==3)t=i;
		}
		scanf("%lf%lf",&a,&b);
		if(k==1||k==3)continue;
		if(a>eps)
            red[i]=1,aver[i]=a*a/2.0/(a+b);
	}
	for(int i = 1;i<= m;i++)
	{
		ia = trie.insert();
		ib = trie.insert();
		scanf("%s",tmp);
		scanf("%lf",&c);
		add(ia,ib,c),add(ib,ia,c);
	}
	for(int i = 1;i<= num;i++)
	{
		SPFA(gass[i]);
		for(int j = 1;j<= num;j++)
		{
			v = gass[j];
			if(j!=i)
			{
				for(int k = 0;k<=light;k++)
					if(dis[k][v]<INF)
						ADD(k,i,j,dis[k][v]);
			}
		}
	}
	printf("%.3lf\n",spfa(sta[s],sta[t])-cost);
	return 0;
}
