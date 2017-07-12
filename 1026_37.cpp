
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
long long f[15][15];
long long get_ans(long long x)
{
	int num[15] = {},cnt = 0;
	long long ans = 0;
	while(x)
	{
		num[++cnt] = x%10;
		x/=10;
	}
	for(int i = 1;i<= num[cnt]-1;i++)
		ans+=f[cnt][i];
	for(int i = cnt-1;i>=1;i--)
		for(int j = 1;j<= 9;j++)
			ans+=f[i][j];
	for(int i = cnt-1;i>= 1;i--)
	{
		for(int j = 0;j<= num[i]-1;j++)
			if(abs(j-num[i+1])>=2)
				ans+=f[i][j];
		if(abs(num[i+1]-num[i])<2)break;
	}
	return ans;
}
int main()
{
	long long a,b;
	scanf("%lld%lld",&a,&b);
	for(int i = 0;i<= 9;i++)
		f[1][i] = 1;
	for(int i = 2;i<= 10;i++)
		for(int j = 0;j<= 9;j++)
			for(int k = 0;k<=9;k++)
				if(abs(j-k)>=2)
					f[i][j]+=f[i-1][k];
	printf("%lld",get_ans(b+1)-get_ans(a));
	return 0;
}
