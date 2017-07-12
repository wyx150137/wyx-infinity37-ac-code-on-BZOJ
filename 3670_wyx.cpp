
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int mod = 1e9+7;
const int N = 1e6+5;
typedef long long LL;

char str[N];
int nxt[N], num[N];

int main() {
//	freopen("tt.in","r",stdin);
	int n;
	cin >> n; getchar();
	for(int cases = 1; cases <= n; ++ cases) {
		memset(num,0,sizeof num);
		memset(nxt,0,sizeof nxt);
		scanf("%s",str+1);
		num[1] = 1;
		int tmp = 0, ans = 1;
		for(int i=2;str[i];++i) {
			while(tmp && str[tmp+1] != str[i]) tmp = nxt[tmp];
			if(str[tmp+1] == str[i]) tmp ++; nxt[i] = tmp; num[i] = num[tmp] + 1;
		}
		tmp = 0;
		for(int i=2;str[i];++i) {
			while(tmp && str[tmp+1] != str[i]) tmp = nxt[tmp];
			if(str[tmp+1] == str[i]) tmp ++; 
			while((tmp<<1) > i) tmp = nxt[tmp];
			ans = (LL) ans * (num[tmp] + 1) % mod;
		}
		cout << ans << endl;
	}
}
