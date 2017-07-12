
#include <vector>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 500+5;
const int M = 60000+5;
#define lowbit(x) ((x)&(-x))
using namespace std;

int mp[N][N], tr[N][N];
vector <int> V[2][N*N];

void change(int x,int y)
{
	for(int i=x;i<N;i+=lowbit(i))
		for(int j=y;j<N;j+=lowbit(j))
			tr[i][j] ++;
}

inline int ask(int x,int y)
{
	int ans = 0;
	for(int i=x;i;i-=lowbit(i))
		for(int j=y;j;j-=lowbit(j))
			ans += tr[i][j];
	return ans;
}

struct data
{
	int x,y,num;
	bool operator < (const data &z)const
	{
		return num < z.num;
	}
	data () {}
	data (int _,int __,int ___)
	:x(_),y(__),num(___){}
}T[N*N];

struct Query
{
	int x[4],y[4],L,R,id,K;
	inline int calc()
	{
		return ask(x[0],y[0]) + ask(x[1],y[1]) - ask(x[2],y[2]) - ask(x[3],y[3]);
	}
}a[M];

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

void init(int x)
{
	for(int i=1;i<=N*N;++i) V[x][i].clear();
	memset(tr,0,sizeof tr);
}

int main()
{
	
	int n = read(), tt = 0 , Q = read();

	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			T[++tt] = data(i+1,j+1,mp[i][j] = read());
	sort(T+1,T+tt+1);

	int tmp = 1 + tt; tmp >>= 1;

	for(int i=1;i<=Q;++i)
	{
		int x1 = read()+1, y1 = read()+1, x2 = read()+1, y2 = read()+1 ,K = read();
		a[i].x[0] = x1 - 1, a[i].y[0] = y1 - 1;
		a[i].x[1] = x2 ,    a[i].y[1] = y2;
		a[i].x[2] = x1 - 1, a[i].y[2] = y2;
		a[i].x[3] = x2,     a[i].y[3] = y1 - 1;
		a[i].id = i, a[i].L = 1, a[i].R = tt, a[i].K = K;
		V[1][tmp].push_back(i);
	}

	for(int times = 1; times <= 19; ++ times)
	{
		init((times+1)&1);
		int o = (times+1)&1,op = times & 1;
		for(int i=1;i<=n*n;++i)
		{
			change(T[i].x,T[i].y);

			for(int k=0;k<V[op][i].size();++k)
			{
				int t = V[op][i][k], now = a[t].calc(),nowmid = (a[t].L + a[t].R) >> 1;
				if(a[t].L >= a[t].R) continue;
				else if(now < a[t].K) a[t].L = nowmid+1;
				else a[t].R = nowmid ;
				nowmid = (a[t].L + a[t].R) >> 1;
				V[o][nowmid].push_back(a[t].id);
			}
		}
	}

	for(int i=1;i<=Q;++i)
		printf("%d\n",T[a[i].L].num);
	
}
