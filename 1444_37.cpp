
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
#define s(i) (s[i]-'A')
const int N = 105;
const double eps = 1e-6;
const double EPS = 1e-4;
int p[15],q[15],cnt;
int ch[N][15],n,m,l,pos[N];
char s[15];
int fail[N],danger[N];
void init()
{
	cnt = 1;
	for(int i = 0;i<m;i++)
		ch[0][i] = 1;
}
void insert(int id)
{
	int now = 1,i = 0;
	while(s[i])
	{
		if(!ch[now][s(i)])ch[now][s(i)]=++cnt;
		now = ch[now][s(i)];
		i++;
	}
	danger[now] = true;
	pos[id] = now;
}
int Q[N],h,t;
void build()
{
	h = 0,t = -1;
	Q[++t]=1,fail[0]=1;
	while(h<=t)
	{
		int x=Q[h++];
		for(int i = 0;i<m;i++)
		{
			int j = ch[x][i];
			if(j)
			{
				Q[++t] = j;
				int r = fail[x];
				while(!ch[r][i])r = fail[r];
				fail[j] = ch[r][i];
				danger[j]|=danger[fail[j]];
			}
			else ch[x][i] = ch[fail[x]][i];
		}
	}
}
struct Matrix 
{
	int w,h;
	double d[105][105];
	Matrix(){}
	Matrix(int _w,int _h):w(_w),h(_h){memset(d,0,sizeof(d));}
	void operator*=(const Matrix &S)
	{
		Matrix res(w,S.h);
		for(int i = 1;i<=res.w;i++)
			for(int j = 1;j<=res.h;j++)
			{
				res.d[i][j] = 0;
				for(int k = 1;k<=h;k++)
					res.d[i][j]+=d[i][k]*S.d[k][j];
			}
		*this = res;		
	}
};
void debug(const Matrix &f)
{
	for(int i = 1;i<= 6;i++)
	{
		for(int j = 1;j<= 6;j++)
			printf("%5.2f",f.d[i][j]);
		printf("\n");
	}
}
int main()
{
	scanf("%d%d%d",&n,&l,&m);
	for(int i = 0;i< m;i++)
		scanf("%d%d",&p[i],&q[i]);
	init();
	for(int i = 1;i<= n;i++)
	{
		scanf("%s",s);
		insert(i);
	}
	build();
	Matrix f(cnt,cnt);
	for(int i= 1;i<= cnt;i++)
	{
		if(danger[i])
			f.d[i][i]=1;
		else
			for(int j =0;j<m;j++)
				f.d[i][ch[i][j]]+=(double)p[j]/(double)q[j];
	}
	for(int i = 1;i<= 50;i++)
		f*=f;
	for(int i = 1;i<= n;i++)
		printf("%.2f\n",f.d[1][pos[i]]);
	return 0;
}
