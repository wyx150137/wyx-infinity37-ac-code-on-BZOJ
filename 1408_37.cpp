
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1005;
const int mod = 10000;
int p[N],e[N];
int quick_pow(int x,int y)
{
	if(y==0)return 1;
	int tmp = quick_pow(x,y>>1);
	if(y&1)return tmp*tmp%mod*x%mod;
	else return tmp*tmp%mod;
}
int main()
{
	int k;
	scanf("%d",&k);
	for(int i = 1;i<= k;i++)
		scanf("%d%d",&p[i],&e[i]);
	int ans1=0,ans2=0,ans3,tmp1,tmp2;
	for(int i = 1;i<= k;i++)
	{
		if(p[i]==2)continue;
		tmp1 = (ans1+ans2*(p[i]-1)%mod)%mod;
		tmp2 = (ans2+(ans1+1)*(p[i]-1)%mod)%mod;
		ans1 = tmp1,ans2 = tmp2;
	}
	int m = 1;
	for(int i = 1;i<= k;i++)
		m = m*quick_pow(p[i]%mod,e[i])%mod;
	ans3 = (((m-1)-ans1-ans2)%mod+mod)%mod;
	printf("%d\n%d\n%d\n",ans1,ans2,ans3);
	return 0;
}
