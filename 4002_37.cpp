
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;
typedef unsigned long long ll;
const ll mod = 7528443412579576937ll;
ll quick_plus(ll x,ll y)
{
	if(y==0)return 0;
	ll tmp = quick_plus(x,y>>1);
	if(y&1)return ((tmp+tmp)%mod+x)%mod;
	else return (tmp+tmp)%mod;
}
struct Matrix
{
	ll d[2][2];
	Matrix(){memset(d,0,sizeof(d));}
	void operator*=(const Matrix &s)
	{
		Matrix res;
		for(int i = 0;i<2;i++)for(int k = 0;k<2;k++)if(d[i][k])
			for(int j = 0;j<2;j++)
				(res.d[i][j]+=quick_plus(d[i][k],s.d[k][j]))%=mod;
		*this = res;
	}
	friend Matrix quick_pow(Matrix x,ll y)
	{
		Matrix ans;
		for(int i = 0;i<2;i++)ans.d[i][i]=1;
		while(y)
		{
			if(y&1)ans*=x;
			x*=x;
			y>>=1;
		}
		return ans;
	}
}a;
int main()
{
	ll b,d,n;
	scanf("%llu%llu%llu",&b,&d,&n);
	a.d[0][0] = 0;
	a.d[1][0] = 1;
	a.d[0][1] = (d-b*b)/4;
	a.d[1][1] = b;
	Matrix ans = quick_pow(a,n);
	ll Ans = (quick_plus(ans.d[0][0],2)+quick_plus(ans.d[1][0],b))%mod;
	Ans = Ans-(b!=d*d&&(~n&1));
	printf("%llu\n",(Ans+mod)%mod);
	return 0;
}
