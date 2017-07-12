
#include <cmath>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <algorithm>
typedef long long LL;
const int N = 263000+5;
const int mod = 1e9+7;
const double PI = M_PI;
using namespace std;

struct cp
{
	double a,b;
	cp (double _a=0,double _b=0) :a(_a),b(_b){}
	cp operator+(const cp &z)const {return cp(a+z.a,b+z.b);}
	cp operator-(const cp &z)const {return cp(a-z.a,b-z.b);}
	cp operator*(const cp &z)const {return cp(a*z.a-b*z.b,a*z.b+b*z.a);}
}a[N<<1],b[N<<1],A[N<<1],c[N<<1],x,y;

int rev[N<<1],n=1;
int dig[40];
LL power[N<<1];
LL ans = 0;
char str[N<<1];

void FFT(cp *a,int type)
{
	for(int i=0;i<n;++i) A[i] = a[rev[i]];
	for(int i=0;i<n;++i) a[i] = A[i];
	for(int i=2;i<=n;i<<=1){
		cp wn (cos(2*PI/i),type*sin(2*PI/i));
		for(int k=0;k<n;k+=i) {
			cp w (1,0);
			for(int j=k;j<k+i/2;++j,w = w*wn) {
				x = a[j], y = a[j+i/2]*w; a[j] = x+y, a[j+i/2] = x - y;
			}
		}
	}
	if(type == -1) for(int i=0;i<n;++i) a[i].a /= n;
}

void Pre()
{
	power[0] = 1; for(int i=1;i<N;++i) power[i] = (power[i-1] << 1) % mod;
}

char s[N<<1];
int p[N<<1];

int manacher(char *str,int n)
{
	int re = 0;
	s[0] = '!', s[1] = '^';
	for(int i=1;i<=n;++i) s[i<<1] = str[i] , s[i<<1|1] = '^';
	n <<= 1; n |= 1;
	int mx = 1, id = 1;	
	for(int i=1;i<=n;++i)
	{
		p[i] = min(p[(id<<1)-i],mx-i);
		while(s[i+p[i]] == s[i-p[i]]) p[i]++;
		if(p[i] + i > mx) mx = p[i] + i ,id = i;
		re += p[i] >> 1, re %= mod;
	}
	return re;
}

int main()
{
	scanf("%s",str+1);
	int len = strlen(str+1);
	Pre(); int l = 0;
	for(;n<=(len<<1);n<<=1,l++); n<<=1,l++;
	for(int i=0,t=0,len=0;i<n;++i,len=0)
	{
		for(t=i;t;t>>=1) dig[len++] = t & 1;
		for(t=0;t<l;++t) rev[i] = (rev[i] << 1) | dig[t];
	}
	for(int i=1;i<=len;++i) if(str[i] == 'a') a[i].a = 1;
	FFT(a,1);
	for(int i=0;i<n;++i) b[i] = a[i] * a[i];
	memset(a,0,sizeof a);
	for(int i=1;i<=len;++i) if(str[i] == 'b') a[i].a = 1;
	FFT(a,1);
	for(int i=0;i<n;++i) b[i] = b[i] + a[i] * a[i];
	FFT(b,-1);
	for(int i=0;i<n;++i) (ans += power[((LL)(b[i].a+1.5))>>1] - 1) %= mod;
	cout << (ans + mod - manacher(str,len) )% mod << endl;
}

