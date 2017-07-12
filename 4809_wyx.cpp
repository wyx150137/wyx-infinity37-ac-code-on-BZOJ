
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
 
int a[20][20], v1[20], v2[40], v3[40], n, ans;
 
void DFS(int x)
{
	if (x > n) {ans++; return;}
	for(int i=1;i<=n;++i) 
		if (!a[x][i] && !v1[i] && !v2[x + i] && !v3[x - i + n]) {
			v1[i] = v2[x + i] = v3[x - i + n] = 1;
			DFS(x + 1);
			v1[i] = v2[x + i] = v3[x - i + n] = 0;
		}
}
 
int main()
{
	scanf("%d", &n);
	for(int i=1;i<=n;++i) for(int j=1;j<=n;++j) scanf("%d", &a[i][j]);
	DFS(1); printf("%d\n", ans);
	return 0;
}
