
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 3e5+5;
const int M = 233333+5;
const int mod = 1000000007;

__attribute__((always_inline)) char getc()
{
	static const int LEN = 1<<15;
	static char buf[LEN],*S=buf,*T=buf;
	if(S == T)
	{
		T = (S=buf)+fread(buf,1,LEN,stdin);
		if(S == T)return EOF;
	}
	return *S++;
}

__attribute__((always_inline)) int read()
{
	static char ch;
	static int D;
	while(!isdigit(ch=getc())) if(ch == EOF) return -1;
	for(D=ch-'0'; isdigit(ch=getc());) D=(D<<3)+(D<<1)+(ch-'0');
	return D;
}
int a[N];
int T[M+5];

int main() {
	int n = read();
	for(int i=1;i<=n;++i) a[i] = read();
	reverse(a+1, a+n+1);
	register int j;
	for(int i=1;i<=n;++i) {
		int ans = 0;
		for(j=a[i];j;j=(j-1)&a[i]) {
			(ans += T[j]) %= mod; 
		}
		T[a[i]] = ans + 1;
	}
	long long ans = 0;
	for(int i=1;i<=n;++i) (ans += (T[a[i]] - 1) ) %= mod;
	cout << ans << endl;
}
