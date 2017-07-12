
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long LL;
const LL mod = 1e9+7;
LL f[65][2],ans;
struct Martix
{
	int h,w;
	LL map[4][4];
	Martix(int x,int y)
	{
		h = x;
		w = y;
		memset(map,0,sizeof(map));
	}
	Martix()
	{
		h = w = 0;
		memset(map,0,sizeof(map));
	}
	Martix operator*(const Martix &S)const
	{
		Martix ans(S.w,h);
        for(int i = 1;i<= ans.h;i++)
            for(int j = 1;j<= ans.w;j++)
                for(int k = 1;k<= S.h;k++)
                    (ans.map[i][j]+=map[i][k]*S.map[k][j])%=mod;
		return ans;
	}
};
Martix quick_pow(LL y,const Martix &S) 
{
	if(y==0)
	{
		Martix one(3,3);
		for(int i = 0;i<= 3;i++)
			one.map[i][i] = 1;
		return one;
	}
	Martix tmp = quick_pow(y/2,S);
	if(y&1)return tmp*tmp*S;
	else return tmp*tmp;	
}
void init()
{
	f[1][1] = 1,f[1][0] = 1;
	for(int j = 2;j<= 63;j++)
	{
		f[j][0] = f[j-1][0]+f[j-1][1];
		f[j][1] = f[j-1][0];
	}
}
void work(LL n)
{
	//LL tmp = n;
	int cnt = 63;
    while(n < ((LL)1<<(cnt-1))) cnt--;
	for(int i = 1;i < cnt;i++)
        ans += f[i][1];
	int cur = n / ((LL)1<<(cnt-1));
    int pre = cur;
    n %= ((LL)1<<(cnt-1));
	for(int j = cnt-1;j>=1;j--)
	{
		cur = n/((LL)1<<(j-1));
		if(cur)
			ans+=f[j][0];
		if(cur&&pre)break;
		pre = cur;
		n%=((LL)1<<(j-1));
	}
}
int main()
{
	init();
	int T;
	scanf("%d",&T);
	LL n;
	while(T--)
	{
		scanf("%lld",&n);
		ans = 0;
		work(n+1);
		Martix sta(1,2);
		sta.map[1][1] = 1;sta.map[1][2] = 1;
		Martix go(2,2);
		go.map[1][1] = go.map[1][2] = go.map[2][1] = 1;
		sta = sta*quick_pow(n,go);
		printf("%lld\n%lld\n",ans,sta.map[1][1]);
	}
	return 0;
}
