
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int mod = 2017;
struct Martix
{
	int d[35][35];
	int w,h;
	Martix(int _w=0,int _h=0):w(_w),h(_h){memset(d,0,sizeof(d));}
	Martix operator *(const Martix &s)const
	{
		Martix res(s.w,h);
		for(int i = 1;i<= res.w;i++)
			for(int k = 1;k<= s.h;k++)
				if(s.d[i][k])
					for(int j = 1;j<= res.h;j++)
						(res.d[i][j]+=s.d[i][k]*d[k][j]%mod)%=mod;
		return res;
	}
	friend Martix operator ^(const Martix &a,int s)
	{
		Martix res(a.w,a.h);
		Martix t = a;
		for(int i = 1;i<= a.w;i++)res.d[i][i] = 1;
		while(s)
		{
			if(s&1)res = res*t;
			t = t*t;
			s>>=1;
		}
		return res;
	}
};
int main()
{
	int n,m;
	int x,y;
	scanf("%d%d",&n,&m);
	Martix go(n+1,n+1),ans(n+1,1);
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d",&x,&y);
		go.d[x][y]++;
		go.d[y][x]++;
	}
	for(int i = 1;i<= n+1;i++)
		go.d[i][i]=1,go.d[n+1][i]=1;
	ans.d[1][1] = 1;
	int t;
	scanf("%d",&t);
	ans = ans*(go^t);
	int Ans = 0;
	for(int i = 1;i<= n+1;i++)(Ans+=ans.d[i][1])%=mod;
	printf("%d\n",Ans);
	return 0;
}
