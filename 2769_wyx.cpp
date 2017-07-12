
#include <map>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 2e4+5;

map <int,int> mp;

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int T[N];
int a[N], b[N], c[N];

int main() {
//	freopen("tt.in","r",stdin);
	int n = read();
	register int *p1, i;	
	for(i=1;i<=n;++i) c[i] = b[i] = read();
	sort(b+1,b+n+1); 
	int cnt = 0;
	for(i=1;i<=n;++i) if(!mp[b[i]]) mp[b[i]] = ++ cnt;
	for(i=1;i<=n;++i) c[i] = mp[c[i]];
	int x, temp;
	for(i=1;i<=n;++i) {
		x = c[i] - 1, temp = c[i];
		for(p1 = a + 1; p1 - (a + 1) <= i; p1 = p1 + 15) {
			if(*(p1) > temp) T[*(p1) - x] ++;
			if(*(p1+1) > temp) T[*(p1+1) - x] ++;
			if(*(p1+2) > temp) T[*(p1+2) - x] ++;
			if(*(p1+3) > temp) T[*(p1+3) - x] ++;
			if(*(p1+4) > temp) T[*(p1+4) - x] ++;
			if(*(p1+5) > temp) T[*(p1+5) - x] ++;
			if(*(p1+6) > temp) T[*(p1+6) - x] ++;
			if(*(p1+7) > temp) T[*(p1+7) - x] ++;
			if(*(p1+8) > temp) T[*(p1+8) - x] ++;
			if(*(p1+9) > temp) T[*(p1+9) - x] ++;
			if(*(p1+10) > temp) T[*(p1+10) - x] ++;
			if(*(p1+11) > temp) T[*(p1+11) - x] ++;
			if(*(p1+12) > temp) T[*(p1+12) - x] ++;
			if(*(p1+13) > temp) T[*(p1+13) - x] ++;
			if(*(p1+14) > temp) T[*(p1+14) - x] ++;
		}
		a[i] = c[i];
	}
	double ans = 0;
	for(i=1;i<=n;++i) 
		ans += (double)2.0*T[i]/i;	
	printf("%.6lf\n", ans);
}
