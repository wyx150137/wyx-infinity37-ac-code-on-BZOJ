
#include <stdio.h>
#include <cctype>
#include <iostream>
#include <string.h>
using namespace std;
const int N = 32;
__attribute__((optimize("-O2"))) char getc()
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
 
__attribute__((optimize("-O2"))) int read()
{
	static char ch;
	static int D;
	while(!isdigit(ch=getc()));
	for(D=ch-'0'; isdigit(ch=getc());)
		D=(D<<3)+(D<<1)+(ch-'0');
	return D;
}
__attribute__((optimize("-O2"))) int main() {
	int a[N] = {};
	int n = read();
	register int j;
	for(int i=1;i<=n;++i) {
		int tmp = read();
		for(j=30;~j;--j) {
			if(((1<<j)&a[j]) && ((1<<j)&tmp)) tmp ^= a[j]	;
			else if(( ( (1<<j)&a[j]) == 0) && ((1<<j)&tmp)) {a[j] = tmp; break;}
		}
	}
	int now = 0;
	for(j=30;~j;--j) {
		if(((1<<j)&a[j])&& ((1<<j)&now)==0) now ^= a[j];
	}
	printf("%d ", now);
	for(j=0;j<30;++j) if(a[j]) {now ^= a[j]; break;}
	cout << now << endl;
}
