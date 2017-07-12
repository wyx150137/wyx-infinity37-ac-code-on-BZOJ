
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 50;
const double inf = 1e15;
using namespace std;

int sum[N],n;
double f[N][N],C,K;
bool vis[N][N];

double DFS(int l,int r){
	if(l>r)return 0;
	if(vis[l][r])return f[l][r];
	vis[l][r] = 1;
	double &tmp = f[l][r];
	for(int i=l;i<=r;++i)
		tmp = min(tmp,DFS(l,i-1)+DFS(i+1,r)+C*(sum[i]-sum[i-1])/sum[n]);
	return tmp += K*(sum[r]-sum[l-1])/sum[n];
}

int main()
{
	cin >> n >> K >> C;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			f[i][j] = inf;
	for(int i=1;i<=n;++i)
		cin >> sum[i] , sum[i] += sum[i-1];
	printf("%.3lf\n",DFS(1,n));
}
