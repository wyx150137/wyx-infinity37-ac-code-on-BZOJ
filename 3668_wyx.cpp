
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 1e5+5; 
using namespace std;

inline int read(){
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int kind[N+5],val[N+5];
int sval[2][50];

int main(){ register int i,j;
	int n = read(), m = read();
	char str[5];
	for(i=1;i<=n;++i) {
		scanf("%s",str);
		if(str[0] == 'A') kind[i] = 1;
		if(str[0] == 'X') kind[i] = 2;
		if(str[0] == 'O') kind[i] = 3;
		val[i] = read();
	}
	int cnt = 31, all = 0, ans = 0;

	for(i=cnt-1;~i;--i) {
		int tmp1 = 0, tmp2 = 1;
		for(j=1;j<=n;++j) {
			if(kind[j] == 1) tmp1 &= ((val[j]>>i)&1), tmp2 &= ((val[j]>>i)&1);
			if(kind[j] == 2) tmp1 ^= ((val[j]>>i)&1), tmp2 ^= ((val[j]>>i)&1);
			if(kind[j] == 3) tmp1 |= ((val[j]>>i)&1), tmp2 |= ((val[j]>>i)&1);
		}
		if(!tmp1 && tmp2 && (1<<i)+all<=m) {
			ans += (1<<i);
			all += (1<<i);
		}
		else if(tmp1) ans += (1<<i);
	}
	cout << ans << endl;
}
