
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 1000000+5;
using namespace std;
inline int read(){
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int a[N];

int main(){
	int n = read();
	for(int i=1;i<=n;++i) a[i] = read();
	sort(a+1,a+n+1);
	int sum = 0;
	if(n==1 && (a[1]&1)) return puts("NIESTETY"),0;
	for(int i=1;i<=n;++i) sum += a[i];
	if(sum % 2 == 0) cout << sum << endl;
	else 
		for(int i=1;i<=n;++i) 
			if(a[i]&1){
				cout << sum -a[i] << endl;
				return 0;
			}
}
