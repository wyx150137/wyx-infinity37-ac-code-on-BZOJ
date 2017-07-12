
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 50000;
int prime[N+5],cnt,sum[N+5];
bool F[N];
void init(){
	sum[1] = 1;
	register int i,j;
	for(i=2;i<=N;++i){
		if(!F[i]) sum[prime[++cnt] = i] = -1;
		for(j=1;prime[j]*i<=N;++j){
			F[prime[j]*i] = 1;
			if(i%prime[j] == 0) break;
			sum[i*prime[j]] = -sum[i];
		}
	}
	for(i=1;i<=N;++i) sum[i] += sum[i-1];
}

inline int calc(int x,int y){
	register int i;
	if(x>y)swap(x,y);
	int last = 0,ans = 0;
	for(i=1;i<=x;i=last+1){
		last = min(x/(x/i),y/(y/i));
		ans += (x/i)*(y/i)*(sum[last]-sum[i-1]);
	}
	return ans;
}

inline int read(){
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int main(){
	init();
	int n,a,b,c,d,k;
	cin >> n ;
	while(n--){
		a = read(), b = read(), c = read(), d = read(), k = read();
		printf("%d\n",calc(b/k,d/k)-calc((a-1)/k,d/k)-calc((c-1)/k,(b)/k)+calc((a-1)/k,(c-1)/k));
	}
}
