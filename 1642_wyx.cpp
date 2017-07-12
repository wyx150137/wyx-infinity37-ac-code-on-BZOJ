
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
#define max(a,b) ((a)>(b)?(a):(b))
const int N = 1000+5;

struct data
{
	int s,t,val;
	bool operator < (const data &z)const
	{
		return s < z.s;
	}
}a[N];

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch =='-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
} 

int f[N];

int main()
{
	int ans = 0;
	read();
	int m = read(),R = read();
	for(int i=1;i<=m;++i)
		a[i].s=read(),a[i].t=read(),a[i].val = read();
	sort(a+1,a+m+1);
	for(int i=1;i<=m;++i)
	{
		f[i] = a[i].val;
		for(int j=0;j<i;++j)
			if(a[i].s-a[j].t >= R)
				f[i] = max(f[i],f[j]+a[i].val),
				ans = max(ans,f[i]);
	}
//	for(int i=1;i<=m;++i)
//		cout << f[i] << endl;
	cout << ans;

}
