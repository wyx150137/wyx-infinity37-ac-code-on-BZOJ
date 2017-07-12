
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = 5000+5;
LL seed, a, b, c, d;
int arr[N*N],g[N][N];
int ans[N<<2];
bool v[N][N];
  
inline int work() {
	return seed = (a*seed*seed%d+b*seed%d+c)%d;
}

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int main() {
	cin >> seed >> a >> b >> c >> d;
	int n, m, q;
	cin >> m >> n >> q;
	for(int i=1;i<=n*m;++i) arr[i] = i, swap(arr[i], arr[work()%i+1]);
	for(int i=1;i<=q;++i) {
		int x = read(), y = read();
		swap(arr[x], arr[y]);
	}
	for(int i=1;i<=m;++i) for(int j=1;j<=n;++j) g[i][j] = arr[(i-1)*n+j];
	for(int i=1;i<=m;++i) for(int j=1;j<=n;++j) arr[g[i][j]] = (i-1)*n+j;
	int x, y;
	for(int i=1;i<=n*m;++i) {
		x=arr[i]/n+1-(arr[i]%n==0), y=arr[i]-(x-1)*n;
		if (!v[x][y]) {   
			if (i!=1) putchar(' '); 
			printf("%d",i); 
			for (int j=x+1;j<=m;j++) 
				for (int k=y-1;k;k--) { 
					if (v[j][k])
						break; 
					v[j][k]=true; 
				} 
			for (int j=x-1;j;j--)
				for (int k=y+1;k<=n;k++) { 
					if (v[j][k])
						break; 
					v[j][k]=true; 
				} 
		}    
	}
}
