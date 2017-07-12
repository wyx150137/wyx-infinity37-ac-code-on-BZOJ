
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 1000+5;
const int M = 100+5;
using namespace std;

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9') {if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9') {x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int t, n;
int sg[M][M];

struct node{
	int x,y;
} poi[N];

inline int get(int x,int y) {
	if(!x || !y) return 0;
	if(x == y) return sg[x][y] = 0;
	if(sg[x][y] != -1) return sg[x][y];
	bool hash[M*M] = {};
	for(int k=1;;++k) {
		if(x - k <= 0 && y - k <= 0) break;
		if(x - k >  0 && x - k != y) hash[get(x-k,y)] = 1;
		if(y - k >  0 && y - k != x) hash[get(x,y-k)] = 1;
		if(x - k >  0 && y - k >  0) hash[get(x-k,y-k)] = 1;
	}
	for(int i=0;;i++) 
		if(!hash[i])
			return (sg[x][y] = sg[y][x] = i);
}

int main() {//freopen("08.in","r",stdin);
	cin >> t;
	memset(sg, -1, sizeof sg);
	while(t -- ){
		cin >> n;
		bool flag = false;
		for(int i=1;i<=n;++i) {
			poi[i].x = read(), poi[i].y = read();
			if(!poi[i].x || !poi[i].y || poi[i].x == poi[i].y) flag = true;
		}
		if(flag) {
			puts("^o^");
			continue;
		}
		int ans = 0;
		for(int i=1;i<=n;++i) ans ^= get(poi[i].x, poi[i].y);
		if(ans == 0) puts("T_T");
		else puts("^o^");
	}

}
