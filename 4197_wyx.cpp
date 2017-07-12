
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1000+5;
int mod, n;
int F[260][260], G[260][260], H[260][260];

struct data {
	int x, y;
	bool operator < (const data &z) const {
		return y < z.y;
	}
}a[N];

int prime[] = {2,3,5,7,11,13,17,19};

int main() {
	cin >> n >> mod;
	int Max = (1<<8)-1;
	for(int i=2;i<=n;++i) {
		int x = i;
		for(int j=0;j<8;++j)
			while(x % prime[j] == 0) a[i].x |= (1<<j), x /= prime[j];
		a[i].y = x;
	}
	sort(a+2,a+n+1);
	F[0][0] = 1;
	int i;
	register int temp1,temp2;

	for(i=2;a[i].y==1;++i) {
		int x = a[i].x;
		memcpy(G, F, sizeof F);
		for(temp1=0;temp1<=Max;++temp1) {
			for(temp2=0;temp2<=Max;++temp2) if(!(temp1&temp2)){
				if(!(temp2&x)) (G[temp1|x][temp2] += F[temp1][temp2]) %= mod;
				if(!(temp1&x)) (G[temp1][temp2|x] += F[temp1][temp2]) %= mod;
			}
		}
		memcpy(F, G, sizeof F);
	}

	for(int p=i;a[i].y;) {
		memcpy(G, F, sizeof F);
		memcpy(H, F, sizeof F);
		while(a[p].y == a[i].y) ++p;
		for(;i<p;++i) {
			int x = a[i].x;
			for(temp1=Max;~temp1;--temp1) {
				for(temp2=Max;~temp2;--temp2) {
					if(!(temp1&temp2)) {
						if(!(temp2&x)) (G[temp1|x][temp2] += G[temp1][temp2]) %= mod;
					}
				}
			}
			for(temp1=Max;~temp1;--temp1) {
				for(temp2=Max;~temp2;--temp2) {
					if(!(temp1&temp2)) 
						if(!(temp1&x)) (H[temp1][temp2|x] += H[temp1][temp2]) %= mod;
				}
			}
		}
		for(temp1=0;temp1<=Max;++temp1) {
			for(temp2=0;temp2<=Max;++temp2) {
				if(!(temp1&temp2)) {
					F[temp1][temp2] = - F[temp1][temp2];
					(F[temp1][temp2] += G[temp1][temp2]) %= mod;
					(F[temp1][temp2] += H[temp1][temp2]) %= mod;
					(F[temp1][temp2] += mod) %= mod; 
				}
			}
		}
	}
	int ans = 0;
	for(temp1=0;temp1<=Max;++temp1)
		for(temp2=0;temp2<=Max;++temp2) {
			(ans += F[temp1][temp2]) %= mod;
		}
	cout << ans << endl;
}
