
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
const LL inf = 1e10;
LL L, R, F[12][12][12][5][5][5], ans; // f(i,j,k,l,m,n)第i位是j,i+1位是k当前4/8的状态，是否已经有了三个一样的 是否比原数字小的方案数

inline LL calc(LL x) {
	LL last = x;
	memset(F, 0, sizeof F);
	int stack[20] = {}, top = 0;
	while(x) {
		stack[++top] = x % 10, x /= 10;
	}
	for(int i=0;i<=9;++i) 
		for(int j=0;j<=9;++j) {
			for(int k=0;k<=9;++k) {
				int temp1 = 0, temp2 = 0, temp3 = 0, temp4 = 0;
				if(i == 4 || j == 4 || k == 4) temp1 = 1;
				if(i == 8 || j == 8 || k == 8) temp2 = 2;
				if(i == j && j == k) temp3 = 1;
				if(i * 100 + j * 10 + k <= last % 1000) temp4 = 1;
				F[3][i][j][temp1|temp2][temp3][temp4] ++;
	//			cout << i*100+j*10+k << ' ' << (temp1|temp2) << ' ' << (temp3) << ' ' << temp4 << endl;
			}
		}
	const int Max = 11; 
	for(int pos = 4; pos <= Max; pos ++) {
		for(int i=0;i<=9;++i) {
			for(int j=0;j<=9;++j) {
				for(int k=0;k<=9;++k) {
					int temp1 = 0, temp2 = 0, temp3 = 0, temp4 = 0;
					if(i == 4 || j == 4 || k == 4) temp1 = 1;
					if(i == 8 || j == 8 || k == 8) temp2 = 2;
					if(i == j && j == k) temp3 = 1;
					for(int temp = 0; temp <= 1; ++ temp) { // 上一轮是否小于等于
						if(stack[pos] > i || (stack[pos] == i && temp == 1)) temp4 = 1;
						for(int lasttemp = 0; lasttemp < 4; ++ lasttemp) { // 上一轮 4 8 状态
							for(int lasttemp3 = 0; lasttemp3 <= 1; ++ lasttemp3) { // 上一轮里面有没有三个一样的
								F[pos][i][j][temp1|temp2|lasttemp][temp3|lasttemp3][temp4] += 
								F[pos-1][j][k][lasttemp][lasttemp3][temp];
							}
						}
					}
				}
			}
		}
	}
	LL ret = 0;
	for(int i=1;i<=9;++i) {
		for(int j=0;j<=9;++j) {
			for(int sta=0;sta<=2;++sta) {
				ret += F[Max][i][j][sta][1][1];
			}
		}
	}
	return ret;
}

int main() {
//	freopen("tt.in","r",stdin);
	cin >> L >> R;
	if(L == R && L == inf) return 0*puts("1");
	else if(L == inf) ans = 1;
	else L --;
//	cout << calc(R) << ' ' << calc(L) << endl;
	cout << calc(R) - calc(L) + ans << endl;
}
