
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
typedef long long LL;
const int N = 500000+5;
using namespace std;

LL a[N],m,d,sum;

int n;

inline LL read()
{
	LL x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

bool cmp(const LL &a,const LL &b)
{
	return a > b;
}

void quit()
{
	puts("0");
	exit(0);
}

int main()
{
	cin >> m >> d >> n;
	int ans = 1;
	for(int i=1;i<=n;++i) a[i] = read();
	sort(a+1,a+n+1,cmp);
	int pos = 0;
	for(;a[pos+1]>=m-d && pos < n; pos ++);if(!pos) quit();
	for(int i=1;i<=n;++i)
		if(i^pos)
		{
			if(m-sum+d-sum <= a[pos]) break;
			if(a[i] < d-sum) quit();
			ans ++;sum += a[i]-d+sum;
			if(sum >= d) break;
		}
	if(m-sum+d-sum>a[pos]) quit();
	printf("%d\n",sum >=m ? ans-1 : ans);
}
