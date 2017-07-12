
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = 2e6+5;
const LL inf = 1e18;
#define fir first
#define sec second

int all;

const int dx [] = {-1,1,0,0};
const int dy [] = {0,0,1,-1};

struct data{
	int F[N], col[N];
	int stack[N];
	
	inline int find(int x) {
		while(F[x] != x && F[x]) {
			stack[++stack[0]] = x;
			x = F[x];
		}
		F[x] = x;
		while(stack[0]) {
			F[stack[stack[0]--]] = x;
		}
		return x;	
	}
	
	inline void init() {
		for(int i=1;i<=all;++i) {
			col[i] = -1;
		}
	}
	
	inline void solve(int l,int r,int C) {
		for(int i = find(l); i <= r; i = find(i)) {
			col[i] = C;
			F[i] = i + 1;
		}
	}
} temp1, temp2;

int n, m;

inline int calc(int i,int j,int opt) {
	if(opt == 2) 
		return (i-1)*n+j;
	else 
		return (j-1)*m+i;
}

char str[N];

LL be[N];
pair<int,int> q[N], bepos[N];
char tempstr[N];

int main() {
//	freopen("tt.in","r",stdin);
	int Q;
	cin >> n >> m >> Q;
	all = n * m;
	temp1.init(); 
	temp2.init();
	int last = (n-1) * m;
	for(int i=1;i<=n;++i) {
		scanf("%s", tempstr+1);
		for(int j=1;j<=m;++j) {
			str[last+j] = tempstr[j];
		}
		last -= m;
	}
	pair <int,int> now;
	now = make_pair(1,1);
	
	LL times = 1;
	
	char tt[20];
	int tt1, o ;
	
	for(int i=1;i<=Q;++i) {
		be[i] = times;
		bepos[i] = now;
		scanf("%s%d" , tt, & tt1);
		if(tt[0] == 'u') o = 2;
		else if(tt[0] == 'r') o = 1;
		else if(tt[0] == 'd') o = 3;
		else o = 0;
		now.fir += tt1 * dx[o];
		now.sec += tt1 * dy[o];
		times += tt1;
		q[i] = make_pair(o, tt1);
	}
	
	for(int i=Q;i>=1;--i) {
		pair <int,int> temp = now;
		temp.fir -= q[i].sec * dx[q[i].fir];
		temp.sec -= q[i].sec * dy[q[i].fir];
		if(q[i].fir < 2) {
			int tmp1 = calc(temp.fir,temp.sec,1);
			int tmp2 = calc(now.fir,now.sec, 1);
			temp1.solve(min(tmp1,tmp2),max(tmp1,tmp2),i);
			now = temp;
		}
		else {
			int tmp1 = calc(temp.fir, temp.sec, 2);
			int tmp2 = calc(now.fir,now.sec,2);
			temp2.solve(min(tmp1,tmp2),max(tmp1,tmp2),i);
			now = temp;
		}
	}
	
	LL Min = 0, Max = times;

	for(int i=1;i<=n;++i) {
		for(int j=1;j<=m;++j) {
			if(str[(i-1)*m+j] == '#') {
				if(temp1.col[calc(j,i,1)] == -1 && temp2.col[calc(j,i,2)] == -1) {
					puts("-1 -1");
					return 0;
				}
				else {
					int pos = max(temp1.col[calc(j,i,1)], temp2.col[calc(j,i,2)]);
					LL ttimes = be[pos] + abs(i - bepos[pos].sec) + abs(j - bepos[pos].fir);
					Min = max(Min, ttimes);
				}
			}
			else {
				int pos = max(temp1.col[calc(j,i,1)], temp2.col[calc(j,i,2)]);
				if(pos == -1) continue; 
				LL ttimes = be[pos] + abs(i - bepos[pos].sec) + abs(j - bepos[pos].fir);
				Max = min(Max, ttimes - 1);
			}
		}
	}
	
	if(Min > Max) puts("-1 -1");
	else cout << Min << ' ' << Max << endl;
}
