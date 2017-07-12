
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = 41;
int n,m,cnt;
LL K,mx;
struct Martix
{
	LL a[N*3][N*3];
	Martix()
	{
		memset(a,0,sizeof(a));
	}
	Martix operator*(const Martix &S)const
	{
		Martix ans;
		int i,j,k;
		for (i=0; i<=cnt; i++)
			for (j=0; j<=cnt; j++)
				if (S.a[i][j]<0 || a[i][j]<0)
				{
					ans.a[0][0]=-1; return ans;
				}
		for (i=0; i<=cnt; i++)
			for (j=0; j<=cnt; j++) 
				if (S.a[i][j])
				for (k=0; k<=cnt; k++) 
					if(a[j][k]){
					if (S.a[i][j]>K/a[j][k]){
						ans.a[0][0]=-1; return ans;
					}
					ans.a[i][k]+=S.a[i][j]*a[j][k];
					if (ans.a[i][k]>K){
						ans.a[0][0]=-1; return ans;
					}
				}
		return ans;
	}
};
Martix quick[65],b,c;
int id[N][3],st[N*3];
bool check()
{
	if (b.a[0][0]<0) return 0; 
	LL tmp=0;
	for (int i=1; i<=cnt; i++) 
		if (b.a[0][i] && st[i])
		{
			if(b.a[0][i]>K/st[i]) return 0;
			tmp+=b.a[0][i]*st[i];
			if (tmp>=K) return 0;
		}
	return 1;
}
int main()
{
	int x,y,C;
	scanf("%d%d%lld",&n,&m,&K);
	mx = K*3;
	for(int i = 1;i<= n;i++)
		for(int j = 0;j<3;j++)
			id[i][j] = ++cnt;
	Martix A;
	for(int i = 1;i<= n;i++)
	{
		for(int j = 0;j<2;j++)
			A.a[id[i][j]][id[i][j+1]]++;
		A.a[0][id[i][0]] = 1;
	}
	A.a[0][0] = 1;
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d%d",&x,&y,&C);
		A.a[id[x][C-1]][id[y][0]]++;
		st[id[x][C-1]]++;
	}
	int len = 0;
	while((LL)1<<len<=mx)len++;
	len--;
	quick[0] = A;
	for(int i = 1;i<= len;i++)
		quick[i] = quick[i-1]*quick[i-1];
	c.a[0][0] = 1;
	LL ans = 0;
	for(int i = len;i>=0;i--)
	{
		b = quick[i]*c;
		if(check())
		{
			ans|=((LL)1<<i);
			memcpy(c.a[0],b.a[0],sizeof(b.a[0]));
		}
	}
	ans++; 
	printf("%lld\n",(ans<=mx)?ans:-1);
	return 0;
}
