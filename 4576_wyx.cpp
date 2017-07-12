
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <string.h>
const int N = 300000;
using namespace std;

int F[N][59];

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int a[N];

int main()
{
	int n = read();
	for(int i=1;i<=n;++i) a[i] = read();
//	sort(a+1,a+n+1);
	for(int i=1;i<=n;++i) F[i][a[i]] = i+1;

	for(int j=2;j<=58;++j)
		for(int i=1;i<=n;++i)
			if(!F[i][j])
				F[i][j] = F[F[i][j-1]][j-1];

	int ans = 0;

	for(int i=1;i<=n;++i)
		for(int j=58;j;--j)
			if(F[i][j])
			{
				ans = max(ans,j);
				break;
			}
	cout << ans << endl;
}
