
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
const int inf = 1e9+7;
const int N = 100000+10;
const int M = 1000000+10;
using namespace std;

int f[M];
int prime[M];
int tot;

void init(int MAX)
{
	for(int i=2;i<=MAX;++i)
	{
		if(!f[i]) f[i] = 1,prime[++tot] = i;
		for(int j=1;prime[j]*i<=MAX;++j)
		{
			f[prime[j]*i] = f[i] + 1;
			if(i%prime[j] == 0) break;
		}
	}
}

int MIN[M][2],a[N];

void updata(int x,int i)
{
	if(f[a[x]] <= f[a[MIN[i][0]]])
	{
		MIN[i][1] = MIN[i][0];
		MIN[i][0] = x;
	}	
	else if(f[a[x]] <= f[a[MIN[i][1]]])
	{
		MIN[i][1] = x;
	}
}

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int main()
{
//	freopen("07.in","r",stdin);
	f[0] = 1e9+7;
	int MAX = 0;
	int n = read();
	for(int i=1;i<=n;++i)
	{
		a[i] = read();
		MAX = max(MAX,a[i]);
	}
	
	init(MAX);

	for(int i=n;i;--i)
	{
		for(int j=1;j*j<=a[i];++j)
		{
			if(a[i]%j == 0)
			{
				updata(i,j);
				if(j*j!=a[i])
					updata(i,a[i]/j);
			}
		}
	}
	
//	cout << MIN[2][0] << " " << MIN[2][1] << endl;
	 
	for(int i=1;i<=n;++i)
	{
		int ans = inf;
		int tmp = inf;
		for(int j=1;j*j<=a[i];++j)
		{
			if(a[i]%j==0)
			{
				int fac = j,pos;
				if(MIN[fac][0] != i) pos = MIN[fac][0];
				else pos = MIN[fac][1];
				int tt = f[a[pos]] - 2*f[fac];
				if(tt < ans || (tt == ans && pos < tmp))
					ans = tt,tmp = pos;
				fac = a[i]/j;
				if(MIN[fac][0] != i) pos = MIN[fac][0];
				else pos = MIN[fac][1];
				tt = f[a[pos]] - 2*f[fac];
				if(tt < ans || (tt == ans && pos < tmp))
					ans = tt ,tmp = pos;
			}
		}
		printf("%d\n",tmp);
	}

}
