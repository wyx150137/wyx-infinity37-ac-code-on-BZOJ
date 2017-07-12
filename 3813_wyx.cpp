
#include <bitset>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define mp make_pair
using namespace std;
typedef long long LL;
const int N = 1e6+5;
const int mod = 19961993;

LL prime[100],rev[100];

LL pow(LL a,LL b){ LL res = 1;
	for(;b;b>>=1, a = a * a % mod)
		if(b & 1)
			res = res * a % mod;
	return res;
}

bool isprime(int x){
	for(int i=2;i*i<=x;++i)
		if(x%i == 0) return false;
	return true;
}
char getc()
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
  
int read()
{
    static char ch;
    static int D;
    while(!isdigit(ch=getc()));
    for(D=ch-'0'; isdigit(ch=getc());)
        D=(D<<3)+(D<<1)+(ch-'0');
    return D;
}
  

struct seg{
	seg *l,*r;
	bitset <60> cnt;
	LL val;
	seg () {
		l = r = NULL;
		cnt.reset();
		val = 0;
	}
}*root;

void build(seg *&k,int l,int r){
	k = new seg();
	if(l==r){
		k -> cnt[1] = 1;
		k -> val = 3;
		return;
	}
	int mid = (l+r) >> 1;
	build(k->l,l,mid);
	build(k->r,mid+1,r);
	k->cnt = k->l->cnt | k->r->cnt;
	k->val = k->l->val * k->r->val % mod;
}

inline void change(seg *k,int l,int r,int pos,int val){
	if(l==r){
		k -> val = val;
		for(int i=0;i<60;++i)
			if(val % prime[i] == 0) k->cnt[i] = 1;
			else k -> cnt[i] = 0;
		return;
	}
	int mid = (l+r) >> 1;
	if(pos <= mid) change(k->l,l,mid,pos,val);
	else change(k->r,mid+1,r,pos,val);
	k -> cnt = k -> l -> cnt | k -> r -> cnt;
	k -> val = k -> l -> val * k -> r -> val % mod;
}

pair <bitset<60>,LL >ask(seg *k,int l,int r,int x,int y){
	if(l==x&&r==y) return mp(k->cnt,k->val);
	int mid = (l+r) >> 1;
	if(y <= mid) return ask(k->l,l,mid,x,y);
	else if(x > mid)return ask(k->r,mid+1,r,x,y);
	else {
		pair <bitset<60>,LL > tmp1, tmp2;
		tmp1 = ask(k->l,l,mid,x,mid);
		tmp2 = ask(k->r,mid+1,r,mid+1,y);
		tmp1.first |= tmp2.first;
		(tmp1.second*=tmp2.second) %= mod;
		return tmp1;
	}
}

int main(){// freopen("13.in","r",stdin);
	register int i,j;
	int cnt = 0;
	LL ans;
	for(i=2;i<=281;++i) if(isprime(i)) prime[cnt++] = i;
	for(i=0;i<cnt;++i) rev[i] = (prime[i]-1)*pow(prime[i],mod-2)%mod;
	int n = read(); build(root,1,100000);
	for(i=1;i<=n;++i){
		int opt = read(), x = read(), y = read();
		if (opt == 0){
			pair <bitset<60>,LL > p = ask(root,1,100000,x,y); ans = p.second;
			for(j=0;j<60;++j) if(p.first[j]) (ans *= rev[j]) %= mod;
			printf("%lld\n",ans);
		}
		else
			change(root,1,100000,x,y);
	}
}
