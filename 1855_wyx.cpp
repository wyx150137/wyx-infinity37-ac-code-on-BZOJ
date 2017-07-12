
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>

const int N = 2000+10;

using namespace std;

int f[N][N];
int q[N];

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

struct data
{
	int Ap,Bp,As,Bs;
	void in(){
		Ap = read(), Bp = read(), As = read(), Bs = read();
	}
}a[N];

int main()
{
	int T = read(), MAX = read(), w = read();
	for(int i=1;i<=T;++i) a[i].in();
	memset(f,-0x3f,sizeof f);
	register int i , j;
	for(i=1;i<=T;++i)
	{
		for(j=0;j<=a[i].As;++j) f[i][j] = -a[i].Ap * j;
		for(j=0;j<=MAX;++j) f[i][j] = max(f[i][j],f[i-1][j]);
		int op = i-w-1;
		if(op >= 0)
		{
			{
				int l = 0 , r = 0;
				for(j=0;j<=MAX;++j)
				{
					while(l<r && q[l]<j-a[i].As) l++;
					while(l<r && f[op][j]+j*a[i].Ap>=f[op][q[r-1]]+q[r-1]*a[i].Ap) --r;
					q[r++] = j;
					if(l < r) f[i][j] = max(f[i][j],f[op][q[l]]-(j-q[l])*a[i].Ap);
				}
			}
			
			{
				int l = 0 ,r = 0;
				for(j=MAX;~j;--j)
				{
					while(l<r && q[l]>j+a[i].Bs) l++;
					while(l<r && f[op][j]+j*a[i].Bp >= f[op][q[r-1]] + q[r-1]*a[i].Bp) r--;
					q[r++] = j;
					if(l<r) f[i][j] = max(f[i][j],f[op][q[l]] + (q[l]-j)*a[i].Bp);
				}
			}
		}
	}

	int ans = 0;

  	for(i=0;i<=MAX;++i) ans = max(ans,f[T][i]);
  	cout << ans << endl;
}
