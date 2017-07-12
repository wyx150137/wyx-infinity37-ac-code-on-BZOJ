
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define N 1000000+5
const int inf = 0x7fffff;
using namespace std;
int a[N];
int q_MAX[N],q_MIN[N];
int l_MAX,r_MAX;
int l_MIN,r_MIN;

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int main()
{
	register int i = 1;
	int n = read() , m = read(), c = read();
	bool flag = false;
	for(;i<=n;++i)
	{
		a[i] = read();
		{
			int &r = r_MAX;
			int &l = l_MAX;
			int *q = q_MAX;
			while( r-l>=1 && a[q[r]] < a[i])
				r --;
			q[++r] = i;
			while(i - q[l+1] >= m)
				l ++;
		}
		{
			int &r = r_MIN;
			int &l = l_MIN;
			int *q = q_MIN;
			while(r-l>=1 && a[q[r]] > a[i])
				r --;
			q[++r] = i;
			while(i - q[l+1] >= m)
				l ++;
		}
		if(i >= m && a[q_MAX[l_MAX+1]] - a[q_MIN[l_MIN+1]] <= c && i - m + 1 > 0 )
				printf("%d\n",i-m+1),flag = true;
	}
	if(!flag)
		puts("NONE");
}
