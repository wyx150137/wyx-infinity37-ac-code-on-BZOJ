
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define lowbit(x) ((x)&(-x))
using namespace std;
const int N = 300;
int a[100+1][300+1][300+1];
int k[300+1][300+1];
inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x * f;
}

void updata(int x,int y,int num,int tmp)
{
	for(int i=x;i<=N;i+=lowbit(i))
		for(int j=y;j<=N;j+=lowbit(j))
			a[num][i][j] += tmp;
}

int ask(int x,int y,int num)
{
	int ans = 0;
	for(int i=x;i>0;i-=lowbit(i))
		for(int j=y;j>0;j-=lowbit(j))
			ans += a[num][i][j];
	return ans;
}	

int main()
{
	int n = read(),m=read();
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			k[i][j] = read();
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			updata(i,j,k[i][j],1);
	int Q = read();
	while(Q--)
	{
		int op = read();
		if(op == 1)
		{
			int x = read(),y=read();
			updata(x,y,k[x][y],-1);
			k[x][y] = read();
			updata(x,y,k[x][y],1);
		}
		else
		{
			int x1 = read(),x2=read(),y1=read(),y2=read();
			int c = read();
			int tt1 = ask(x1-1,y1-1,c);
			int tt2 = ask(x2,y2,c);
			int tt3 = ask(x2,y1-1,c);
			int tt4 = ask(x1-1,y2,c);
			int ans = tt2 + tt1 - tt3 - tt4;
			printf("%d\n",ans);
		}
	}
}
