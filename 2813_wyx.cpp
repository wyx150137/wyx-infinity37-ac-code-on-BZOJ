
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <string.h>
typedef long long LL;
const int N = 1e7+5;
const int mod = 1000000007;

using namespace std;

int prime[N];
bool flag[N];
int f[N],g[N];
int T[N];
int tmp[N];
int cnt = 0;

void pre(int n)
{
	f[1] = g[1]  = 1;
	int i=1,j=2;
	for(i=2;i<=n;++i)
	{
		if(!flag[i])
		{
			prime[++cnt] = i;
			f[i] = ((LL)i*i%mod+1)%mod;
			g[i] = 2;
			T[i] = 1;
			tmp[i] = 1;
		}
		for(j=1;(LL)prime[j]*i <= n;++j)
		{
			flag[prime[j]*i] = 1;
			if(i%prime[j]!=0)
			{	
				g[prime[j]*i] = 2*g[i];
				f[prime[j]*i] = (LL)f[i]*((LL)prime[j]*prime[j]%mod+1)%mod;
				T[prime[j]*i] = i; 
				tmp[prime[j]*i] = 1;
			}
			else
			{
				g[prime[j]*i] = g[i]/(tmp[i]+1)*(tmp[i]+2);
				f[prime[j]*i] = ((LL)f[i]*prime[j]%mod*prime[j]%mod+(LL)f[T[i]])%mod;
				T[prime[j]*i] = T[i];
				tmp[prime[j]*i] = tmp[i]+1;
				break;				
			}
		}
	}
}

void test()
{
	for(int i=1;i<=100;++i)
		cout << g[i] << " "  << f[i] << endl;
	
}

int main()
{
	int Q;
	cin >> Q;
	LL tmp , A, B ,C;
	cin >> tmp >> A >> B >> C;
	pre(1e7);
	
//	test();
	
	LL ans1 = 0;
	LL ans2 = 0;
	while(Q--)
	{
		(ans1 += g[tmp])%=mod;
		(ans2 += f[tmp])%=mod;
		if(tmp &1) ans1 ++, ans2 += 4;
		((tmp *= A) += B )%=C;
		tmp++;
	}
	cout << ans1 << endl << ans2 << endl;
}
