
#include <set>
#include <map>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
#define pb push_back
const int N = 5e5+5;
const int M = N << 2;

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

struct data {
	int val[33];
	data () {
		memset(val, 0, sizeof val);
	}
	void operator += (int x) {
		for(int i=30;~i;--i) {
			if((1<<i)&x) {
				if((1<<i)&val[i]) x ^= val[i];
				else {
					val[i] = x;
					break;
				} 
			}
		}
	}

	inline int get_max() {
		int now = 0;
		for(int i=30;~i;--i) {
			if((1<<i)&val[i] && !((1<<i)&now)) now ^= val[i]; 
		}
		return now;
	}
}Ans;

vector <int> tr[M];

inline void change(int k,int l,int r,int x,int y,int val) {
	if(l==x && r==y) {
		tr[k].pb(val);
		return;
	}
	int mid = (l+r) >> 1;
	if(y <= mid) change(k<<1,l,mid,x,y,val);
	else if(x > mid) change(k<<1|1,mid+1,r,x,y,val);
	else change(k<<1,l,mid,x,mid,val), change(k<<1|1,mid+1,r,mid+1,y,val);
}

inline void solve(int k,int l,int r,data C) {
	vector <int> :: iterator it;
	for(int i=0;i<tr[k].size();++i) C += tr[k][i];
	if(l==r) {
		printf("%d\n", C.get_max());
		return ;
	}
	int mid = (l+r) >> 1;
	solve(k<<1,l,mid,C);
	solve(k<<1|1,mid+1,r,C);
}

set <int> s;
map <int,int> cnt, last;

int main() {
//	freopen("tt.in","r",stdin);
	int n = read();
	for(int i=1;i<=n;++i) {
		int x = read();
		if(x > 0) {
			cnt[x] ++;
			if(cnt[x] == 1) last[x] = i;
			s.insert(x);
		}
		else {
			cnt[-x] --;
			if(cnt[-x] == 0) change(1,1,n,last[-x],i-1,-x); 
//			cout << last[-x] << " " << i-1 << " " << -x << endl;
			s.erase(s.find(-x));
		}
	}
	set <int> :: iterator it;
	for(it = s.begin(); it != s.end(); ++it) {
		int tmp = (*it);
		change(1,1,n,last[tmp],n,tmp);
//		cout << last[tmp] << " " << n << " " << tmp << endl;
	}
	solve(1,1,n,Ans);
}
