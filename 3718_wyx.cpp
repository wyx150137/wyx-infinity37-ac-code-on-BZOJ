
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 50000+5;
#define lowbit(x) ((x)&(-x))

int T,n,m;

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int tr[N],pos[N];

void updata(int x,int delta) {
	while(x <= n) {
		tr[x] = max(tr[x],delta);
		x += lowbit(x);
	}
}

int ask(int x) {
	int ans = 0;
	while(x) {
		ans = max(ans,tr[x]);
		x -= lowbit(x);
	}
	return ans;
}

struct data {
	int x1,y1,x2,y2,w,id;
	bool operator <(const data& a)const {
		return x1==a.x1?x2<a.x2:x1<a.x1;
	}
}s1[N],s2[N];

int main() { T = read();while (T--) {
		memset(tr,0,sizeof tr);
		memset(pos,0,sizeof pos);
		n = read(), m = read();
		for (int i=1;i<=n;i++) {
			s1[i].x1 = read(),s1[i].y1 = read();
			s1[i].x2 = read(), s1[i].y2 = read();
			if (s1[i].x1>s1[i].x2)  swap(s1[i].x1,s1[i].x2);
			if (s1[i].y1>s1[i].y2)  swap(s1[i].y1,s1[i].y2);
			s1[i].w=s1[i].y2-s1[i].y1;s1[i].id=i;
		}

		for (int i=1;i<=n;i++) {
			s2[i].x1 = read(), s2[i].y1 = read();
			s2[i].x2 = read(), s2[i].y2 = read();
			if (s2[i].x1>s2[i].x2)  swap(s2[i].x1,s2[i].x2);
			if (s2[i].y1>s2[i].y2)  swap(s2[i].y1,s2[i].y2);
			s2[i].w=s2[i].y2-s2[i].y1;s2[i].id=i;
		}
		
		sort(s1+1,s1+n+1);
		sort(s2+1,s2+n+1);
		for (int i=1;i<=n;i++)  pos[s1[i].id]=i;
		bool flag=true;

		for (int i=n;i&&flag;i--) {
			if (ask(pos[s2[i].id])+s2[i].w>m) flag=false;
			updata(pos[s2[i].id],s2[i].w);
		}
		if (flag) puts("TAK");
		else puts("NIE");
	}
}
