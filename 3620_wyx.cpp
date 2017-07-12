
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 2e5+5;
char s[N];
int k, nxt[N];
long long ans = 1;

inline void solve(char *str) {
	int tmp = 0;
	int i = 2;
	for(;str[i];++i) {
		while(tmp && str[tmp+1] != str[i]) tmp = nxt[tmp];
		if(str[tmp+1] == str[i]) tmp ++; nxt[i] = tmp;
	}
	tmp = 0; i = 1;
	for(;str[i];++i) {
		while(tmp && str[tmp+1] != str[i]) tmp = nxt[tmp];
		if(str[tmp+1] == str[i]) tmp ++;
		while((tmp<<1) >= i) tmp = nxt[tmp];
		if(tmp >= k) ans ++;
	}
}

int main() {
//	freopen("07.in","r",stdin);
	scanf("%s%d",s+1, &k);
	for(int i=0;s[i+1];++i) solve(s+i);
	cout << ans-1 << endl;
}
