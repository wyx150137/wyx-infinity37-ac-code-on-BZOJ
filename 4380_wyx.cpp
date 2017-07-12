
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
typedef long long LL;
using namespace std;

const int N = 50+2;
const int M = 4000+2;

int n,m,cnt;

int l[M],r[M],c[M],a[M];
int pos[N][N][M],val[N][N][M];

LL f[N][N][M],sum[N][N][M];
int V[M];

void print(int l,int r,int v)
{
	if(r < l) return;
	int tt = val[l][r][v];
	print(l,pos[l][r][v]-1,tt);
	printf("%d ",V[tt]);
	print(pos[l][r][v]+1,r,tt);
}

inline int read()
{
	int x = 0, f = 1; char ch = getchar();
	while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
	while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
	return x * f;
}
int stack[M];

int main()
{
	cin >> n >> m;
	register int k;
	for(int i=1;i<=m;++i) l[i] = read(),r[i] = read(),V[i] = c[i] = read();
	int top;
	sort(V+1,V+m+1);
	for(int i=1;i<=m;++i)
		if(V[i]!=V[i-1])
			V[++cnt] = V[i];
	for(int i=0;i<n;++i)
		for(int j=1;j+i<=n;++j)
		{
			int ri = j + i;
			for(k=j;k<=ri;++k)
			{
				top = 0;
				for(int t=1;t<=m;++t)
					if(l[t] >= j && r[t] <= ri && l[t] <= k && r[t] >= k)
						stack[++top] = c[t];
				sort(stack+1,stack+top+1);
				for(int t=1,now=1;t<=cnt;++t)
				{
					while(now <= top && stack[now] < V[t]) ++ now;
					LL t1 = sum[j][k-1][t] + sum[k+1][ri][t] + (LL)V[t]*(top-now+1);
					if(t1 >= f[j][ri][t])
					{
						f[j][ri][t] = t1;
						pos[j][ri][t] = k;
					}
				}
			}

			for(k=cnt;k>=1;--k)
			{
				val[j][ri][k] = k;
				if(f[j][ri][k] < sum[j][ri][k+1])
				{
					pos[j][ri][k] = pos[j][ri][k+1];
					val[j][ri][k] = val[j][ri][k+1];
				}
				sum[j][ri][k] = max(sum[j][ri][k+1],f[j][ri][k]);
			}
		}
	cout << sum[1][n][1] << endl;
	print(1,n,1);
}
