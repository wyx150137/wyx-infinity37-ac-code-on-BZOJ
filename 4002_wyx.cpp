
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
typedef unsigned long long ull;
const ull mod = 7528443412579576937ll;

ull mul(ull a,ull b){
	ull res = 0; a %= mod;
	for(;b;b>>=1,a=(a+a)%mod)
		if(b&1)
			res = (res + a) % mod;
	return res;
}

struct Maxtrix{
	ull a[2][2];

	Maxtrix () {
		memset(a,0,sizeof a);
	} 

	void init(){
		a[0][0] = a[1][1] = 1ll;
	}

	void show(){
		cout << a[0][0] << " " << a[0][1] << endl;
		cout << a[1][0] << " " << a[1][1] << endl;
	}

}tmp1,tmp2;

Maxtrix operator * (const Maxtrix &a,const Maxtrix &b){
	Maxtrix res; int i,j,k;
	for(i=0;i<2;++i)
		for(j=0;j<2;++j)
			for(k=0;k<2;++k)
				(res.a[i][j] += mul(a.a[i][k],b.a[k][j]) ) %= mod;
	return res;
}

Maxtrix pow(Maxtrix a,ull b){
	Maxtrix res; res.init();
	for(;b;b>>=1,a=a*a)
		if(b&1)
			res = res * a;
	return res;
}

int main(){
	ull b,d,n;
	cin >> b >> d >> n;
	if(n == 0) {
		puts("1");
		return 0;
	}
	tmp1.a[0][0] = b, tmp1.a[0][1] = 2;
//	tmp1.show();
	tmp2.a[0][0] = b, tmp2.a[0][1] = 1, tmp2.a[1][0] = (d-b*b)/4, tmp2.a[1][1] = 0;
//	tmp2.show();
	tmp2 = pow(tmp2,n-1);
	tmp1 = tmp1 * tmp2;
	ull ans = tmp1.a[0][0];
	if(n%2==0 && d != mul(b,b)) ans = (ans - 1 + mod) % mod;
	cout << ans << endl;
}
